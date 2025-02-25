/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

//
// NPC_move.cpp
//
#include "anims.h"
#include "b_local.h"
#include "g_nav.h"

void G_Cylinder(vec3_t start, vec3_t end, float radius, vec3_t color);

qboolean G_BoundsOverlap(const vec3_t mins1, const vec3_t maxs1,
                         const vec3_t mins2, const vec3_t maxs2);
int NAV_Steer(gentity_t *self, vec3_t dir, float distance);
extern int GetTime(int lastTime);

navInfo_t frameNavInfo;
extern qboolean FlyingCreature(gentity_t *ent);

extern qboolean PM_InKnockDown(playerState_t *ps);

/*
-------------------------
NPC_ClearPathToGoal
-------------------------
*/

qboolean NPC_ClearPathToGoal(vec3_t dir, gentity_t *goal) {
  trace_t trace;
  float radius, dist, tFrac;

  // FIXME: What does do about area portals?  THIS IS BROKEN
  // if ( trap->inPVS( NPC->r.currentOrigin, goal->r.currentOrigin ) == qfalse )
  //	return qfalse;

  // Look ahead and see if we're clear to move to our goal position
  if (NAV_CheckAhead(NPCS.NPC, goal->r.currentOrigin, &trace,
                     (NPCS.NPC->clipmask & ~CONTENTS_BODY) |
                         CONTENTS_BOTCLIP)) {
    // VectorSubtract( goal->r.currentOrigin, NPC->r.currentOrigin, dir );
    return qtrue;
  }

  if (!FlyingCreature(NPCS.NPC)) {
    // See if we're too far above
    if (fabs(NPCS.NPC->r.currentOrigin[2] - goal->r.currentOrigin[2]) > 48)
      return qfalse;
  }

  // This is a work around
  radius = (NPCS.NPC->r.maxs[0] > NPCS.NPC->r.maxs[1]) ? NPCS.NPC->r.maxs[0]
                                                       : NPCS.NPC->r.maxs[1];
  dist = Distance(NPCS.NPC->r.currentOrigin, goal->r.currentOrigin);
  tFrac = 1.0f - (radius / dist);

  if (trace.fraction >= tFrac)
    return qtrue;

  // See if we're looking for a navgoal
  if (goal->flags & FL_NAVGOAL) {
    // Okay, didn't get all the way there, let's see if we got close enough:
    if (NAV_HitNavGoal(trace.endpos, NPCS.NPC->r.mins, NPCS.NPC->r.maxs,
                       goal->r.currentOrigin, NPCS.NPCInfo->goalRadius,
                       FlyingCreature(NPCS.NPC))) {
      // VectorSubtract(goal->r.currentOrigin, NPC->r.currentOrigin, dir);
      return qtrue;
    }
  }

  return qfalse;
}

/*
-------------------------
NPC_CheckCombatMove
-------------------------
*/

static QINLINE qboolean NPC_CheckCombatMove(void) {
  // return NPCInfo->combatMove;
  if ((NPCS.NPCInfo->goalEntity && NPCS.NPC->enemy &&
       NPCS.NPCInfo->goalEntity == NPCS.NPC->enemy) ||
      (NPCS.NPCInfo->combatMove)) {
    return qtrue;
  }

  if (NPCS.NPCInfo->goalEntity && NPCS.NPCInfo->watchTarget) {
    if (NPCS.NPCInfo->goalEntity != NPCS.NPCInfo->watchTarget) {
      return qtrue;
    }
  }

  return qfalse;
}

/*
-------------------------
NPC_LadderMove
-------------------------
*/

static void NPC_LadderMove(vec3_t dir) {
  // FIXME: this doesn't guarantee we're facing ladder
  // ALSO: Need to be able to get off at top
  // ALSO: Need to play an anim
  // ALSO: Need transitionary anims?

  if ((dir[2] > 0) ||
      (dir[2] < 0 && NPCS.NPC->client->ps.groundEntityNum == ENTITYNUM_NONE)) {
    // Set our movement direction
    NPCS.ucmd.upmove = (dir[2] > 0) ? 127 : -127;

    // Don't move around on XY
    NPCS.ucmd.forwardmove = NPCS.ucmd.rightmove = 0;
  }
}

/*
-------------------------
NPC_GetMoveInformation
-------------------------
*/

