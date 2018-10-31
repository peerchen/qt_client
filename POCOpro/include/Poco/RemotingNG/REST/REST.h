//
// REST.h
//
// $Id: //poco/1.7/RemotingNG/REST/include/Poco/RemotingNG/REST/REST.h#1 $
//
// Library: RemotingNG/REST
// Package: REST
// Module:  REST
//
// Basic definitions for the Poco RemotingNG REST library.
// This file must be the first file included by every other REST
// header file.
//
// Copyright (c) 2010-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_REST_REST_INCLUDED
#define RemotingNG_REST_REST_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Poco/Foundation.h"
#endif


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RemotingNGREST_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RemotingNGREST_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(RemotingNGREST_EXPORTS)
		#define RemotingNGREST_API __declspec(dllexport)
	#else
		#define RemotingNGREST_API __declspec(dllimport)
	#endif
#endif


#if !defined(RemotingNGREST_API)
	#define RemotingNGREST_API
#endif


//
// Automatically link JSON library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(RemotingNGREST_EXPORTS)
		#pragma comment(lib, "PocoRemotingNGREST" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // RemotingNG_REST_REST_INCLUDED
