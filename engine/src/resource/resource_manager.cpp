#include "engine/resource/resource_manager.hpp"

#include <vector>

namespace engine::resource {

ResourceManager::ResourceManager(const char* argv0)
{
	std::filesystem::path binDir = std::filesystem::path(argv0).parent_path();
	if (std::filesystem::is_directory(binDir / "res")) {
		m_resourcesPath = std::filesystem::absolute("res");
	} else {
		m_resourcesPath = binDir.parent_path() / "share" / "sdltest";
	}
}

std::filesystem::path ResourceManager::getFilePath(const std::string& name)
{
	return m_resourcesPath / name;
}

}
