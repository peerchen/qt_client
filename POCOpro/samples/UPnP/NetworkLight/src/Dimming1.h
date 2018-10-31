//
// Dimming1.h
//
// This file has been generated from Dimming1.cpsp on 2011-03-30 10:20:09.
//


#ifndef Dimming1_INCLUDED
#define Dimming1_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class Dimming1: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Dimming1_INCLUDED
