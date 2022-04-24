#pragma once

#include "component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace component {

class Camera : public Component {

private:

public:
	Camera();
	~Camera() override;

	std::string getTypeName() override;

	std::shared_ptr<ComponentCacheBase> getCacheEntry() override;

};

}
