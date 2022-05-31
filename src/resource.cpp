#include "resource.hpp"

namespace engine {

Resource::Resource(const std::filesystem::path& resPath) : m_resourcePath(resPath)
{
}

Resource::~Resource() {}

}
