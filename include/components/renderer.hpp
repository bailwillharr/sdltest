#pragma once

#include "component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace component {

class Renderer : public Component {

private:

public:
	Renderer();
	~Renderer() override;

	std::string getTypeName() override;

	std::shared_ptr<ComponentCacheBase> getCacheEntry() override;

};

}
