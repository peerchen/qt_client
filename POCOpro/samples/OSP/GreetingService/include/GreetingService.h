//
// GreetingService.cpp
//
// $Id: //poco/1.7/OSP/samples/GreetingService/include/GreetingService.h#1 $
//
// Definition of the GreetingService class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef GreetingService_INCLUDED
#define GreetingService_INCLUDED


#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"


class GreetingService: public Poco::OSP::Service
	/// This is an example for a very simple
	/// OSP service.
	///
	/// The service is available under the name
	/// "com.appinf.osp.samples.GreetingService".
{
public:
	typedef Poco::AutoPtr<GreetingService> Ptr;

	virtual std::string greeting() = 0;
		/// Return a greeting in the user's language, if the
		/// language is known, or in English otherwise.
};


#endif // GreetingService_INCLUDED
