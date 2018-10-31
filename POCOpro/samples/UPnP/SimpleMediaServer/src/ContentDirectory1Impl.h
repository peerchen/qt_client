//
// ContentDirectory1Impl.h
//
// $Id: //poco/1.7/UPnP/samples/SimpleMediaServer/src/ContentDirectory1Impl.h#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef MediaServer1_ContentDirectory1Impl_INCLUDED
#define MediaServer1_ContentDirectory1Impl_INCLUDED


#include "UPnPS/MediaServer1/ContentDirectory1.h"
#include "Poco/UPnP/GENA/StateProvider.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/File.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include <map>


class ContentDirectory1Impl: public UPnPS::MediaServer1::ContentDirectory1, public Poco::UPnP::GENA::StateProvider
{
public:
	ContentDirectory1Impl(const std::string& serverAddress, const std::string& mediaPath);
		/// Creates a ContentDirectory1Impl.

	virtual ~ContentDirectory1Impl();
		/// Destroys the ContentDirectory1Impl.

	static std::string mediaClassForExtension(const std::string& ext);
	static std::string contentTypeForExtension(const std::string& ext);
	static std::string dlnaProfileForExtension(const std::string& ext);
	static std::string dlnaFlagsForExtension(const std::string& ext);
	static std::string dlnaContentFeaturesForExtension(const std::string& ext);

	// ContentDirectory1
	void browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);
	void createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result);
	void createReference(const std::string& containerID, const std::string& objectID, std::string& newID);
	void deleteResource(const Poco::URI& resourceURI);
	void destroyObject(const std::string& objectID);
	void exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID);
	void getSearchCapabilities(std::string& searchCaps);
	void getSortCapabilities(std::string& sortCaps);
	void getSystemUpdateID(Poco::UInt32& id);
	void getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal);
	void importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID);
	void search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);
	void stopTransferResource(Poco::UInt32 transferID);
	void updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue);

	// StateProvider
	Poco::UPnP::GENA::StateProvider::StateVec currentState() const;
	
protected:
	struct MediaInfo
	{
		std::string id;
		std::string title;
		std::string parentID;
		Poco::File  file;
	};
	typedef std::map<std::string, MediaInfo> MediaMap;

	static const std::string PF_DC;
	static const std::string PF_UPNP;
	static const std::string NS_DC;
	static const std::string NS_UPNP;
	static const std::string NS_DIDL;
	static const std::string DIDL_LITE;
	static const std::string DIDL_CONTAINER;
	static const std::string DIDL_ITEM;
	static const std::string DIDL_RES;

	void browseMetadata(const MediaInfo& mediaInfo, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);
	void browseDirectChildren(const MediaInfo& mediaInfo, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);

	void startDIDL(Poco::XML::XMLWriter& xmlWriter);
	void endDIDL(Poco::XML::XMLWriter& xmlWriter);
	void startContainer(Poco::XML::XMLWriter& xmlWriter, const std::string& id, const std::string& parentId, Poco::UInt32 childCount);
	void endContainer(Poco::XML::XMLWriter& xmlWriter);
	void startItem(Poco::XML::XMLWriter& xmlWriter, const std::string& id, const std::string& parentId);
	void endItem(Poco::XML::XMLWriter& xmlWriter);
	void property(Poco::XML::XMLWriter& xmlWriter, const std::string& nameSpace, const std::string& name, const std::string& value);
	void resource(Poco::XML::XMLWriter& xmlWriter, const std::string& protocolInfo, Poco::UInt64 size, const std::string& uri);

	std::string mediaPath(const Poco::Path& path) const;
	const MediaInfo& findMediaInfo(const std::string& objectID) const;
	const MediaInfo& findOrCreateMediaInfo(const Poco::File& file, const std::string& parentID);
	static Poco::UInt32 countChildren(const Poco::File& directory);
	
private:
	std::string _serverAddress;
	std::string _mediaPath;
	MediaMap _mediaMap;
	mutable Poco::FastMutex _mutex;
	Poco::Logger& _logger;
};


#endif // MediaServer1_ContentDirectory1Impl_INCLUDED
