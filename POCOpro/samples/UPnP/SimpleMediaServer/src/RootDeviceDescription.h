//
// RootDeviceDescription.h
//
// This file has been generated from RootDeviceDescription.cpsp.
//


#ifndef RootDeviceDescription_INCLUDED
#define RootDeviceDescription_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class RootDeviceDescription: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // RootDeviceDescription_INCLUDED
