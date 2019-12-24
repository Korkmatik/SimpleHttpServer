#include "HttpHeader.hpp"

#include <iterator>
#include <sstream>

HttpHeader::HttpHeader(std::string header)
{
	methodToString = new std::map<std::string, Method>;
	methodToString->insert(std::make_pair("GET", Method::GET));
	methodToString->insert(std::make_pair("HEAD", Method::HEAD));
	methodToString->insert(std::make_pair("POST", Method::POST));	
	methodToString->insert(std::make_pair("PUT", Method::PUT));
	methodToString->insert(std::make_pair("DELETE", Method::DELETE));
	methodToString->insert(std::make_pair("CONNECT", Method::CONNECT));
	methodToString->insert(std::make_pair("OPTIONS", Method::TRACE));
	methodToString->insert(std::make_pair("PATCH", Method::PATCH));
	methodToString->insert(std::make_pair("TRACE", Method::TRACE));

	parse(header);
}

HttpHeader::~HttpHeader()
{
	delete methodToString;
}

HttpHeader::Method HttpHeader::getMethod()
{
	return method;
}

std::string HttpHeader::getPath()
{
	return path;
}

std::string HttpHeader::getVersion()
{
	return version;
}

std::string HttpHeader::getHost()
{
	return host;
}

std::string HttpHeader::getUserAgent()
{
	return userAgent;
}

std::string HttpHeader::getAccept()
{
	return accept;
}

std::string HttpHeader::getAcceptLanguage()
{
	return acceptLanguage;
}

const std::vector<std::string>& HttpHeader::getAcceptEncoding()
{
	return acceptEncoding;
}

std::string HttpHeader::getReferer()
{
	return referer;
}

std::string HttpHeader::getConnection()
{
	return connection;
}

int HttpHeader::getUpgradeInsecureRequests()
{
	return upgradeInsecureRequest;
}

std::string HttpHeader::getIfModifiedSince()
{
	return ifModifiedSince;
}

std::string HttpHeader::getIfNoneMatch()
{
	return ifNoneMatch;
}

std::string HttpHeader::getCacheControl()
{
	return cacheControl;
}

std::string HttpHeader::methodToStr(Method method)
{
	std::string returnValue = "";

	for (auto it = methodToString->begin(); it != methodToString->end(); it++) {
		if (it->second == method) {
			returnValue = it->first;
			break;
		}
	}

	return returnValue;
}

void HttpHeader::parse(const std::string& header)
{
	// splitting each line of the header
	std::istringstream stream(header);

	std::vector<std::string> lines;
	std::string segment;
	while(std::getline(stream, segment)) {
		lines.push_back(segment);
	}

	
	std::vector<int> spacePositions;

	// reading the first line
	for (int i = 0; i < lines[0].length(); i++) {
		if (lines[0].at(i) == ' ') {
			spacePositions.push_back(i);

			if (spacePositions.size() >= 2) {
				break;
			}
		}
	}	

	// Getting the method
	std::string method = lines[0].substr(0, spacePositions[0]);
	this->method = methodToString->at(method);
	
	path = lines[0].substr(spacePositions[0]+1, spacePositions[1]-(spacePositions[0]+1));

	version = lines[0].substr(spacePositions[1]+1, lines[0].length()-(spacePositions[1]+1));
	
}
