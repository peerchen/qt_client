//
// AVTransport1Proxy.h
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1Proxy
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


#ifndef MediaServer1_AVTransport1Proxy_INCLUDED
#define MediaServer1_AVTransport1Proxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/MediaServer1/IAVTransport1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API AVTransport1Proxy: public UPnPS::MediaServer1::IAVTransport1, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<AVTransport1Proxy> Ptr;

	AVTransport1Proxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a AVTransport1Proxy.

	virtual ~AVTransport1Proxy();
		/// Destroys the AVTransport1Proxy.

	virtual void getCurrentTransportActions(Poco::UInt32 instanceID, std::string& actions);

	virtual void getDeviceCapabilities(Poco::UInt32 instanceID, std::string& playMedia, std::string& recMedia, std::string& recQualityModes);

	virtual void getMediaInfo(Poco::UInt32 instanceID, Poco::UInt32& nrTracks, std::string& mediaDuration, std::string& currentURI, std::string& currentURIMetaData, std::string& nextURI, std::string& nextURIMetaData, std::string& playMedium, std::string& recordMedium, std::string& writeStatus);

	virtual void getPositionInfo(Poco::UInt32 instanceID, Poco::UInt32& track, std::string& trackDuration, std::string& trackMetaData, std::string& trackURI, std::string& relTime, std::string& absTime, Poco::Int32& relCount, Poco::Int32& absCount);

	virtual void getTransportInfo(Poco::UInt32 instanceID, std::string& currentTransportState, std::string& currentTransportStatus, std::string& currentSpeed);

	virtual void getTransportSettings(Poco::UInt32 instanceID, std::string& playMode, std::string& recQualityMode);

	virtual void next(Poco::UInt32 instanceID);

	virtual void pause(Poco::UInt32 instanceID);

	virtual void play(Poco::UInt32 instanceID, const std::string& speed);

	virtual void previous(Poco::UInt32 instanceID);

	virtual void record(Poco::UInt32 instanceID);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void seek(Poco::UInt32 instanceID, const std::string& unit, const std::string& target);

	virtual void setAVTransportURI(Poco::UInt32 instanceID, const std::string& currentURI, const std::string& currentURIMetaData);

	virtual void setNextAVTransportURI(Poco::UInt32 instanceID, const std::string& nextURI, const std::string& nextURIMetaData);

	virtual void setPlayMode(Poco::UInt32 instanceID, const std::string& newPlayMode);

	virtual void setRecordQualityMode(Poco::UInt32 instanceID, const std::string& newRecordQualityMode);

	virtual void stop(Poco::UInt32 instanceID);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& AVTransport1Proxy::remoting__typeId() const
{
	return IAVTransport1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_AVTransport1Proxy_INCLUDED

