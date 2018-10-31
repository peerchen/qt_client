//
// ContentDirectory1.h
//
// This file has been generated from ContentDirectory1.cpsp on 2013-01-04 08:27:17.
//


#ifndef ContentDirectory1_INCLUDED
#define ContentDirectory1_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class ContentDirectory1: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // ContentDirectory1_INCLUDED
