#include "engine/resource/resource.hpp"

#include <map>
#include <string>

// Owns resources

namespace engine::resource {

class ResourceManager {

public:
	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	~ResourceManager() = default;

	Resource* get(const std::string& name);

private:
	std::map<std::string, Resource> m_resources;

};

}
