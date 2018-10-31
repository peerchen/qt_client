//
// IWANPOTSLinkConfig.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  IWANPOTSLinkConfig
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


#ifndef InternetGateway1_IWANPOTSLinkConfig_INCLUDED
#define InternetGateway1_IWANPOTSLinkConfig_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANPOTSLinkConfig.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API IWANPOTSLinkConfig: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IWANPOTSLinkConfig> Ptr;

	IWANPOTSLinkConfig();
		/// Creates a IWANPOTSLinkConfig.

	virtual ~IWANPOTSLinkConfig();
		/// Destroys the IWANPOTSLinkConfig.

	virtual void getCallRetryInfo(Poco::UInt32& newNumberOfRetries, Poco::UInt32& newDelayBetweenRetries) = 0;

	virtual void getDataCompression(std::string& newDataCompression) = 0;

	virtual void getDataModulationSupported(std::string& newDataModulationSupported) = 0;

	virtual void getDataProtocol(std::string& newDataProtocol) = 0;

	virtual void getFclass(std::string& newFclass) = 0;

	virtual void getISPInfo(std::string& newISPPhoneNumber, std::string& newISPInfo, std::string& newLinkType) = 0;

	virtual void getPlusVTRCommandSupported(bool& newPlusVTRCommandSupported) = 0;

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setCallRetryInfo(Poco::UInt32 newNumberOfRetries, Poco::UInt32 newDelayBetweenRetries) = 0;

	virtual void setISPInfo(const std::string& newISPPhoneNumber, const std::string& newISPInfo, const std::string& newLinkType) = 0;

};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_IWANPOTSLinkConfig_INCLUDED

