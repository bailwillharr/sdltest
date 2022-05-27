#include "engine/resource/resource_manager.hpp"

#include <vector>

namespace engine::resource {

ResourceManager::ResourceManager()
{

}

Resource* ResourceManager::get(const std::string& name)
{
	return &m_resources.at(name);
}

}
