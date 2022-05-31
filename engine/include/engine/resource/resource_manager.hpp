#pragma once

#include "engine/resource/resource.hpp"

#include <map>
#include <string>
#include <iostream>
#include <filesystem>

// Owns resources

namespace engine::resource {

class ResourceManager {

public:
	ResourceManager(const char* argv0);
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	~ResourceManager() = default;

	template <class T>
	std::shared_ptr<T> create(const std::string& name);

	// creates the resource if it is not in the map or the weak_ptr has expired
	template <class T>
	std::shared_ptr<T> get(const std::string& name);

private:
	std::filesystem::path m_resourcesPath;
	std::map<std::string, std::weak_ptr<Resource>> m_resources;

	std::filesystem::path getFilePath(const std::string& name);

};

template <class T>
std::shared_ptr<T> ResourceManager::create(const std::string& name)
{
	if (std::is_base_of<Resource, T>::value == false) {
		throw std::runtime_error("ResourceManager::create() error: specified type is not a subclass of 'Resource'");
	}
	auto resource = std::make_shared<T>(getFilePath(name));
	m_resources.emplace(name, std::dynamic_pointer_cast<Resource>(resource));
	return resource;
}

template <class T>
std::shared_ptr<T> ResourceManager::get(const std::string& name)
{
	if (std::is_base_of<Resource, T>::value == false) {
		throw std::runtime_error("ResourceManager::get() error: specified type is not a subclass of 'Resource'");
	}

	bool resourceExists = true;
	std::weak_ptr<Resource> res;
	try {
		res = m_resources.at(name);
	} catch (std::out_of_range &e) {
		resourceExists = false;
	}
	if (res.expired()) {
		resourceExists = false;
		m_resources.erase(name);
	}

	if (resourceExists) {
		auto castedSharedPtr = std::dynamic_pointer_cast<T>(res.lock());
		if (castedSharedPtr == nullptr) {
			throw std::runtime_error("error: attempt to get Resource which already exists as another type");
		} else {
			return castedSharedPtr;
		}
	} else {
		return create<T>(name);
	}
}

}