static QINLINE qboolean NPC_GetMoveInformation(vec3_t dir, float *distance) {
  // NOTENOTE: Use path stacks!

  // Make sure we have somewhere to go
  if (NPCS.NPCInfo->goalEntity == NULL)
    return qfalse;

  // Get our move info
  VectorSubtract(NPCS.NPCInfo->goalEntity->r.currentOrigin,
                 NPCS.NPC->r.currentOrigin, dir);
  *distance = VectorNormalize(dir);

  VectorCopy(NPCS.NPCInfo->goalEntity->r.currentOrigin,
             NPCS.NPCInfo->blockedDest);

  return qtrue;
}

/*
-------------------------
NAV_GetLastMove
-------------------------
*/

void NAV_GetLastMove(navInfo_t *info) { *info = frameNavInfo; }

/*
-------------------------
NPC_GetMoveDirection
-------------------------
*/

qboolean NPC_GetMoveDirection(vec3_t out, float *distance) {
  vec3_t angles;

  // Clear the struct
  memset(&frameNavInfo, 0, sizeof(frameNavInfo));

  // Get our movement, if any
  if (NPC_GetMoveInformation(frameNavInfo.direction, &frameNavInfo.distance) ==
      qfalse)
    return qfalse;

  // Setup the return value
  *distance = frameNavInfo.distance;

  // For starters
  VectorCopy(frameNavInfo.direction, frameNavInfo.pathDirection);

  // If on a ladder, move appropriately
  if (NPCS.NPC->watertype & CONTENTS_LADDER) {
    NPC_LadderMove(frameNavInfo.direction);
    return qtrue;
  }

  // Attempt a straight move to goal
  if (NPC_ClearPathToGoal(frameNavInfo.direction, NPCS.NPCInfo->goalEntity) ==
      qfalse) {
    // See if we're just stuck
    if (NAV_MoveToGoal(NPCS.NPC, &frameNavInfo) == WAYPOINT_NONE) {
      // Can't reach goal, just face
      vectoangles(frameNavInfo.direction, angles);
      NPCS.NPCInfo->desiredYaw = AngleNormalize360(angles[YAW]);
      VectorCopy(frameNavInfo.direction, out);
      *distance = frameNavInfo.distance;
      return qfalse;
    }

    frameNavInfo.flags |= NIF_MACRO_NAV;
  }

  // Avoid any collisions on the way
  if (NAV_AvoidCollision(NPCS.NPC, NPCS.NPCInfo->goalEntity, &frameNavInfo) ==
      qfalse) {
    // FIXME: Emit a warning, this is a worst case scenario
    // FIXME: if we have a clear path to our goal (exluding bodies), but then
    // this 			check (against bodies only) fails, shouldn't we fall back 			to macro
    //navigation?  Like so:
    if (!(frameNavInfo.flags &
          NIF_MACRO_NAV)) { // we had a clear path to goal and didn't try macro
                            // nav, but can't avoid collision so try macro nav
                            // here
      // See if we're just stuck
      if (NAV_MoveToGoal(NPCS.NPC, &frameNavInfo) == WAYPOINT_NONE) {
        // Can't reach goal, just face
        vectoangles(frameNavInfo.direction, angles);
        NPCS.NPCInfo->desiredYaw = AngleNormalize360(angles[YAW]);
        VectorCopy(frameNavInfo.direction, out);
        *distance = frameNavInfo.distance;
        return qfalse;
      }

      frameNavInfo.flags |= NIF_MACRO_NAV;
    }
  }

  // Setup the return values
  VectorCopy(frameNavInfo.direction, out);
  *distance = frameNavInfo.distance;

  return qtrue;
}

/*
-------------------------
NPC_GetMoveDirectionAltRoute
-------------------------
*/
extern int NAVNEW_MoveToGoal(gentity_t *self, navInfo_t *info);
extern qboolean NAVNEW_AvoidCollision(gentity_t *self, gentity_t *goal,
                                      navInfo_t *info, qboolean setBlockedInfo,
                                      int blockedMovesLimit);
