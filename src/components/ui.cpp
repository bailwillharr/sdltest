#include "components/ui.hpp"

#include "object.hpp"
#include "resource_manager.hpp"

#include <iostream>

namespace components {

UI::UI(Object* parent) : Component(parent, TypeEnum::UI)
{
	const std::string FONTFILE{ "fonts/LiberationMono-Regular.ttf" };
	m_font = parent->res.get<resources::Font>(FONTFILE);
}

UI::~UI()
{
}

void UI::render(glm::mat4 transform)
{
}

}
