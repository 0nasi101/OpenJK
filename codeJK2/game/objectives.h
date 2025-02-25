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

#ifndef __OBJECTIVES_H__
#define __OBJECTIVES_H__

// mission Objectives

// DO NOT CHANGE MAX_MISSION_OBJ. IT AFFECTS THE SAVEGAME STRUCTURE

typedef enum //# Objective_e
{
  //=================================================
  //
  //=================================================
  KEJIM_POST_OBJ1 = 0,   //# KEJIM POST
  KEJIM_POST_OBJ2,       //# KEJIM POST
  KEJIM_BASE_OBJ1,       //# KEJIM BASE
  KEJIM_BASE_OBJ2,       //# KEJIM BASE
  KEJIM_BASE_OBJ3,       //# KEJIM BASE
  ARTUS_MINE_OBJ1,       //# ARTUS MINE
  ARTUS_MINE_OBJ2,       //# ARTUS MINE
  ARTUS_MINE_OBJ3,       //# ARTUS MINE
  ARTUS_DETENTION_OBJ1,  //# ARTUS DETENTION
  ARTUS_DETENTION_OBJ2,  //# ARTUS DETENTION
  ARTUS_TOPSIDE_OBJ1,    //# ARTUS TOPSIDE
  ARTUS_TOPSIDE_OBJ2,    //# ARTUS TOPSIDE
  YAVIN_TEMPLE_OBJ1,     //# YAVIN TEMPLE
  YAVIN_TRIAL_OBJ1,      //# YAVIN TRIAL
  YAVIN_TRIAL_OBJ2,      //# YAVIN TRIAL
  NS_STREETS_OBJ1,       //# NS STREETS
  NS_STREETS_OBJ2,       //# NS STREETS
  NS_STREETS_OBJ3,       //# NS STREETS
  NS_HIDEOUT_OBJ1,       //# NS HIDEOUT
  NS_HIDEOUT_OBJ2,       //# NS HIDEOUT
  NS_STARPAD_OBJ1,       //# NS STARPAD
  NS_STARPAD_OBJ2,       //# NS STARPAD
  NS_STARPAD_OBJ3,       //# NS STARPAD
  NS_STARPAD_OBJ4,       //# NS STARPAD
  NS_STARPAD_OBJ5,       //# NS STARPAD
  BESPIN_UNDERCITY_OBJ1, //# BESPIN UNDERCITY
  BESPIN_UNDERCITY_OBJ2, //# BESPIN UNDERCITY
  BESPIN_STREETS_OBJ1,   //# BESPIN STREETS
  BESPIN_STREETS_OBJ2,   //# BESPIN STREETS
  BESPIN_PLATFORM_OBJ1,  //# BESPIN PLATFORM
  BESPIN_PLATFORM_OBJ2,  //# BESPIN PLATFORM
  CAIRN_BAY_OBJ1,        //# CAIRN BAY
  CAIRN_BAY_OBJ2,        //# CAIRN BAY
  CAIRN_ASSEMBLY_OBJ1,   //# CAIRN ASSEMBLY
  CAIRN_REACTOR_OBJ1,    //# CAIRN REACTOR
  CAIRN_REACTOR_OBJ2,    //# CAIRN REACTOR
  CAIRN_DOCK1_OBJ1,      //# CAIRN DOCK1
  CAIRN_DOCK1_OBJ2,      //# CAIRN DOCK1
  DOOM_COMM_OBJ1,        //# DOOM COMM
  DOOM_COMM_OBJ2,        //# DOOM COMM
  DOOM_COMM_OBJ3,        //# DOOM COMM
  DOOM_DETENTION_OBJ1,   //# DOOM DETENTION
  DOOM_DETENTION_OBJ2,   //# DOOM DETENTION
  DOOM_SHIELDS_OBJ1,     //# DOOM SHIELDS
  DOOM_SHIELDS_OBJ2,     //# DOOM SHIELDS
  YAVIN_SWAMP_OBJ1,      //# YAVIN SWAMP
  YAVIN_SWAMP_OBJ2,      //# YAVIN SWAMP
  YAVIN_CANYON_OBJ1,     //# YAVIN CANYON
  YAVIN_CANYON_OBJ2,     //# YAVIN CANYON
  YAVIN_COURTYARD_OBJ1,  //# YAVIN COURTYARD
  YAVIN_COURTYARD_OBJ2,  //# YAVIN COURTYARD
  YAVIN_FINAL_OBJ1,      //# YAVIN FINAL
  KEJIM_POST_OBJ3,       //# KEJIM POST - GRAPHICS IN IT.
  KEJIM_POST_OBJ4,       //# KEJIM POST - GRAPHICS IN IT.
  KEJIM_POST_OBJ5,       //# KEJIM POST - GRAPHICS IN IT.
  ARTUS_DETENTION_OBJ3,  //# ARTUS DETENTION
  DOOM_COMM_OBJ4,        //# DOOM COMM - GRAPHICS IN IT.
  DOOM_SHIELDS_OBJ3,     //# DOOM SHIELDS
  DEMO_OBJ1,             //# DEMO
  DEMO_OBJ2,             //# DEMO
  DEMO_OBJ3,             //# DEMO
  DEMO_OBJ4,             //# DEMO

  //# #eol
  MAX_OBJECTIVES,
} objectiveNumber_t;

