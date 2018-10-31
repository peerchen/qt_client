//
// WANPOTSLinkConfigRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPOTSLinkConfigRemoteObject
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


#ifndef InternetGateway1_WANPOTSLinkConfigRemoteObject_INCLUDED
#define InternetGateway1_WANPOTSLinkConfigRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANPOTSLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPOTSLinkConfigRemoteObject: public UPnPS::InternetGateway1::IWANPOTSLinkConfig, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANPOTSLinkConfigRemoteObject> Ptr;

	WANPOTSLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject);
		/// Creates a WANPOTSLinkConfigRemoteObject.

	virtual ~WANPOTSLinkConfigRemoteObject();
		/// Destroys the WANPOTSLinkConfigRemoteObject.

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
	Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> _pServiceObject;
};


inline void WANPOTSLinkConfigRemoteObject::getCallRetryInfo(Poco::UInt32& newNumberOfRetries, Poco::UInt32& newDelayBetweenRetries)
{
	_pServiceObject->getCallRetryInfo(newNumberOfRetries, newDelayBetweenRetries);
}


inline void WANPOTSLinkConfigRemoteObject::getDataCompression(std::string& newDataCompression)
{
	_pServiceObject->getDataCompression(newDataCompression);
}


inline void WANPOTSLinkConfigRemoteObject::getDataModulationSupported(std::string& newDataModulationSupported)
{
	_pServiceObject->getDataModulationSupported(newDataModulationSupported);
}


inline void WANPOTSLinkConfigRemoteObject::getDataProtocol(std::string& newDataProtocol)
{
	_pServiceObject->getDataProtocol(newDataProtocol);
}


inline void WANPOTSLinkConfigRemoteObject::getFclass(std::string& newFclass)
{
	_pServiceObject->getFclass(newFclass);
}


inline void WANPOTSLinkConfigRemoteObject::getISPInfo(std::string& newISPPhoneNumber, std::string& newISPInfo, std::string& newLinkType)
{
	_pServiceObject->getISPInfo(newISPPhoneNumber, newISPInfo, newLinkType);
}


inline void WANPOTSLinkConfigRemoteObject::getPlusVTRCommandSupported(bool& newPlusVTRCommandSupported)
{
	_pServiceObject->getPlusVTRCommandSupported(newPlusVTRCommandSupported);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANPOTSLinkConfigRemoteObject::remoting__typeId() const
{
	return IWANPOTSLinkConfig::remoting__typeId();
}


inline void WANPOTSLinkConfigRemoteObject::setCallRetryInfo(Poco::UInt32 newNumberOfRetries, Poco::UInt32 newDelayBetweenRetries)
{
	_pServiceObject->setCallRetryInfo(newNumberOfRetries, newDelayBetweenRetries);
}


inline void WANPOTSLinkConfigRemoteObject::setISPInfo(const std::string& newISPPhoneNumber, const std::string& newISPInfo, const std::string& newLinkType)
{
	_pServiceObject->setISPInfo(newISPPhoneNumber, newISPInfo, newLinkType);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPOTSLinkConfigRemoteObject_INCLUDED

