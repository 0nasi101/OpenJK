/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
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

/*****************************************************************************
 * name:		l_libvar.c
 *
 * desc:		bot library variables
 *
 * $Archive: /MissionPack/code/botlib/l_libvar.c $
 * $Author: Zaphod $
 * $Revision: 2 $
 * $Modtime: 11/21/00 11:33a $
 * $Date: 11/21/00 11:49a $
 *
 *****************************************************************************/

#include "l_libvar.h"
#include "l_memory.h"
#include "qcommon/q_shared.h"

// list with library variables
libvar_t *libvarlist = NULL;

//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
float LibVarStringValue(char *string) {
  int dotfound = 0;
  float value = 0;

  while (*string) {
    if (*string < '0' || *string > '9') {
      if (dotfound || *string != '.') {
        return 0;
      } // end if
      else {
        dotfound = 10;
        string++;
      } // end if
    }   // end if
    if (dotfound) {
      value = value + (float)(*string - '0') / (float)dotfound;
      dotfound *= 10;
    } // end if
    else {
      value = value * 10.0 + (float)(*string - '0');
    } // end else
    string++;
  } // end while
  return value;
} // end of the function LibVarStringValue
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
libvar_t *LibVarAlloc(char *var_name) {
  libvar_t *v;

  v = (libvar_t *)GetMemory(sizeof(libvar_t));
  Com_Memset(v, 0, sizeof(libvar_t));
  v->name = (char *)GetMemory(strlen(var_name) + 1);
  strcpy(v->name, var_name);
  // add the variable in the list
  v->next = libvarlist;
  libvarlist = v;
  return v;
} // end of the function LibVarAlloc
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void LibVarDeAlloc(libvar_t *v) {
  if (v->string)
    FreeMemory(v->string);
  FreeMemory(v->name);
  FreeMemory(v);
} // end of the function LibVarDeAlloc
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void LibVarDeAllocAll(void) {
  libvar_t *v;

  for (v = libvarlist; v; v = libvarlist) {
    libvarlist = libvarlist->next;
    LibVarDeAlloc(v);
  } // end for
  libvarlist = NULL;
} // end of the function LibVarDeAllocAll
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
libvar_t *LibVarGet(char *var_name) {
  libvar_t *v;

  for (v = libvarlist; v; v = v->next) {
    if (!Q_stricmp(v->name, var_name)) {
      return v;
    } // end if
  }   // end for
  return NULL;
} // end of the function LibVarGet
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
char *LibVarGetString(char *var_name) {
  libvar_t *v;

  v = LibVarGet(var_name);
  if (v) {
    return v->string;
  } // end if
  else {
    return "";
  } // end else
} // end of the function LibVarGetString
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
float LibVarGetValue(char *var_name) {
  libvar_t *v;

  v = LibVarGet(var_name);
  if (v) {
    return v->value;
  } // end if
  else {
    return 0;
  } // end else
} // end of the function LibVarGetValue
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
libvar_t *LibVar(char *var_name, char *value) {
  libvar_t *v;
  v = LibVarGet(var_name);
  if (v)
    return v;
  // create new variable
  v = LibVarAlloc(var_name);
  // variable string
  v->string = (char *)GetMemory(strlen(value) + 1);
  strcpy(v->string, value);
  // the value
  v->value = LibVarStringValue(v->string);
  // variable is modified
  v->modified = qtrue;
  //
  return v;
} // end of the function LibVar
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
char *LibVarString(char *var_name, char *value) {
  libvar_t *v;

  v = LibVar(var_name, value);
  return v->string;
} // end of the function LibVarString
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
float LibVarValue(char *var_name, char *value) {
  libvar_t *v;

  v = LibVar(var_name, value);
  return v->value;
} // end of the function LibVarValue
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void LibVarSet(char *var_name, char *value) {
  libvar_t *v;

  v = LibVarGet(var_name);
  if (v) {
    FreeMemory(v->string);
  } // end if
  else {
    v = LibVarAlloc(var_name);
  } // end else
  // variable string
  v->string = (char *)GetMemory(strlen(value) + 1);
  strcpy(v->string, value);
  // the value
  v->value = LibVarStringValue(v->string);
  // variable is modified
  v->modified = qtrue;
} // end of the function LibVarSet
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
qboolean LibVarChanged(char *var_name) {
  libvar_t *v;

  v = LibVarGet(var_name);
  if (v) {
    return v->modified;
  } // end if
  else {
    return qfalse;
  } // end else
} // end of the function LibVarChanged
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void LibVarSetNotModified(char *var_name) {
  libvar_t *v;

  v = LibVarGet(var_name);
  if (v) {
    v->modified = qfalse;
  } // end if
} // end of the function LibVarSetNotModified
