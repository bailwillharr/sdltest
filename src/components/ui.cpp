#include "components/ui.hpp"

#include "object.hpp"
#include "resource_manager.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdexcept>
#include <iostream>

namespace components {

UI::UI(Object* parent) : Component(parent, TypeEnum::UI)
{
	FT_Library library;
	if (FT_Init_FreeType(&library)) {
		throw std::runtime_error("Failed to initialise freetype library");
	}

	FT_Face face;
	const std::string FONTFILE { "LiberationMono-Regular.ttf" };
	int err = FT_New_Face(library, parent->res.getFilePath(FONTFILE).string().c_str(), 0, &face);
	if (err == FT_Err_Unknown_File_Format) {
		FT_Done_FreeType(library);
		throw std::runtime_error("Unknown file format for font '" + FONTFILE + "'");
	}
	else if (err != 0) {
		FT_Done_FreeType(library);
		throw std::runtime_error("Unable to open font 'font.ttf'");
	}

	std::cerr << "Number of glyphs: " << face->num_glyphs << "\n";

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

UI::~UI()
{
}

void UI::render(glm::mat4 transform)
{
}

}