qboolean NPC_GetMoveDirectionAltRoute(vec3_t out, float *distance,
                                      qboolean tryStraight) {
  vec3_t angles;

  NPCS.NPCInfo->aiFlags &= ~NPCAI_BLOCKED;

  // Clear the struct
  memset(&frameNavInfo, 0, sizeof(frameNavInfo));

  // Get our movement, if any
  if (NPC_GetMoveInformation(frameNavInfo.direction, &frameNavInfo.distance) ==
      qfalse)
    return qfalse;

  // Setup the return value
  *distance = frameNavInfo.distance;

  // For starters
  VectorCopy(frameNavInfo.direction, frameNavInfo.pathDirection);

  // If on a ladder, move appropriately
  if (NPCS.NPC->watertype & CONTENTS_LADDER) {
    NPC_LadderMove(frameNavInfo.direction);
    return qtrue;
  }

  // Attempt a straight move to goal
  if (!tryStraight ||
      NPC_ClearPathToGoal(frameNavInfo.direction, NPCS.NPCInfo->goalEntity) ==
          qfalse) { // blocked
    // Can't get straight to goal, use macro nav
    if (NAVNEW_MoveToGoal(NPCS.NPC, &frameNavInfo) == WAYPOINT_NONE) {
      // Can't reach goal, just face
      vectoangles(frameNavInfo.direction, angles);
      NPCS.NPCInfo->desiredYaw = AngleNormalize360(angles[YAW]);
      VectorCopy(frameNavInfo.direction, out);
      *distance = frameNavInfo.distance;
      return qfalse;
    }
    // else we are on our way
    frameNavInfo.flags |= NIF_MACRO_NAV;
  } else { // we have no architectural problems, see if there are ents inthe way
           // and try to go around them
    // not blocked
    if (d_altRoutes.integer) { // try macro nav
      navInfo_t tempInfo;
      memcpy(&tempInfo, &frameNavInfo, sizeof(tempInfo));
      if (NAVNEW_AvoidCollision(NPCS.NPC, NPCS.NPCInfo->goalEntity, &tempInfo,
                                qtrue, 5) == qfalse) { // revert to macro nav
        // Can't get straight to goal, dump tempInfo and use macro nav
        if (NAVNEW_MoveToGoal(NPCS.NPC, &frameNavInfo) == WAYPOINT_NONE) {
          // Can't reach goal, just face
          vectoangles(frameNavInfo.direction, angles);
          NPCS.NPCInfo->desiredYaw = AngleNormalize360(angles[YAW]);
          VectorCopy(frameNavInfo.direction, out);
          *distance = frameNavInfo.distance;
          return qfalse;
        }
        // else we are on our way
        frameNavInfo.flags |= NIF_MACRO_NAV;
      } else { // otherwise, either clear or can avoid
        memcpy(&frameNavInfo, &tempInfo, sizeof(frameNavInfo));
      }
    } else { // OR: just give up
      if (NAVNEW_AvoidCollision(NPCS.NPC, NPCS.NPCInfo->goalEntity,
                                &frameNavInfo, qtrue,
                                30) == qfalse) { // give up
        return qfalse;
      }
    }
  }

  // Setup the return values
  VectorCopy(frameNavInfo.direction, out);
  *distance = frameNavInfo.distance;

  return qtrue;
}

void G_UcmdMoveForDir(gentity_t *self, usercmd_t *cmd, vec3_t dir) {
  vec3_t forward, right;
  float fDot, rDot;

  AngleVectors(self->r.currentAngles, forward, right, NULL);

  dir[2] = 0;
  VectorNormalize(dir);
  // NPCs cheat and store this directly because converting movement into a ucmd
  // loses precision
  VectorCopy(dir, self->client->ps.moveDir);

  fDot = DotProduct(forward, dir) * 127.0f;
  rDot = DotProduct(right, dir) * 127.0f;
  // Must clamp this because DotProduct is not guaranteed to return a number
  // within -1 to 1, and that would be bad when we're shoving this into a signed
  // byte
  if (fDot > 127.0f) {
    fDot = 127.0f;
  }
  if (fDot < -127.0f) {
    fDot = -127.0f;
  }
  if (rDot > 127.0f) {
    rDot = 127.0f;
  }
  if (rDot < -127.0f) {
    rDot = -127.0f;
  }
  cmd->forwardmove = floor(fDot);
  cmd->rightmove = floor(rDot);

  /*
  vec3_t	wishvel;
  for ( int i = 0 ; i < 3 ; i++ )
  {
          wishvel[i] = forward[i]*cmd->forwardmove + right[i]*cmd->rightmove;
  }
  VectorNormalize( wishvel );
  if ( !VectorCompare( wishvel, dir ) )
  {
          Com_Printf( "PRECISION LOSS: %s != %s\n", vtos(wishvel), vtos(dir) );
  }
  */
}

