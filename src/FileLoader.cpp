#include "FileLoader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

FileLoader::FileLoader()
{
	//TODO: load from config
	rootWWWDir = "WebContent/";
	rootTemplatesDir = "Templates/";

	templateExtension = ".template";

	html404File = rootTemplatesDir + "404" + templateExtension;
}

FileLoader::~FileLoader()
{

}

std::string FileLoader::loadFile(const std::string& path)
{
	std::ifstream file;
	
	std::string wwwPath = rootWWWDir + path;
	std::cout << "WWW Path: " << wwwPath;

	if (doesFileExist(wwwPath)) {
		file.open(wwwPath);
		statusCode = HttpStatus::Http200;
	}
	else {
		file.open(html404File);
		statusCode = HttpStatus::Http404;
	}
	
	std::string pageContent;
	std::string line;
	std::stringstream ss;

	while(!file.eof()) {
		std::getline(file, line);
		ss << line;
	}
	file.close();

	pageContent = ss.str();

	return pageContent;
}

FileLoader::HttpStatus FileLoader::getStatus() const
{
	return statusCode;
}

inline bool FileLoader::doesFileExist(const std::string& path)
{
	std::ifstream f(path.c_str());

	bool retVal = f.good();
	if (retVal == true) {
		f.close();
	}

	return retVal;
}

