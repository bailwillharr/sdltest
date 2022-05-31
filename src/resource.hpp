#pragma once

#include <string>
#include <filesystem>

class Resource {

public:
	Resource(const std::filesystem::path& resPath);
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;
	virtual ~Resource() = 0;

protected:
	std::filesystem::path m_resourcePath;

};