typedef enum                       //# MissionFailed_e
{ MISSIONFAILED_JAN = 0,           //#
  MISSIONFAILED_LUKE,              //#
  MISSIONFAILED_LANDO,             //#
  MISSIONFAILED_R5D2,              //#
  MISSIONFAILED_WARDEN,            //#
  MISSIONFAILED_PRISONERS,         //#
  MISSIONFAILED_EMPLACEDGUNS,      //#
  MISSIONFAILED_LADYLUCK,          //#
  MISSIONFAILED_KYLECAPTURE,       //#
  MISSIONFAILED_TOOMANYALLIESDIED, //#
  //# #eol
  MAX_MISSIONFAILED,
} missionFailed_t;

typedef enum //# StatusText_e
{
  //=================================================
  //
  //=================================================
  STAT_INSUBORDINATION = 0, //# Starfleet will not tolerate such insubordination
  STAT_YOUCAUSEDDEATHOFTEAMMATE, //# You caused the death of a teammate.
  STAT_DIDNTPROTECTTECH,  //# You failed to protect Chell, your technician.
  STAT_DIDNTPROTECT7OF9,  //# You failed to protect 7 of 9
  STAT_NOTSTEALTHYENOUGH, //# You weren't quite stealthy enough
  STAT_STEALTHTACTICSNECESSARY, //# Starfleet will not tolerate such
                                //insubordination
  STAT_WATCHYOURSTEP,           //# Watch your step
  STAT_JUDGEMENTMUCHDESIRED,    //# Your judgement leaves much to be desired

  //# #eol
  MAX_STATUSTEXT,
} statusText_t;

extern qboolean missionInfo_Updated;

#define SET_TACTICAL_OFF 0
#define SET_TACTICAL_ON 1

#define SET_OBJ_HIDE 0
#define SET_OBJ_SHOW 1
#define SET_OBJ_PENDING 2
#define SET_OBJ_SUCCEEDED 3
#define SET_OBJ_FAILED 4

#define OBJECTIVE_HIDE 0
#define OBJECTIVE_SHOW 1

#define OBJECTIVE_STAT_PENDING 0
#define OBJECTIVE_STAT_SUCCEEDED 1
#define OBJECTIVE_STAT_FAILED 2

extern int statusTextIndex;

void OBJ_SaveObjectiveData(void);
void OBJ_LoadObjectiveData(void);
extern void OBJ_SetPendingObjectives(gentity_t *ent);

#ifndef G_OBJECTIVES_CPP

extern stringID_table_t objectiveTable[];
extern stringID_table_t statusTextTable[];
extern stringID_table_t missionFailedTable[];

#else

