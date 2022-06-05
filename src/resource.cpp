#include "resource.hpp"

Resource::Resource(const std::filesystem::path& resPath, const std::string& type) : m_resourcePath(resPath), m_type(type)
{
}

Resource::~Resource() {}

std::string Resource::getType()
{
	return m_type;
}
