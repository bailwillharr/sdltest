#include "engine/resource/resource.hpp"

#include <map>
#include <string>
#include <filesystem>

// Owns resources

namespace engine::resource {

class ResourceManager {

public:
	ResourceManager(const std::string& argv0);
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	~ResourceManager() = default;

	/*
	template <class T>
	T* get(const std::string& name);
	*/

private:
	std::filesystem::path m_resourcesPath;
	std::map<std::string, std::unique_ptr<Resource>> m_resources;

};

/*
template <class T>
T* ResourceManager::get(const std::string& name)
{
	if (std::is_base_of<Resource, T>::value == false) {
		throw std::runtime_error("ResourceManager::get() error: specified type is not a subclass of 'Resource'");
	}
	try {
	 = m_resources.at(name);
	}
	T* derived = dynamic_cast<T*>();
	if (derived != nullptr) {
		return derived;
	}
	return nullptr;

}
*/

}