stringID_table_t objectiveTable[] = {
    //=================================================
    //
    //=================================================
    ENUM2STRING(KEJIM_POST_OBJ1),       //# KEJIM POST
    ENUM2STRING(KEJIM_POST_OBJ2),       //# KEJIM POST
    ENUM2STRING(KEJIM_BASE_OBJ1),       //# KEJIM BASE
    ENUM2STRING(KEJIM_BASE_OBJ2),       //# KEJIM BASE
    ENUM2STRING(KEJIM_BASE_OBJ3),       //# KEJIM BASE
    ENUM2STRING(ARTUS_MINE_OBJ1),       //# ARTUS MINE
    ENUM2STRING(ARTUS_MINE_OBJ2),       //# ARTUS MINE
    ENUM2STRING(ARTUS_MINE_OBJ3),       //# ARTUS MINE
    ENUM2STRING(ARTUS_DETENTION_OBJ1),  //# ARTUS DETENTION
    ENUM2STRING(ARTUS_DETENTION_OBJ2),  //# ARTUS DETENTION
    ENUM2STRING(ARTUS_TOPSIDE_OBJ1),    //# ARTUS TOPSIDE
    ENUM2STRING(ARTUS_TOPSIDE_OBJ2),    //# ARTUS TOPSIDE
    ENUM2STRING(YAVIN_TEMPLE_OBJ1),     //# YAVIN TEMPLE
    ENUM2STRING(YAVIN_TRIAL_OBJ1),      //# YAVIN TRIAL
    ENUM2STRING(YAVIN_TRIAL_OBJ2),      //# YAVIN TRIAL
    ENUM2STRING(NS_STREETS_OBJ1),       //# NS STREETS
    ENUM2STRING(NS_STREETS_OBJ2),       //# NS STREETS
    ENUM2STRING(NS_STREETS_OBJ3),       //# NS STREETS
    ENUM2STRING(NS_HIDEOUT_OBJ1),       //# NS HIDEOUT
    ENUM2STRING(NS_HIDEOUT_OBJ2),       //# NS HIDEOUT
    ENUM2STRING(NS_STARPAD_OBJ1),       //# NS STARPAD
    ENUM2STRING(NS_STARPAD_OBJ2),       //# NS STARPAD
    ENUM2STRING(NS_STARPAD_OBJ3),       //# NS STARPAD
    ENUM2STRING(NS_STARPAD_OBJ4),       //# NS STARPAD
    ENUM2STRING(NS_STARPAD_OBJ5),       //# NS STARPAD
    ENUM2STRING(BESPIN_UNDERCITY_OBJ1), //# BESPIN UNDERCITY
    ENUM2STRING(BESPIN_UNDERCITY_OBJ2), //# BESPIN UNDERCITY
    ENUM2STRING(BESPIN_STREETS_OBJ1),   //# BESPIN STREETS
    ENUM2STRING(BESPIN_STREETS_OBJ2),   //# BESPIN STREETS
    ENUM2STRING(BESPIN_PLATFORM_OBJ1),  //# BESPIN PLATFORM
    ENUM2STRING(BESPIN_PLATFORM_OBJ2),  //# BESPIN PLATFORM
    ENUM2STRING(CAIRN_BAY_OBJ1),        //# CAIRN BAY
    ENUM2STRING(CAIRN_BAY_OBJ2),        //# CAIRN BAY
    ENUM2STRING(CAIRN_ASSEMBLY_OBJ1),   //# CAIRN ASSEMBLY
    ENUM2STRING(CAIRN_REACTOR_OBJ1),    //# CAIRN REACTOR
    ENUM2STRING(CAIRN_REACTOR_OBJ2),    //# CAIRN REACTOR
    ENUM2STRING(CAIRN_DOCK1_OBJ1),      //# CAIRN DOCK1
    ENUM2STRING(CAIRN_DOCK1_OBJ2),      //# CAIRN DOCK1
    ENUM2STRING(DOOM_COMM_OBJ1),        //# DOOM COMM
    ENUM2STRING(DOOM_COMM_OBJ2),        //# DOOM COMM
    ENUM2STRING(DOOM_COMM_OBJ3),        //# DOOM COMM
    ENUM2STRING(DOOM_DETENTION_OBJ1),   //# DOOM DETENTION
    ENUM2STRING(DOOM_DETENTION_OBJ2),   //# DOOM DETENTION
    ENUM2STRING(DOOM_SHIELDS_OBJ1),     //# DOOM SHIELDS
    ENUM2STRING(DOOM_SHIELDS_OBJ2),     //# DOOM SHIELDS
    ENUM2STRING(YAVIN_SWAMP_OBJ1),      //# YAVIN SWAMP
    ENUM2STRING(YAVIN_SWAMP_OBJ2),      //# YAVIN SWAMP
    ENUM2STRING(YAVIN_CANYON_OBJ1),     //# YAVIN CANYON
    ENUM2STRING(YAVIN_CANYON_OBJ2),     //# YAVIN CANYON
    ENUM2STRING(YAVIN_COURTYARD_OBJ1),  //# YAVIN COURTYARD
    ENUM2STRING(YAVIN_COURTYARD_OBJ2),  //# YAVIN COURTYARD
    ENUM2STRING(YAVIN_FINAL_OBJ1),      //# YAVIN FINAL
    ENUM2STRING(KEJIM_POST_OBJ3),       //# KEJIM POST - GRAPHICS IN IT.
    ENUM2STRING(KEJIM_POST_OBJ4),       //# KEJIM POST - GRAPHICS IN IT.
    ENUM2STRING(KEJIM_POST_OBJ5),       //# KEJIM POST - GRAPHICS IN IT.
    ENUM2STRING(ARTUS_DETENTION_OBJ3),  //# ARTUS DETENTION
    ENUM2STRING(DOOM_COMM_OBJ4), //# DOOM COMM - GRAPHICS IN IT. IT MUST BE LAST
                                 //IN THE LIST
    ENUM2STRING(DOOM_SHIELDS_OBJ3), //# DOOM SHIELDS
    ENUM2STRING(DEMO_OBJ1),         //# DEMO
    ENUM2STRING(DEMO_OBJ2),         //# DEMO
    ENUM2STRING(DEMO_OBJ3),         //# DEMO
    ENUM2STRING(DEMO_OBJ4),         //# DEMO

    // stringID_table_t Must end with a null entry
    {"", 0}};

