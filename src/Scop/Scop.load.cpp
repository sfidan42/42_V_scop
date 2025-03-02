#include <Scop.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void	Scop::loadTexture(const char *texPath)
{
	unsigned int	texture;

	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(texPath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		texLoaded = true;
	}
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
        texLoaded = false;
    }
}
