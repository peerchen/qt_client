//
// RESTRequestHandlerFactory.h
//
// $Id: //poco/1.7/RemotingNG/REST/include/Poco/RemotingNG/REST/RESTRequestHandlerFactory.h#1 $
//
// Library: RemotingNG/REST
// Package: REST
// Module:  RESTRequestHandlerFactory
//
// Definition of the RESTRequestHandlerFactory class.
//
// Copyright (c) 2010-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_REST_RESTRequestHandlerFactory_INCLUDED
#define RemotingNG_REST_RESTRequestHandlerFactory_INCLUDED


#include "Poco/RemotingNG/REST/REST.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"


namespace Poco {
namespace RemotingNG {
namespace REST {


class Listener;


class RemotingNGREST_API RESTRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
	/// A factory for RESTRequestHandler objects.
{
public:
	RESTRequestHandlerFactory(Listener& listener);
		/// Creates the RESTRequestHandlerFactory.

	~RESTRequestHandlerFactory();
		/// Destroys the RESTRequestHandlerFactory.

	// Poco::Net::HTTPRequestHandlerFactory
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
	Listener& _listener;
};


} } } // namespace Poco::RemotingNG::REST


#endif // RemotingNG_REST_RESTRequestHandlerFactory_INCLUDED
