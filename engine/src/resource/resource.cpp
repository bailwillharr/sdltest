#include "engine/resource/resource.hpp"

namespace engine::resource {

Resource::Resource(const std::filesystem::path& resPath) : m_resourcePath(resPath)
{
}

Resource::~Resource() {}

}