/*
-------------------------
NPC_MoveToGoal

  Now assumes goal is goalEntity, was no reason for it to be otherwise
-------------------------
*/
#if AI_TIMERS
extern int navTime;
#endif //	AI_TIMERS
qboolean NPC_MoveToGoal(qboolean tryStraight) {
  float distance;
  vec3_t dir;

#if AI_TIMERS
  int startTime = GetTime(0);
#endif //	AI_TIMERS
       // If taking full body pain, don't move
  if (PM_InKnockDown(&NPCS.NPC->client->ps) ||
      ((NPCS.NPC->s.legsAnim >= BOTH_PAIN1) &&
       (NPCS.NPC->s.legsAnim <= BOTH_PAIN18))) {
    return qtrue;
  }

  /*
  if( NPC->s.eFlags & EF_LOCKED_TO_WEAPON )
  {//If in an emplaced gun, never try to navigate!
          return qtrue;
  }
  */
  // rwwFIXMEFIXME: emplaced support

  // FIXME: if can't get to goal & goal is a target (enemy), try to find a
  // waypoint that has line of sight to target, at least? Get our movement
  // direction
#if 1
  if (NPC_GetMoveDirectionAltRoute(dir, &distance, tryStraight) == qfalse)
#else
  if (NPC_GetMoveDirection(dir, &distance) == qfalse)
#endif
    return qfalse;

  NPCS.NPCInfo->distToGoal = distance;

  // Convert the move to angles
  vectoangles(dir, NPCS.NPCInfo->lastPathAngles);
  if ((NPCS.ucmd.buttons & BUTTON_WALKING)) {
    NPCS.NPC->client->ps.speed = NPCS.NPCInfo->stats.walkSpeed;
  } else {
    NPCS.NPC->client->ps.speed = NPCS.NPCInfo->stats.runSpeed;
  }

  // FIXME: still getting ping-ponging in certain cases... !!!  Nav/avoidance
  // error?  WTF???!!! If in combat move, then move directly towards our goal
  if (NPC_CheckCombatMove()) { // keep current facing
    G_UcmdMoveForDir(NPCS.NPC, &NPCS.ucmd, dir);
  } else { // face our goal
    // FIXME: strafe instead of turn if change in dir is small and temporary
    NPCS.NPCInfo->desiredPitch = 0.0f;
    NPCS.NPCInfo->desiredYaw =
        AngleNormalize360(NPCS.NPCInfo->lastPathAngles[YAW]);

    // Pitch towards the goal and also update if flying or swimming
    if ((NPCS.NPC->client->ps.eFlags2 & EF2_FLYING)) // moveType == MT_FLYSWIM )
    {
      NPCS.NPCInfo->desiredPitch =
          AngleNormalize360(NPCS.NPCInfo->lastPathAngles[PITCH]);

      if (dir[2]) {
        float scale = (dir[2] * distance);
        if (scale > 64) {
          scale = 64;
        } else if (scale < -64) {
          scale = -64;
        }
        NPCS.NPC->client->ps.velocity[2] = scale;
        // NPC->client->ps.velocity[2] = (dir[2] > 0) ? 64 : -64;
      }
    }

    // Set any final info
    NPCS.ucmd.forwardmove = 127;
  }

#if AI_TIMERS
  navTime += GetTime(startTime);
#endif //	AI_TIMERS
  return qtrue;
}

/*
-------------------------
void NPC_SlideMoveToGoal( void )

  Now assumes goal is goalEntity, if want to use tempGoal, you set that before
calling the func
-------------------------
*/
qboolean NPC_SlideMoveToGoal(void) {
  float saveYaw = NPCS.NPC->client->ps.viewangles[YAW];
  qboolean ret;

  NPCS.NPCInfo->combatMove = qtrue;

  ret = NPC_MoveToGoal(qtrue);

  NPCS.NPCInfo->desiredYaw = saveYaw;

  return ret;
}

/*
-------------------------
NPC_ApplyRoff
-------------------------
*/

void NPC_ApplyRoff(void) {
  BG_PlayerStateToEntityState(&NPCS.NPC->client->ps, &NPCS.NPC->s, qfalse);
  // VectorCopy ( NPC->r.currentOrigin, NPC->lastOrigin );
  // rwwFIXMEFIXME: Any significance to this?

  // use the precise origin for linking
  trap->LinkEntity((sharedEntity_t *)NPCS.NPC);
}
