/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2006 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef COMMON_SCUMMSYS_H
#define COMMON_SCUMMSYS_H

#if !defined(_STDAFX_H) && !defined(__PLAYSTATION2__)
#error Included scummsys.h without including stdafx.h first!
#endif

#include <stdlib.h>
#include <stdio.h>

// Use config.h, generated by configure
#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

// make sure we really are compiling for WIN32
#ifndef WIN32
#undef _MSC_VER
#endif


// In the following we configure various targets, in particular those
// which can't use our "configure" tool and hence don't use config.h.
//
// Some #defines that occur here frequently:
// SCUMM_LITTLE_ENDIAN
//    - Define this on a little endian target
// SCUMM_BIG_ENDIAN
//    - Define this on a big endian target
// SCUMM_NEED_ALIGNMENT
//    - Define this if your system has problems reading e.g. an int32 from an odd address
// SCUMMVM_USE_LONG_INT
//    - Define this if your port needs to use 'long' for the int32 datatype
//      (i.e. an integer with exactly 32 bits).
// SCUMMVM_DONT_DEFINE_TYPES
//    - Define this if you need to provide your own typedefs, e.g. because your
//      system headers conflict with our typenames, or because you have odd
//      type requirements.
// SMALL_SCREEN_DEVICE
//    - ...
// ...

// We define all types in config.h, so we don't want to typedef those types
// here again!
#ifdef HAVE_CONFIG_H
#define SCUMMVM_DONT_DEFINE_TYPES
#endif


#if defined(_MSC_VER) && !defined(__SYMBIAN32__)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp _strnicmp
	#define snprintf _snprintf

	#define SCUMM_LITTLE_ENDIAN

	// FIXME: Do you really need to use 'long' on this port? Please replace
	// this comment with a new comment that states so, and ideally also
	// explains the reasons briefly.
	#define SCUMMVM_USE_LONG_INT

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

	#if defined(CHECK_HEAP)
	#undef CHECK_HEAP
	#define CHECK_HEAP checkHeap();
	#endif

	#define FORCEINLINE __forceinline
	#define NORETURN _declspec(noreturn)
	#define PLUGIN_EXPORT __declspec(dllexport)

	#if defined(_WIN32_WCE) && _WIN32_WCE < 300
	#define CDECL __cdecl
	#define SMALL_SCREEN_DEVICE
	#endif

	typedef signed char int8_t;
	typedef signed short int16_t;
	typedef signed long int32_t;
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned long uint32_t;

#elif defined(__MINGW32__)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp strnicmp

	#define SCUMM_LITTLE_ENDIAN

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

	#define PLUGIN_EXPORT __declspec(dllexport)

	#ifndef _HEAPOK
	#define _HEAPOK	(-2)
	#endif

#elif defined(UNIX)

	#define scumm_stricmp strcasecmp
	#define scumm_strnicmp strncasecmp

	#ifndef CONFIG_H
		#ifdef X11_BACKEND
	
		// You need to set this manually if necessary
	//	#define SCUMM_LITTLE_ENDIAN
		
		#else
		/* need this for the SDL_BYTEORDER define */
		#include <SDL_byteorder.h>
	
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		#define SCUMM_LITTLE_ENDIAN
		#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
		#define SCUMM_BIG_ENDIAN
		#else
		#error Neither SDL_BIG_ENDIAN nor SDL_LIL_ENDIAN is set.
		#endif
		#endif
	#endif

	// You need to set this manually if necessary
//	#define SCUMM_NEED_ALIGNMENT

	#if defined(__DECCXX) // Assume alpha architecture
	#define INVERSE_MKID
	#define SCUMM_NEED_ALIGNMENT
	#endif

	#if !defined(__GNUC__)
	#define START_PACK_STRUCTS pack (1)
	#define END_PACK_STRUCTS   pack ()
	#endif

#elif defined(__PALMOS_TRAPS__)	|| defined (__PALMOS_ARMLET__)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp strnicmp

	#ifdef PALMOS_68K
	#define SCUMM_BIG_ENDIAN
	#else
	#define SCUMM_LITTLE_ENDIAN
	#endif

	#define SCUMM_NEED_ALIGNMENT

	// FIXME: Do you really need to use 'long' on this port? Please replace
	// this comment with a new comment that states so, and ideally also
	// explains the reasons briefly.
	#define SCUMMVM_USE_LONG_INT

	#define START_PACK_STRUCTS pack (1)
	#define END_PACK_STRUCTS   pack ()

	#include "palmversion.h"
	#include "globals.h"
	#include "extend.h"
	
	#define STRINGBUFLEN 256

	#if !defined(COMPILE_ZODIAC) && !defined(COMPILE_OS5)
	#define NEWGUI_256
	#else
	#undef UNUSED
	#endif

#elif defined(__MORPHOS__)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp strnicmp

	#define SCUMM_BIG_ENDIAN
	#define SCUMM_NEED_ALIGNMENT

	// FIXME: Do you really need to use 'long' on this port? Please replace
	// this comment with a new comment that states so, and ideally also
	// explains the reasons briefly.
	#define SCUMMVM_USE_LONG_INT

	#if !defined(__GNUC__)
		#define START_PACK_STRUCTS pack (1)
		#define END_PACK_STRUCTS   pack ()
	#endif

