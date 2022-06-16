#include "components/ui.hpp"

namespace components {

UI::UI(Object* parent) : Component(parent, TypeEnum::RENDERER)
{
}

UI::~UI()
{
}

void UI::render(glm::mat4 transform)
{
}

}
