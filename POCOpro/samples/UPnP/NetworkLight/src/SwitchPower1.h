//
// SwitchPower1.h
//
// This file has been generated from SwitchPower1.cpsp on 2011-03-30 10:18:41.
//


#ifndef SwitchPower1_INCLUDED
#define SwitchPower1_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class SwitchPower1: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // SwitchPower1_INCLUDED
