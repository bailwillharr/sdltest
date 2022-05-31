#include "engine/resource/resource_manager.hpp"

#include <vector>

namespace engine::resource {

ResourceManager::ResourceManager()
{
	std::filesystem::path cwd = std::filesystem::current_path();

	if (std::filesystem::is_directory(cwd / "res")) {
		m_resourcesPath = std::filesystem::absolute("res");
	} else {
		m_resourcesPath = cwd.parent_path() / "share" / "sdltest";
	}
}

std::filesystem::path ResourceManager::getFilePath(const std::string& name)
{
	return m_resourcesPath / name;
}

}