stringID_table_t missionFailedTable[] = {
    ENUM2STRING(MISSIONFAILED_JAN),               //# JAN DIED
    ENUM2STRING(MISSIONFAILED_LUKE),              //# LUKE DIED
    ENUM2STRING(MISSIONFAILED_LANDO),             //# LANDO DIED
    ENUM2STRING(MISSIONFAILED_R5D2),              //# R5D2 DIED
    ENUM2STRING(MISSIONFAILED_WARDEN),            //# THE WARDEN DIED
    ENUM2STRING(MISSIONFAILED_PRISONERS),         //#	TOO MANY PRISONERS DIED
    ENUM2STRING(MISSIONFAILED_EMPLACEDGUNS),      //#	ALL EMPLACED GUNS GONE
    ENUM2STRING(MISSIONFAILED_LADYLUCK),          //#	LADY LUCK DISTROYED
    ENUM2STRING(MISSIONFAILED_KYLECAPTURE),       //# KYLE HAS BEEN CAPTURED
    ENUM2STRING(MISSIONFAILED_TOOMANYALLIESDIED), //# TOO MANY ALLIES DIED

    // stringID_table_t Must end with a null entry
    {"", 0}};

stringID_table_t statusTextTable[] = {
    //=================================================
    //
    //=================================================
    ENUM2STRING(STAT_INSUBORDINATION), //# Starfleet will not tolerate such
                                       //insubordination
    ENUM2STRING(
        STAT_YOUCAUSEDDEATHOFTEAMMATE),  //# You caused the death of a teammate.
    ENUM2STRING(STAT_DIDNTPROTECTTECH),  //# You failed to protect Chell, your
                                         //technician.
    ENUM2STRING(STAT_DIDNTPROTECT7OF9),  //# You failed to protect 7 of 9
    ENUM2STRING(STAT_NOTSTEALTHYENOUGH), //# You weren't quite stealthy enough
    ENUM2STRING(STAT_STEALTHTACTICSNECESSARY), //# Starfleet will not tolerate
                                               //such insubordination
    ENUM2STRING(STAT_WATCHYOURSTEP),           //# Watch your step
    ENUM2STRING(STAT_JUDGEMENTMUCHDESIRED), //# Your judgement leaves much to be
                                            //desired stringID_table_t Must end
                                            // with a null entry
    {"", 0}};

#endif // #ifndef G_OBJECTIVES_CPP

#endif // #ifndef __OBJECTIVES_H__
