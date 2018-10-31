//
// LightingControls1.h
//
// $Id: //poco/1.7/UPnP/samples/LightingControls_1/include/UPnPS/LightingControls1/LightingControls1.h#1 $
//
// Basic definitions for the UPnP LightingControls1 library.
// This file must be the first file included by every other LightingControls1
// header file.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef LightingControls1_INCLUDED
#define LightingControls1_INCLUDED


#include "Poco/UPnP/UPnP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LightingControls1_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LightingControls1_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(LightingControls1_EXPORTS)
		#define LightingControls1_API __declspec(dllexport)
	#else
		#define LightingControls1_API __declspec(dllimport)
	#endif
#endif


#if !defined(LightingControls1_API)
	#define LightingControls1_API
#endif


//
// Automatically link LightingControls1 library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(LightingControls1_EXPORTS)
		#pragma comment(lib, "LightingControls1" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // LightingControls1_INCLUDED
