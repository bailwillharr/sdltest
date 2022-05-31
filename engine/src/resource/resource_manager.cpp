#include "engine/resource/resource_manager.hpp"

#include <vector>

namespace engine::resource {

ResourceManager::ResourceManager(const std::string& argv0)
{
	std::filesystem::path binDir = std::filesystem::path(argv0).parent_path();
	if (std::filesystem::is_directory(binDir.append("res"))) {
		m_resourcesPath = std::filesystem::absolute("res");
	} else {
		m_resourcesPath = binDir.parent_path().append("share").append("sdltest");
	}
}

}
