//
// ConnectionManager1.h
//
// This file has been generated from ConnectionManager1.cpsp on 2013-01-04 08:27:17.
//


#ifndef ConnectionManager1_INCLUDED
#define ConnectionManager1_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class ConnectionManager1: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // ConnectionManager1_INCLUDED
