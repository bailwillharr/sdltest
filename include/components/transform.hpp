#pragma once

#include "component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace component {

class Transform : public Component {

private:

public:
	Transform();
	~Transform() override;

	std::string getTypeName() override;

	std::shared_ptr<ComponentCacheBase> getCacheEntry() override;

};

}
