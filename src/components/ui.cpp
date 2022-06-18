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
	const std::string FONTFILE{ "LiberationMono-Regular.ttf" };

	FT_Library library;
	FT_Face face;
	int err;

	err = FT_Init_FreeType(&library);
	if (err) {
		throw std::runtime_error("Failed to initialise freetype library");
	}

	err = FT_New_Face(library, parent->res.getFilePath(FONTFILE).string().c_str(), 0, &face);
	if (err == FT_Err_Unknown_File_Format) {
		FT_Done_FreeType(library);
		throw std::runtime_error("Unknown file format for font '" + FONTFILE + "'");
	}
	else if (err != 0) {
		FT_Done_FreeType(library);
		throw std::runtime_error("Unable to open font 'font.ttf'");
	}

	err = FT_Set_Pixel_Sizes(face, 0, 64);
	if (err) {
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		throw std::runtime_error("Attempt to set pixel size to one unavailable in the font");
	}

	err = FT_Load_Char(face, 'H', FT_LOAD_RENDER);
	if (err) {
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		throw std::runtime_error("Unable to load char glyph");
	}



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
