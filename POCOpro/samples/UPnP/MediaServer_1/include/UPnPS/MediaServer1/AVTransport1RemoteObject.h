//
// AVTransport1RemoteObject.h
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1RemoteObject
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


#ifndef MediaServer1_AVTransport1RemoteObject_INCLUDED
#define MediaServer1_AVTransport1RemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/MediaServer1/IAVTransport1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API AVTransport1RemoteObject: public UPnPS::MediaServer1::IAVTransport1, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<AVTransport1RemoteObject> Ptr;

	AVTransport1RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject);
		/// Creates a AVTransport1RemoteObject.

	virtual ~AVTransport1RemoteObject();
		/// Destroys the AVTransport1RemoteObject.

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

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void seek(Poco::UInt32 instanceID, const std::string& unit, const std::string& target);

	virtual void setAVTransportURI(Poco::UInt32 instanceID, const std::string& currentURI, const std::string& currentURIMetaData);

	virtual void setNextAVTransportURI(Poco::UInt32 instanceID, const std::string& nextURI, const std::string& nextURIMetaData);

	virtual void setPlayMode(Poco::UInt32 instanceID, const std::string& newPlayMode);

	virtual void setRecordQualityMode(Poco::UInt32 instanceID, const std::string& newRecordQualityMode);

	virtual void stop(Poco::UInt32 instanceID);

protected:
	void event__lastChangeChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> _pServiceObject;
};


inline void AVTransport1RemoteObject::getCurrentTransportActions(Poco::UInt32 instanceID, std::string& actions)
{
	_pServiceObject->getCurrentTransportActions(instanceID, actions);
}


inline void AVTransport1RemoteObject::getDeviceCapabilities(Poco::UInt32 instanceID, std::string& playMedia, std::string& recMedia, std::string& recQualityModes)
{
	_pServiceObject->getDeviceCapabilities(instanceID, playMedia, recMedia, recQualityModes);
}


inline void AVTransport1RemoteObject::getMediaInfo(Poco::UInt32 instanceID, Poco::UInt32& nrTracks, std::string& mediaDuration, std::string& currentURI, std::string& currentURIMetaData, std::string& nextURI, std::string& nextURIMetaData, std::string& playMedium, std::string& recordMedium, std::string& writeStatus)
{
	_pServiceObject->getMediaInfo(instanceID, nrTracks, mediaDuration, currentURI, currentURIMetaData, nextURI, nextURIMetaData, playMedium, recordMedium, writeStatus);
}


inline void AVTransport1RemoteObject::getPositionInfo(Poco::UInt32 instanceID, Poco::UInt32& track, std::string& trackDuration, std::string& trackMetaData, std::string& trackURI, std::string& relTime, std::string& absTime, Poco::Int32& relCount, Poco::Int32& absCount)
{
	_pServiceObject->getPositionInfo(instanceID, track, trackDuration, trackMetaData, trackURI, relTime, absTime, relCount, absCount);
}


inline void AVTransport1RemoteObject::getTransportInfo(Poco::UInt32 instanceID, std::string& currentTransportState, std::string& currentTransportStatus, std::string& currentSpeed)
{
	_pServiceObject->getTransportInfo(instanceID, currentTransportState, currentTransportStatus, currentSpeed);
}


inline void AVTransport1RemoteObject::getTransportSettings(Poco::UInt32 instanceID, std::string& playMode, std::string& recQualityMode)
{
	_pServiceObject->getTransportSettings(instanceID, playMode, recQualityMode);
}


inline void AVTransport1RemoteObject::next(Poco::UInt32 instanceID)
{
	_pServiceObject->next(instanceID);
}


inline void AVTransport1RemoteObject::pause(Poco::UInt32 instanceID)
{
	_pServiceObject->pause(instanceID);
}


inline void AVTransport1RemoteObject::play(Poco::UInt32 instanceID, const std::string& speed)
{
	_pServiceObject->play(instanceID, speed);
}


inline void AVTransport1RemoteObject::previous(Poco::UInt32 instanceID)
{
	_pServiceObject->previous(instanceID);
}


inline void AVTransport1RemoteObject::record(Poco::UInt32 instanceID)
{
	_pServiceObject->record(instanceID);
}


inline const Poco::RemotingNG::Identifiable::TypeId& AVTransport1RemoteObject::remoting__typeId() const
{
	return IAVTransport1::remoting__typeId();
}


inline void AVTransport1RemoteObject::seek(Poco::UInt32 instanceID, const std::string& unit, const std::string& target)
{
	_pServiceObject->seek(instanceID, unit, target);
}


inline void AVTransport1RemoteObject::setAVTransportURI(Poco::UInt32 instanceID, const std::string& currentURI, const std::string& currentURIMetaData)
{
	_pServiceObject->setAVTransportURI(instanceID, currentURI, currentURIMetaData);
}


inline void AVTransport1RemoteObject::setNextAVTransportURI(Poco::UInt32 instanceID, const std::string& nextURI, const std::string& nextURIMetaData)
{
	_pServiceObject->setNextAVTransportURI(instanceID, nextURI, nextURIMetaData);
}


inline void AVTransport1RemoteObject::setPlayMode(Poco::UInt32 instanceID, const std::string& newPlayMode)
{
	_pServiceObject->setPlayMode(instanceID, newPlayMode);
}


inline void AVTransport1RemoteObject::setRecordQualityMode(Poco::UInt32 instanceID, const std::string& newRecordQualityMode)
{
	_pServiceObject->setRecordQualityMode(instanceID, newRecordQualityMode);
}


inline void AVTransport1RemoteObject::stop(Poco::UInt32 instanceID)
{
	_pServiceObject->stop(instanceID);
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_AVTransport1RemoteObject_INCLUDED

