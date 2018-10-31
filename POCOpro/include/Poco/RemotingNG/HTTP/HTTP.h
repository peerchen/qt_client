//
// HTTP.h
//
// $Id: //poco/1.7/RemotingNG/HTTP/include/Poco/RemotingNG/HTTP/HTTP.h#1 $
//
// Library: RemotingNG/HTTP
// Package: HTTP
// Module:  HTTP
//
// Basic definitions for the Poco RemotingNG HTTP library.
// This file must be the first file included by every other HTTP
// header file.
//
// Copyright (c) 2010-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_HTTP_HTTP_INCLUDED
#define RemotingNG_HTTP_HTTP_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Poco/Foundation.h"
#endif


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RemotingNGHTTP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RemotingNGHTTP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(RemotingNGHTTP_EXPORTS)
		#define RemotingNGHTTP_API __declspec(dllexport)
	#else
		#define RemotingNGHTTP_API __declspec(dllimport)
	#endif
#endif


#if !defined(RemotingNGHTTP_API)
	#define RemotingNGHTTP_API
#endif


//
// Automatically link JSON library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(RemotingNGHTTP_EXPORTS)
		#pragma comment(lib, "PocoRemotingNGHTTP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // RemotingNG_HTTP_HTTP_INCLUDED
