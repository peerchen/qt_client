//
// MediaServer1.h
//
// $Id: //poco/1.7/UPnP/samples/MediaServer_1/include/UPnPS/MediaServer1/MediaServer1.h#1 $
//
// Basic definitions for the UPnP MediaServer1 library.
// This file must be the first file included by every other MediaServer1
// header file.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef MediaServer1_INCLUDED
#define MediaServer1_INCLUDED


#include "Poco/UPnP/UPnP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MediaServer1_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MediaServer1_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(MediaServer1_EXPORTS)
		#define MediaServer1_API __declspec(dllexport)
	#else
		#define MediaServer1_API __declspec(dllimport)
	#endif
#endif


#if !defined(MediaServer1_API)
	#define MediaServer1_API
#endif


//
// Automatically link MediaServer1 library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(MediaServer1_EXPORTS)
		#pragma comment(lib, "MediaServer1" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // MediaServer1_INCLUDED
