#include "resources/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <vector>
#include <iostream>

namespace resources {

// -1 means invalid / no bind
GLuint Texture::s_binded_texture = -1;

static void readPNG(const std::string& path, std::vector<uint8_t>& texbuf, int *width, int *height, bool *isRGBA)
{
	int x, y, n;
	unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

	if (data == NULL) {
		std::runtime_error("Unable to open texture file");
	}

	const size_t size = x * y * n;

	texbuf.resize(size);
	memcpy(texbuf.data(), data, size);

	*width = x;
	*height = y;
	if (n == 4) {
		*isRGBA = true;
	} else {
		*isRGBA = false;
	}

	stbi_image_free(data);
}

static void readGLRaw(const std::string& path, std::vector<uint8_t>& texbuf, int *width, int *height, bool *isRGBA)
{
	FILE *fp = fopen(path.c_str(), "rb");
	if (!fp) {
		std::runtime_error("Unable to open texture file");
	}

	fseek(fp, 0x02, SEEK_SET);
	uint64_t tex_data_offset;
	fread(&tex_data_offset, sizeof(uint64_t), 1, fp);

		fseek(fp, 0L, SEEK_END);
	uint64_t end = ftell(fp);

	texbuf.resize(end);
	fseek(fp, tex_data_offset, SEEK_SET);
	fread(texbuf.data(), 1, end, fp);

	fclose(fp);

	*width = 4096;
	*height = 4096;
	*isRGBA = false;

}

Texture::Texture(const std::filesystem::path& resPath) : Resource(resPath, "texture")
{
	
	std::vector<uint8_t> texbuf;

	int width, height;
	bool isRGBA;

	if (resPath.extension() == ".png") {
		readPNG(resPath.string(), texbuf, &width, &height, &isRGBA);
	} else {
		readGLRaw(resPath.string(), texbuf, &width, &height, &isRGBA);
	}
  	
	glGenTextures(1, &m_texture);
	
	bindTexture(); // glBindTexture
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (isRGBA) {
		std::cerr << "width: " << width << " height: " << height << " size: " << texbuf.size() << "\n";
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texbuf.data());
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texbuf.data());
	}

	glGenerateMipmap(GL_TEXTURE_2D); 
}

Texture::~Texture()
{
	if (s_binded_texture == m_texture) {
		s_binded_texture = -1;
	}
}

void Texture::bindTexture() const
{
	if (s_binded_texture != m_texture) {
		glBindTexture(GL_TEXTURE_2D, m_texture);
		s_binded_texture = m_texture;
	}
}

}