#elif defined(__DC__)

	#define scumm_stricmp strcasecmp
	#define scumm_strnicmp strncasecmp

	#define SCUMM_LITTLE_ENDIAN
	#define SCUMM_NEED_ALIGNMENT

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

#elif defined(__GP32__)

	#define scumm_stricmp stricmp
	#define scumm_strnicmp strnicmp

	#define SCUMM_LITTLE_ENDIAN 
	#define SCUMM_NEED_ALIGNMENT

	// FIXME: Do you really need to use 'long' on this port? Please replace
	// this comment with a new comment that states so, and ideally also
	// explains the reasons briefly.
	#define SCUMMVM_USE_LONG_INT

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

#elif defined(__PLAYSTATION2__)

	#define scumm_stricmp strcasecmp
	#define scumm_strnicmp strncasecmp

	#define SCUMM_LITTLE_ENDIAN 
	#define SCUMM_NEED_ALIGNMENT

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

	#include "backends/ps2/fileio.h"

	#define fopen(a, b)			ps2_fopen(a, b)
	#define fclose(a)			ps2_fclose(a)
	#define fflush(a)			ps2_fflush(a)
	#define fseek(a, b, c)		ps2_fseek(a, b, c)
	#define ftell(a)			ps2_ftell(a)
	#define feof(a)				ps2_feof(a)
	#define fread(a, b, c, d)	ps2_fread(a, b, c, d)
	#define fwrite(a, b, c, d)	ps2_fwrite(a, b, c, d)
	#define fgetc(a)			ps2_fgetc(a)
	#define fgets(a, b, c)		ps2_fgets(a, b, c)
	#define fputc(a, b)			ps2_fputc(a, b)
	#define fputs(a, b)			ps2_fputs(a, b)
	#define fprintf				ps2_fprintf
	#define fsize(a)			ps2_fsize(a)

#elif defined(__PSP__)

	#define scumm_stricmp strcasecmp
	#define scumm_strnicmp strncasecmp

	#define	SCUMM_LITTLE_ENDIAN
	#define	SCUMM_NEED_ALIGNMENT

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

#elif defined(__amigaos4__)

	#define	scumm_stricmp strcasecmp
	#define	scumm_strnicmp strncasecmp

	#define	SCUMM_BIG_ENDIAN
	#define	SCUMM_NEED_ALIGNMENT

	// FIXME: Why is this here? If it does declare types int8 etc., and they
	// are not compatible with our typedefs below, we need a proper fix.
	// In general, though, you should avoid port specific includes in this
	// header file, if possible.
	#include <exec/types.h>

#elif defined(__SYMBIAN32__)

	#define scumm_stricmp strcasecmp
	#define scumm_strnicmp strncasecmp

	#define SCUMM_LITTLE_ENDIAN	
	#define SCUMM_NEED_ALIGNMENT
	#define SCUMMVM_DONT_DEFINE_TYPES

	#define START_PACK_STRUCTS pack(push, 1)
	#define END_PACK_STRUCTS   pack(pop)

	#define SMALL_SCREEN_DEVICE

	typedef unsigned char byte;

	typedef unsigned char uint8;
	typedef signed char int8;

	typedef unsigned short int uint16;
	typedef signed short int int16;

	typedef unsigned long int uint32;
	typedef signed long int int32;

#else

	#error No system type defined

#endif


//
// GCC specific stuff
//
#if defined(__GNUC__)
	#define GCC_PACK __attribute__((packed))
	#define NORETURN __attribute__((__noreturn__)) 
	#define GCC_PRINTF(x,y) __attribute__((format(printf, x, y)))
#else
	#define GCC_PACK
	#define GCC_PRINTF(x,y)
#endif


//
// Fallbacks / default values for various special macros
//
#ifndef START_PACK_STRUCTS
#define	START_PACK_STRUCTS
#define	END_PACK_STRUCTS
#endif

#ifndef FORCEINLINE
#define FORCEINLINE inline
#endif

#ifndef CHECK_HEAP
#define CHECK_HEAP
#endif

#ifndef CDECL
#define	CDECL
#endif

#ifndef PLUGIN_EXPORT
#define PLUGIN_EXPORT
#endif

#ifndef NORETURN
#define	NORETURN
#endif

#ifndef STRINGBUFLEN
#define STRINGBUFLEN 1024
#endif

#ifndef PI
#define PI 3.14159265358979323846
#endif


//
// Typedef our system types unless SCUMMVM_DONT_DEFINE_TYPES is set.
//
#ifndef SCUMMVM_DONT_DEFINE_TYPES
	typedef unsigned char byte;

	typedef unsigned char uint8;
	typedef signed char int8;

	typedef unsigned short uint16;
	typedef signed short int16;

	#ifdef SCUMMVM_USE_LONG_INT
	typedef unsigned long uint32;
	typedef signed long int32;
	typedef unsigned long uint;
	#else
	typedef unsigned int uint32;
	typedef signed int int32;
	typedef unsigned int uint;
	#endif
#endif


//
// Overlay color type (FIXME: shouldn't be declared here)
//
#if defined(NEWGUI_256)
	// 256 color only on PalmOS
	typedef byte OverlayColor;
#else
	// 15/16 bit color mode everywhere else...
	typedef int16 OverlayColor;
#endif


#endif
