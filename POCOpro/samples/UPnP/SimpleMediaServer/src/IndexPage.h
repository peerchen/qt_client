//
// IndexPage.h
//
// This file has been generated from IndexPage.cpsp on 2011-07-17 12:13:14.
//


#ifndef IndexPage_INCLUDED
#define IndexPage_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class IndexPage: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // IndexPage_INCLUDED
