#include "resource_manager.hpp"

#include <vector>

#ifdef _MSC_VER
#include <windows.h>
#define MAX_PATH 260
#endif

ResourceManager::ResourceManager()
{
#ifdef _MSC_VER
	CHAR exeDirBuf[MAX_PATH + 1];
	GetModuleFileNameA(NULL, exeDirBuf, MAX_PATH + 1);
	std::filesystem::path cwd = std::filesystem::path(exeDirBuf).parent_path();
	std::cerr << "CWD: " << cwd << "\n";
#else
	std::filesystem::path cwd = std::filesystem::current_path();
#endif

	if (std::filesystem::is_directory(cwd / "res")) {
		m_resourcesPath = std::filesystem::absolute("res");
	} else {
		m_resourcesPath = cwd.parent_path() / "share" / "sdltest";
	}

	if (std::filesystem::is_directory(m_resourcesPath) == false) {
		throw std::runtime_error("Unable to determine resources location");
	}
}

std::filesystem::path ResourceManager::getFilePath(const std::string& name)
{
	return m_resourcesPath / name;
}
