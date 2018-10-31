//
// FormDeserializer.h
//
// $Id: //poco/1.7/RemotingNG/REST/include/Poco/RemotingNG/REST/FormDeserializer.h#1 $
//
// Library: RemotingNG/REST
// Package: REST
// Module:  FormDeserializer
//
// Definition of the FormDeserializer class.
//
// Copyright (c) 2010-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_REST_FormDeserializer_INCLUDED
#define RemotingNG_REST_FormDeserializer_INCLUDED


#include "Poco/RemotingNG/REST/REST.h"
#include "Poco/RemotingNG/REST/ScalarDeserializer.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTMLForm.h"
#include <istream>


namespace Poco {
namespace RemotingNG {
namespace REST {


class RemotingNGREST_API FormDeserializer: public ScalarDeserializer
	/// The Form Deserializer implementation for the REST Transport.
	///
	/// For more information, please see the Deserializer documentation.
{
public:
	FormDeserializer(Poco::Net::HTTPRequest& request);
		/// Creates the FormDeserializer.

	FormDeserializer(Poco::Net::HTTPRequest& request, std::istream& stream);
		/// Creates the FormDeserializer.

	FormDeserializer(Poco::Net::HTTPResponse& response, std::istream& stream);
		/// Creates the FormDeserializer.

	~FormDeserializer();
		/// Destroys the FormDeserializer.
		
	// Poco::RemotingNG::Deserializer
	bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull);

protected:
	// ScalarDeserializer
	const std::string& deserializeData(const std::string& name, bool isMandatory, bool& found);

private:
	Poco::Net::HTMLForm _form;

	static const std::string EMPTY;
};


} } } // namespace Poco::RemotingNG::REST


#endif // RemotingNG_REST_FormDeserializer_INCLUDED
