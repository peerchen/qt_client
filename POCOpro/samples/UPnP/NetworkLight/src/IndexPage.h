//
// IndexPage.h
//
// This file has been generated from IndexPage.cpsp on 2011-03-31 07:21:26.
//


#ifndef IndexPage_INCLUDED
#define IndexPage_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


#include "DimmableLight.h"


class IndexPage: public Poco::Net::HTTPRequestHandler
{
public:
	IndexPage(DimmableLight&);

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	DimmableLight& context() const
	{
		return _context;
	}

private:
	DimmableLight& _context;
};


#endif // IndexPage_INCLUDED
