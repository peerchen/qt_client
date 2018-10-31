//
// IAVTransport1.h
//
// Library: MediaServer1
// Package: Generated
// Module:  IAVTransport1
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


#ifndef MediaServer1_IAVTransport1_INCLUDED
#define MediaServer1_IAVTransport1_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/MediaServer1/AVTransport1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API IAVTransport1: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IAVTransport1> Ptr;

	IAVTransport1();
		/// Creates a IAVTransport1.

	virtual ~IAVTransport1();
		/// Destroys the IAVTransport1.

	virtual void getCurrentTransportActions(Poco::UInt32 instanceID, std::string& actions) = 0;

	virtual void getDeviceCapabilities(Poco::UInt32 instanceID, std::string& playMedia, std::string& recMedia, std::string& recQualityModes) = 0;

	virtual void getMediaInfo(Poco::UInt32 instanceID, Poco::UInt32& nrTracks, std::string& mediaDuration, std::string& currentURI, std::string& currentURIMetaData, std::string& nextURI, std::string& nextURIMetaData, std::string& playMedium, std::string& recordMedium, std::string& writeStatus) = 0;

	virtual void getPositionInfo(Poco::UInt32 instanceID, Poco::UInt32& track, std::string& trackDuration, std::string& trackMetaData, std::string& trackURI, std::string& relTime, std::string& absTime, Poco::Int32& relCount, Poco::Int32& absCount) = 0;

	virtual void getTransportInfo(Poco::UInt32 instanceID, std::string& currentTransportState, std::string& currentTransportStatus, std::string& currentSpeed) = 0;

	virtual void getTransportSettings(Poco::UInt32 instanceID, std::string& playMode, std::string& recQualityMode) = 0;

	virtual void next(Poco::UInt32 instanceID) = 0;

	virtual void pause(Poco::UInt32 instanceID) = 0;

	virtual void play(Poco::UInt32 instanceID, const std::string& speed) = 0;

	virtual void previous(Poco::UInt32 instanceID) = 0;

	virtual void record(Poco::UInt32 instanceID) = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void seek(Poco::UInt32 instanceID, const std::string& unit, const std::string& target) = 0;

	virtual void setAVTransportURI(Poco::UInt32 instanceID, const std::string& currentURI, const std::string& currentURIMetaData) = 0;

	virtual void setNextAVTransportURI(Poco::UInt32 instanceID, const std::string& nextURI, const std::string& nextURIMetaData) = 0;

	virtual void setPlayMode(Poco::UInt32 instanceID, const std::string& newPlayMode) = 0;

	virtual void setRecordQualityMode(Poco::UInt32 instanceID, const std::string& newRecordQualityMode) = 0;

	virtual void stop(Poco::UInt32 instanceID) = 0;

	Poco::BasicEvent < const std::string > lastChangeChanged;
};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_IAVTransport1_INCLUDED

