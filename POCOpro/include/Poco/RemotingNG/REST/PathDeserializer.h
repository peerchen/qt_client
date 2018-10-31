//
// PathDeserializer.h
//
// $Id: //poco/1.7/RemotingNG/REST/include/Poco/RemotingNG/REST/PathDeserializer.h#1 $
//
// Library: RemotingNG/REST
// Package: REST
// Module:  PathDeserializer
//
// Definition of the PathDeserializer class.
//
// Copyright (c) 2010-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_REST_PathDeserializer_INCLUDED
#define RemotingNG_REST_PathDeserializer_INCLUDED


#include "Poco/RemotingNG/REST/REST.h"
#include "Poco/RemotingNG/REST/ScalarDeserializer.h"
#include "Poco/Net/HTTPRequest.h"
#include <map>


namespace Poco {
namespace RemotingNG {
namespace REST {


class RemotingNGREST_API PathDeserializer: public ScalarDeserializer
	/// The Header Deserializer implementation for the REST Transport.
	///
	/// For more information, please see the Deserializer documentation.
{
public:
	PathDeserializer(const std::string& pathTemplate, const Poco::Net::HTTPRequest& request);
		/// Creates the PathDeserializer.

	~PathDeserializer();
		/// Destroys the PathDeserializer.

	// Poco::RemotingNG::Deserializer
	bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull);

protected:
	void parsePath(const std::string& pathTemplate, const Poco::Net::HTTPRequest& request);

	// ScalarDeserializer
	const std::string& deserializeData(const std::string& name, bool isMandatory, bool& found);

private:
	std::map<std::string, std::string> _values;
};


} } } // namespace Poco::RemotingNG::REST


#endif // RemotingNG_REST_PathDeserializer_INCLUDED
