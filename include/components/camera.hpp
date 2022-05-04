#pragma once

#include "component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace component {

class Camera : public Component {

private:

public:
	Camera(std::shared_ptr<ComponentList> compList);
	~Camera() override;

	std::string getTypeName() override;

};

}
