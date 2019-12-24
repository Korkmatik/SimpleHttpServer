#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>
#include <vector>
#include <map>

class HttpHeader {

public:
	enum class Method {
		GET,
		HEAD,
		POST,
		PUT,
		DELETE,
		CONNECT,
		OPTIONS,
		TRACE,
		PATCH
	};

	explicit HttpHeader(std::string header);
	virtual ~HttpHeader();

	HttpHeader::Method getMethod();
	std::string getPath();
	std::string getVersion();

	std::string getHost();
	std::string getUserAgent();
	std::string getAccept();
	std::string getAcceptLanguage();
	const std::vector<std::string>& getAcceptEncoding();
	std::string getReferer();
	std::string getConnection();
	int getUpgradeInsecureRequests();
	std::string getIfModifiedSince();
	std::string getIfNoneMatch();
	std::string getCacheControl();
	
	std::string methodToStr(HttpHeader::Method method);

private:
	Method method;
	std::string path;
	std::string version;
	std::string host;
	std::string userAgent;
	std::string accept;
	std::string acceptLanguage;
	std::vector<std::string> acceptEncoding;
	std::string referer;
	std::string connection;
	int upgradeInsecureRequest;
	std::string ifModifiedSince;
	std::string ifNoneMatch;
	std::string cacheControl;

	std::map<std::string, Method>* methodToString;

	void parse(const std::string& header);
};

#endif
