//
// WANPOTSLinkConfigProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPOTSLinkConfigProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef InternetGateway1_WANPOTSLinkConfigProxy_INCLUDED
#define InternetGateway1_WANPOTSLinkConfigProxy_INCLUDED


#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/IWANPOTSLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPOTSLinkConfigProxy: public UPnPS::InternetGateway1::IWANPOTSLinkConfig, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<WANPOTSLinkConfigProxy> Ptr;

	WANPOTSLinkConfigProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a WANPOTSLinkConfigProxy.

	virtual ~WANPOTSLinkConfigProxy();
		/// Destroys the WANPOTSLinkConfigProxy.

	virtual void getCallRetryInfo(Poco::UInt32& newNumberOfRetries, Poco::UInt32& newDelayBetweenRetries);

	virtual void getDataCompression(std::string& newDataCompression);

	virtual void getDataModulationSupported(std::string& newDataModulationSupported);

	virtual void getDataProtocol(std::string& newDataProtocol);

	virtual void getFclass(std::string& newFclass);

	virtual void getISPInfo(std::string& newISPPhoneNumber, std::string& newISPInfo, std::string& newLinkType);

	virtual void getPlusVTRCommandSupported(bool& newPlusVTRCommandSupported);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setCallRetryInfo(Poco::UInt32 newNumberOfRetries, Poco::UInt32 newDelayBetweenRetries);

	virtual void setISPInfo(const std::string& newISPPhoneNumber, const std::string& newISPInfo, const std::string& newLinkType);

private:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANPOTSLinkConfigProxy::remoting__typeId() const
{
	return IWANPOTSLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPOTSLinkConfigProxy_INCLUDED

