//
// ContentDirectory1Impl.cpp
//
// $Id: //poco/1.7/UPnP/samples/SimpleMediaServer/src/ContentDirectory1Impl.cpp#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#include "ContentDirectory1Impl.h"
#include "Poco/SAX/AttributesImpl.h"
#include "Poco/UPnP/UPnPException.h"
#include "Poco/Util/Application.h"
#include "Poco/NumberFormatter.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Format.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Path.h"
#include "Poco/MD5Engine.h"
#include "Poco/URI.h"
#include "Poco/String.h"
#include <sstream>


const std::string ContentDirectory1Impl::PF_DC("dc");
const std::string ContentDirectory1Impl::PF_UPNP("upnp");
const std::string ContentDirectory1Impl::NS_DC("http://purl.org/dc/elements/1.1/");
const std::string ContentDirectory1Impl::NS_UPNP("urn:schemas-upnp-org:metadata-1-0/upnp/");
const std::string ContentDirectory1Impl::NS_DIDL("urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/");
const std::string ContentDirectory1Impl::DIDL_LITE("DIDL-Lite");
const std::string ContentDirectory1Impl::DIDL_CONTAINER("container");
const std::string ContentDirectory1Impl::DIDL_ITEM("item");
const std::string ContentDirectory1Impl::DIDL_RES("res");


ContentDirectory1Impl::ContentDirectory1Impl(const std::string& serverAddress, const std::string& mediaPath):
	_serverAddress(serverAddress),
	_mediaPath(mediaPath),
	_logger(Poco::Logger::get("ContentDirectory1Impl"))
{
	MediaInfo root;
	root.id       = "0";
	root.title    = "Media Library";
	root.parentID = "-1";
	root.file     = Poco::File(_mediaPath);
	_mediaMap["0"] = root;
}


ContentDirectory1Impl::~ContentDirectory1Impl()
{
}


void ContentDirectory1Impl::browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	if (_logger.debug())
	{
		_logger.debug(Poco::format("Entering ContentDirectory1Impl::browse(objectID=%s, browseFlag=%s, startIndex=%u, requestedCount=%u)", objectID, browseFlag, startingIndex, requestedCount));
	}
	
	const MediaInfo& mediaInfo = findMediaInfo(objectID);
		
	if (browseFlag == "BrowseMetadata")
	{
		browseMetadata(mediaInfo, filter, startingIndex, requestedCount, sortCriteria, result, numberReturned, totalMatches, updateID);
	}
	else if (browseFlag == "BrowseDirectChildren")
	{
		browseDirectChildren(mediaInfo, filter, startingIndex, requestedCount, sortCriteria, result, numberReturned, totalMatches, updateID);
	}
	else throw Poco::UPnP::UPnPException("browseFlag", Poco::UPnP::UPnPException::CODE_ARGUMENT_VALUE_OUT_OF_RANGE);
	
	if (_logger.debug())
	{
		_logger.debug(result);
	}
}


void ContentDirectory1Impl::browseMetadata(const MediaInfo& mediaInfo, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	numberReturned = 1;
	totalMatches   = 1;
	updateID       = 0;
	std::ostringstream resultStream;
	Poco::XML::XMLWriter xmlWriter(resultStream, Poco::XML::XMLWriter::CANONICAL_XML | Poco::XML::XMLWriter::PRETTY_PRINT);
	startDIDL(xmlWriter);
	if (mediaInfo.file.isDirectory())
	{
		startContainer(xmlWriter, mediaInfo.id, mediaInfo.parentID, countChildren(mediaInfo.file));
		property(xmlWriter, NS_DC, "title", mediaInfo.title);
		property(xmlWriter, NS_UPNP, "class", "object.container.storageFolder");
		endContainer(xmlWriter);
	}
	else
	{
		Poco::Path p(mediaInfo.file.path());
		startItem(xmlWriter, mediaInfo.id, mediaInfo.parentID);
		property(xmlWriter, NS_DC, "title", mediaInfo.title);
		property(xmlWriter, NS_DC, "date", Poco::DateTimeFormatter::format(mediaInfo.file.getLastModified(), "%Y-%m-%d"));
		property(xmlWriter, NS_UPNP, "class", mediaClassForExtension(p.getExtension()));
		std::string contentType(contentTypeForExtension(p.getExtension()));
		std::string protocolInfo(Poco::format("http-get:*:%s:*", contentType));
		std::string uri(Poco::format("http://%s/media%s", _serverAddress, mediaPath(p)));
		resource(xmlWriter, protocolInfo, mediaInfo.file.getSize(), uri);
		endItem(xmlWriter);
	}
	endDIDL(xmlWriter);
	result = resultStream.str();
}


