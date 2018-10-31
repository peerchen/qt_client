//
// JSONParser.h
//
// $Id: //poco/1.7/RemotingNG/REST/include/Poco/RemotingNG/REST/JSONParser.h#1 $
//
// Library: RemotingNG/REST
// Package: JSONParser
// Module:  JSONParser
//
// Definition of the JSONParser class.
//
// Copyright (c) 2010-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_REST_JSONParser_INCLUDED
#define RemotingNG_REST_JSONParser_INCLUDED


#include "Poco/RemotingNG/REST/REST.h"
#include "Poco/RemotingNG/REST/JSValue.h"
#include <istream>


namespace Poco {
namespace RemotingNG {
namespace REST {


class RemotingNGREST_API JSONParser
	/// A simple parser for JSON.
{
public:
	JSONParser(std::istream& istr);
		/// Creates a JSONParser for parsing the given stream.
	
	~JSONParser();
		/// Destroys the JSONParser.
		
	JSValue::Ptr parse();
		/// Reads a JSValue from the stream.

protected:
	int parseValue(int ch, JSValue::Ptr& pValue);
	int parseObject(int ch, JSValue::Ptr& pObject);
	int parseArray(int ch, JSValue::Ptr& pArray);
	int parseScalar(int ch, JSValue::Ptr& pScalar);
	int parseString(int ch, std::string& str);
	int parseUnicode(int ch, std::string& str);
	int skipWhitespace(int ch);
	static bool isWhitespace(int ch);
	static bool isEOF(int ch);

private:
	JSONParser();
	JSONParser(const JSONParser&);
	JSONParser& operator = (const JSONParser&);
	
	std::streambuf& _streambuf;
};


//
// inlines
//
inline bool JSONParser::isWhitespace(int ch)
{
	return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\f';
}


inline bool JSONParser::isEOF(int ch)
{
	return ch == -1;
}


} } } // namespace Poco::RemotingNG::REST


#endif // RemotingNG_REST_JSONParser_INCLUDED
