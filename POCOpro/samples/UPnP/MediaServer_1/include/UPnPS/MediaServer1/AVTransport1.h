//
// AVTransport1.h
//
// Library: MediaServer1
// Package: MediaServer1
// Module:  AVTransport1
//
// This file has been generated on 2012-10-29 11:42:20 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef MediaServer1_AVTransport1_INCLUDED
#define MediaServer1_AVTransport1_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


//@ namespace="urn:schemas-upnp-org:service:AVTransport:1"
//@ remote
class MediaServer1_API AVTransport1
{
public:
	typedef Poco::SharedPtr<AVTransport1> Ptr;

	AVTransport1();
		/// Creates a AVTransport1.

	virtual ~AVTransport1();
		/// Destroys the AVTransport1.

	//@ $actions={name="Actions", direction=out}
	//@ $instanceID={name="InstanceID"}
	//@ name=GetCurrentTransportActions
	//@ optional=true
	//@ replyName=GetCurrentTransportActionsResponse
	virtual void getCurrentTransportActions(Poco::UInt32 instanceID, std::string& actions) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $playMedia={name="PlayMedia", direction=out}
	//@ $recMedia={name="RecMedia", direction=out}
	//@ $recQualityModes={name="RecQualityModes", direction=out}
	//@ name=GetDeviceCapabilities
	//@ replyName=GetDeviceCapabilitiesResponse
	virtual void getDeviceCapabilities(Poco::UInt32 instanceID, std::string& playMedia, std::string& recMedia, std::string& recQualityModes) = 0;

	//@ $currentURI={name="CurrentURI", direction=out}
	//@ $currentURIMetaData={name="CurrentURIMetaData", direction=out}
	//@ $instanceID={name="InstanceID"}
	//@ $mediaDuration={name="MediaDuration", direction=out}
	//@ $nextURI={name="NextURI", direction=out}
	//@ $nextURIMetaData={name="NextURIMetaData", direction=out}
	//@ $nrTracks={name="NrTracks", direction=out}
	//@ $playMedium={name="PlayMedium", direction=out}
	//@ $recordMedium={name="RecordMedium", direction=out}
	//@ $writeStatus={name="WriteStatus", direction=out}
	//@ name=GetMediaInfo
	//@ replyName=GetMediaInfoResponse
	virtual void getMediaInfo(Poco::UInt32 instanceID, Poco::UInt32& nrTracks, std::string& mediaDuration, std::string& currentURI, std::string& currentURIMetaData, std::string& nextURI, std::string& nextURIMetaData, std::string& playMedium, std::string& recordMedium, std::string& writeStatus) = 0;

	//@ $absCount={name="AbsCount", direction=out}
	//@ $absTime={name="AbsTime", direction=out}
	//@ $instanceID={name="InstanceID"}
	//@ $relCount={name="RelCount", direction=out}
	//@ $relTime={name="RelTime", direction=out}
	//@ $track={name="Track", direction=out}
	//@ $trackDuration={name="TrackDuration", direction=out}
	//@ $trackMetaData={name="TrackMetaData", direction=out}
	//@ $trackURI={name="TrackURI", direction=out}
	//@ name=GetPositionInfo
	//@ replyName=GetPositionInfoResponse
	virtual void getPositionInfo(Poco::UInt32 instanceID, Poco::UInt32& track, std::string& trackDuration, std::string& trackMetaData, std::string& trackURI, std::string& relTime, std::string& absTime, Poco::Int32& relCount, Poco::Int32& absCount) = 0;

	//@ $currentSpeed={name="CurrentSpeed", direction=out}
	//@ $currentTransportState={name="CurrentTransportState", direction=out}
	//@ $currentTransportStatus={name="CurrentTransportStatus", direction=out}
	//@ $instanceID={name="InstanceID"}
	//@ name=GetTransportInfo
	//@ replyName=GetTransportInfoResponse
	virtual void getTransportInfo(Poco::UInt32 instanceID, std::string& currentTransportState, std::string& currentTransportStatus, std::string& currentSpeed) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $playMode={name="PlayMode", direction=out}
	//@ $recQualityMode={name="RecQualityMode", direction=out}
	//@ name=GetTransportSettings
	//@ replyName=GetTransportSettingsResponse
	virtual void getTransportSettings(Poco::UInt32 instanceID, std::string& playMode, std::string& recQualityMode) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ name=Next
	//@ replyName=NextResponse
	virtual void next(Poco::UInt32 instanceID) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ name=Pause
	//@ optional=true
	//@ replyName=PauseResponse
	virtual void pause(Poco::UInt32 instanceID) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $speed={name="Speed"}
	//@ name=Play
	//@ replyName=PlayResponse
	virtual void play(Poco::UInt32 instanceID, const std::string& speed) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ name=Previous
	//@ replyName=PreviousResponse
	virtual void previous(Poco::UInt32 instanceID) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ name=Record
	//@ optional=true
	//@ replyName=RecordResponse
	virtual void record(Poco::UInt32 instanceID) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $target={name="Target"}
	//@ $unit={name="Unit"}
	//@ name=Seek
	//@ replyName=SeekResponse
	virtual void seek(Poco::UInt32 instanceID, const std::string& unit, const std::string& target) = 0;

	//@ $currentURI={name="CurrentURI"}
	//@ $currentURIMetaData={name="CurrentURIMetaData"}
	//@ $instanceID={name="InstanceID"}
	//@ name=SetAVTransportURI
	//@ replyName=SetAVTransportURIResponse
	virtual void setAVTransportURI(Poco::UInt32 instanceID, const std::string& currentURI, const std::string& currentURIMetaData) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $nextURI={name="NextURI"}
	//@ $nextURIMetaData={name="NextURIMetaData"}
	//@ name=SetNextAVTransportURI
	//@ optional=true
	//@ replyName=SetNextAVTransportURIResponse
	virtual void setNextAVTransportURI(Poco::UInt32 instanceID, const std::string& nextURI, const std::string& nextURIMetaData) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $newPlayMode={name="NewPlayMode"}
	//@ name=SetPlayMode
	//@ optional=true
	//@ replyName=SetPlayModeResponse
	virtual void setPlayMode(Poco::UInt32 instanceID, const std::string& newPlayMode) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ $newRecordQualityMode={name="NewRecordQualityMode"}
	//@ name=SetRecordQualityMode
	//@ optional=true
	//@ replyName=SetRecordQualityModeResponse
	virtual void setRecordQualityMode(Poco::UInt32 instanceID, const std::string& newRecordQualityMode) = 0;

	//@ $instanceID={name="InstanceID"}
	//@ name=Stop
	//@ replyName=StopResponse
	virtual void stop(Poco::UInt32 instanceID) = 0;

	//@ name=LastChange
	//@ oneway=true
	Poco::BasicEvent<const std::string> lastChangeChanged;
};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_AVTransport1_INCLUDED