void ContentDirectory1Impl::browseDirectChildren(const MediaInfo& mediaInfo, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	std::vector<Poco::File> files;
	if (mediaInfo.file.isDirectory())
		mediaInfo.file.list(files);

	numberReturned = 0;
	totalMatches   = 0;
	updateID       = 0;
	std::ostringstream resultStream;
	Poco::XML::XMLWriter xmlWriter(resultStream, Poco::XML::XMLWriter::CANONICAL_XML | Poco::XML::XMLWriter::PRETTY_PRINT);
	startDIDL(xmlWriter);

	for (std::vector<Poco::File>::iterator it = files.begin(); it != files.end(); ++it)
	{
		if (!it->isHidden())
		{
			if (totalMatches >= startingIndex && (totalMatches < startingIndex + requestedCount || requestedCount == 0))
			{
				Poco::Path p(it->path());
				if (it->isDirectory())
				{
					const MediaInfo& containerInfo = findOrCreateMediaInfo(*it, mediaInfo.id);
					startContainer(xmlWriter, containerInfo.id, containerInfo.parentID, countChildren(*it));
					property(xmlWriter, NS_DC, "title", containerInfo.title);
					property(xmlWriter, NS_UPNP, "class", "object.container.storageFolder");
					endContainer(xmlWriter);
				}
				else
				{
					const MediaInfo& fileInfo = findOrCreateMediaInfo(*it, mediaInfo.id);
					startItem(xmlWriter, fileInfo.id, fileInfo.parentID);
					property(xmlWriter, NS_DC, "title", p.getBaseName());
					property(xmlWriter, NS_DC, "date", Poco::DateTimeFormatter::format(it->getLastModified(), "%Y-%m-%d"));
					property(xmlWriter, NS_UPNP, "class", mediaClassForExtension(p.getExtension()));
					std::string contentType(contentTypeForExtension(p.getExtension()));
					std::string dlnaProfile(dlnaProfileForExtension(p.getExtension()));
					std::string dlnaContentFeatures(dlnaContentFeaturesForExtension(p.getExtension()));
					std::string protocolInfo(Poco::format("http-get:*:%s:%s", contentType, dlnaProfile, dlnaContentFeatures));
					std::string uri(Poco::format("http://%s/media%s", _serverAddress, mediaPath(p)));
					resource(xmlWriter, protocolInfo, it->getSize(), uri);
					endItem(xmlWriter);
				}
				numberReturned++;
			}
			totalMatches++;
		}
	}

	endDIDL(xmlWriter);
	result = resultStream.str();
}


void ContentDirectory1Impl::createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result)
{
	throw Poco::UPnP::UPnPException("CreateObject", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::createReference(const std::string& containerID, const std::string& objectID, std::string& newID)
{
	throw Poco::UPnP::UPnPException("CreateReference", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::deleteResource(const Poco::URI& resourceURI)
{
	throw Poco::UPnP::UPnPException("DeleteResource", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::destroyObject(const std::string& objectID)
{
	throw Poco::UPnP::UPnPException("DestroyObject", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID)
{
	throw Poco::UPnP::UPnPException("ExportResource", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::getSearchCapabilities(std::string& searchCaps)
{
	_logger.debug("Entering ContentDirectory1Impl::getSearchCapabilities()");
	
	searchCaps = "";
}


void ContentDirectory1Impl::getSortCapabilities(std::string& sortCaps)
{
	_logger.debug("Entering ContentDirectory1Impl::getSortCapabilities()");

	sortCaps = "";
}


void ContentDirectory1Impl::getSystemUpdateID(Poco::UInt32& id)
{
	_logger.debug("Entering ContentDirectory1Impl::getSystemUpdateID()");
	
	id = 0;
}


void ContentDirectory1Impl::getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal)
{
	throw Poco::UPnP::UPnPException("GetTransferProgress", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID)
{
	throw Poco::UPnP::UPnPException("ImportResource", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	throw Poco::UPnP::UPnPException("Search", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::stopTransferResource(Poco::UInt32 transferID)
{
	throw Poco::UPnP::UPnPException("StopTransferResource", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void ContentDirectory1Impl::updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue)
{
	throw Poco::UPnP::UPnPException("UpdateObject", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


Poco::UPnP::GENA::StateProvider::StateVec ContentDirectory1Impl::currentState() const
{
	Poco::UPnP::GENA::StateProvider::StateVec result;
	result.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair("ContainerUpdateIDs", ""));
	result.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair("SystemUpdateID", "0"));
	result.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair("TransferIDs", ""));
	return result;
}


std::string ContentDirectory1Impl::mediaClassForExtension(const std::string& ext)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	std::string key(Poco::format("media.class.%s", Poco::toLower(ext)));
	return app.config().getString(key, "object.item");
}


std::string ContentDirectory1Impl::contentTypeForExtension(const std::string& ext)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	std::string key(Poco::format("media.mimeType.%s", Poco::toLower(ext)));
	return app.config().getString(key, "application/binary");
}


std::string ContentDirectory1Impl::dlnaProfileForExtension(const std::string& ext)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	std::string key(Poco::format("dlna.profile.%s", Poco::toLower(ext)));
	return app.config().getString(key, "");
}


std::string ContentDirectory1Impl::dlnaFlagsForExtension(const std::string& ext)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	std::string key(Poco::format("dlna.flags.%s", Poco::toLower(ext)));
	return app.config().getString(key, "00000000");
}


std::string ContentDirectory1Impl::dlnaContentFeaturesForExtension(const std::string& ext)
{
	return Poco::format(
		"DLNA.ORG_PN=%s;DLNA.ORG_OP=01;DLNA.ORG_CI=0;DLNA.ORG_FLAGS=%s000000000000000000000000",
		dlnaProfileForExtension(ext),
		dlnaFlagsForExtension(ext));
}


void ContentDirectory1Impl::startDIDL(Poco::XML::XMLWriter& xmlWriter)
{
	xmlWriter.startDocument();
	xmlWriter.startPrefixMapping(PF_DC, NS_DC);
	xmlWriter.startPrefixMapping(PF_UPNP, NS_UPNP);
	xmlWriter.startPrefixMapping("", NS_DIDL);
	xmlWriter.startElement(NS_DIDL, DIDL_LITE, DIDL_LITE);
}


void ContentDirectory1Impl::endDIDL(Poco::XML::XMLWriter& xmlWriter)
{
	xmlWriter.endElement(NS_DIDL, DIDL_LITE, DIDL_LITE);
	xmlWriter.endPrefixMapping(PF_DC);
	xmlWriter.endPrefixMapping(PF_UPNP);
	xmlWriter.endDocument();
}


void ContentDirectory1Impl::startContainer(Poco::XML::XMLWriter& xmlWriter, const std::string& id, const std::string& parentId, Poco::UInt32 childCount)
{
	Poco::XML::AttributesImpl attrs;
	attrs.addAttribute(NS_DIDL, "id", "", "CDATA", id);
	attrs.addAttribute(NS_DIDL, "parentID", "", "CDATA", parentId);
	attrs.addAttribute(NS_DIDL, "childCount", "", "CDATA", Poco::NumberFormatter::format(childCount));
	attrs.addAttribute(NS_DIDL, "restricted", "", "CDATA", "false");
	attrs.addAttribute(NS_DIDL, "searchable", "", "CDATA", "false");
	xmlWriter.startElement(NS_DIDL, DIDL_CONTAINER, DIDL_CONTAINER, attrs);
}


void ContentDirectory1Impl::endContainer(Poco::XML::XMLWriter& xmlWriter)
{
	xmlWriter.endElement(NS_DIDL, DIDL_CONTAINER, DIDL_CONTAINER);
}


void ContentDirectory1Impl::startItem(Poco::XML::XMLWriter& xmlWriter, const std::string& id, const std::string& parentId)
{
	Poco::XML::AttributesImpl attrs;
	attrs.addAttribute(NS_DIDL, "id", "", "CDATA", id);
	attrs.addAttribute(NS_DIDL, "parentID", "", "CDATA", parentId);
	attrs.addAttribute(NS_DIDL, "restricted", "", "CDATA", "false");
	xmlWriter.startElement(NS_DIDL, DIDL_ITEM, DIDL_ITEM, attrs);
}


void ContentDirectory1Impl::endItem(Poco::XML::XMLWriter& xmlWriter)
{
	xmlWriter.endElement(NS_DIDL, DIDL_ITEM, DIDL_ITEM);
}


void ContentDirectory1Impl::property(Poco::XML::XMLWriter& xmlWriter, const std::string& nameSpace, const std::string& name, const std::string& value)
{
	xmlWriter.startElement(nameSpace, name, "");
	xmlWriter.characters(value);
	xmlWriter.endElement(nameSpace, name, "");
}


void ContentDirectory1Impl::resource(Poco::XML::XMLWriter& xmlWriter, const std::string& protocolInfo, Poco::UInt64 size, const std::string& uri)
{
	Poco::XML::AttributesImpl attrs;
	attrs.addAttribute(NS_DIDL, "protocolInfo", "", "CDATA", protocolInfo);
	attrs.addAttribute(NS_DIDL, "size", "", "CDATA", Poco::NumberFormatter::format(size));
	xmlWriter.startElement(NS_DIDL, DIDL_RES, DIDL_RES, attrs);
	xmlWriter.characters(uri);
	xmlWriter.endElement(NS_DIDL, DIDL_RES, DIDL_RES);
}


std::string ContentDirectory1Impl::mediaPath(const Poco::Path& path) const
{
	Poco::Path p(path);
	p.makeAbsolute();
	p.makeFile();
	Poco::Path basePath(_mediaPath);
	basePath.makeDirectory();
	for (int i = 0; i < basePath.depth(); i++)
	{
		p.popFrontDirectory();
	}
	p.setDevice(""); // remove device part (Windows)
	std::string rawPath = p.toString(Poco::Path::PATH_UNIX);
	std::string encodedPath;
	Poco::URI::encode(rawPath, "", encodedPath);
	return encodedPath;
}


const ContentDirectory1Impl::MediaInfo& ContentDirectory1Impl::findMediaInfo(const std::string& objectID) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	MediaMap::const_iterator it = _mediaMap.find(objectID);
	if (it != _mediaMap.end()) 
		return it->second;
	else
		throw Poco::UPnP::UPnPException("objectID", Poco::UPnP::UPnPException::CODE_ARGUMENT_VALUE_OUT_OF_RANGE);
}


const ContentDirectory1Impl::MediaInfo& ContentDirectory1Impl::findOrCreateMediaInfo(const Poco::File& file, const std::string& parentID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	Poco::MD5Engine md5;
	md5.update(file.path());
	std::string objectID = Poco::DigestEngine::digestToHex(md5.digest());
	
	MediaMap::iterator it = _mediaMap.find(objectID);
	if (it == _mediaMap.end())
	{
		Poco::Path p(file.path());
		MediaInfo& mediaInfo = _mediaMap[objectID];
		mediaInfo.id       = objectID;
		mediaInfo.title    = p.getBaseName();
		mediaInfo.parentID = parentID;
		mediaInfo.file     = file;
		return mediaInfo;
	}
	else return it->second;
}


Poco::UInt32 ContentDirectory1Impl::countChildren(const Poco::File& directory)
{
	Poco::DirectoryIterator it(directory);
	Poco::DirectoryIterator end;
	Poco::UInt32 count = 0;
	while (it != end) 
	{
		if (!it->isHidden())
			count++;
		it++; 
	}
	return count;
}
