#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>

// This class loads a file from the web content folder
class FileLoader {

public:
	enum HttpStatus { Http404, Http200 };

	explicit FileLoader();
	virtual ~FileLoader();

	std::string loadFile(const std::string& path);
	HttpStatus getStatus() const;	

private:
	std::string rootWWWDir;
	std::string rootTemplatesDir;

	std::string templateExtension;

	std::string html404File;

	HttpStatus statusCode;
	
	inline bool doesFileExist(const std::string& path);
};

#endif // FILE_LOADER_H
