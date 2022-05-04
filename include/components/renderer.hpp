#pragma once

#include "component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace component {

class Renderer : public Component {

private:

public:
	Renderer(std::shared_ptr<ComponentList> compList);
	~Renderer() override;

	std::string getTypeName() override;

};

}
