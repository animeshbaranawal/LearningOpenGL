#ifndef MYTEXTURE2D_H
#define MYTEXTURE2D_H

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <string>

class MyTexture2D
{
public:
	/**
	* @brief constructor
	*		 Initialises the data member attributes
	*/
	MyTexture2D();

	/**
	* @brief destructor
	*		 Ensures that the texture data memory is freed before destroying object
	*/
	~MyTexture2D();

	/**
	* @brief sets the properties for the texture id
	* @param GLenum - sets GL_TEXTURE_WRAP_S
	* @param GLenum - sets GL_TEXTURE_WRAP_T
	* @param GLenum - sets GL_TEXTURE_MIN_FILTER
	* @param GLenum - sets GL_TEXTURE_MAG_FILTER
	*/
	void setProperties(GLenum sWrap = GL_REPEAT, GLenum tWrap = GL_REPEAT, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);

	void setTextureSize(const int& width, const int& height)
	{
		textureHeight = height;
		textureWidth = width;
	}

	/**
	* @brief sets the texture data to the given texture ID
	* @param unsigned char* - texture data to set
	* @param GLenum - format of the texture data
	* @param GLenum - type of the texture data
	* @param GLenum - internal format for GL purposes?
	*/
	void setTexture(unsigned char* data, GLenum format, GLenum type, GLint internalFormat = GL_RGB);

	/**
	* @brief activates the texture ID to the provided texture unit
	* @param unsigned int - texture unit ID to use while activation
	*/
	void activateTexture(unsigned int textureUnitID = 0);

	/**
	* @brief get the allotted texture ID
	* @return const unsigned int - texture id for the texture object
	*/
	const unsigned int getID() const
	{
		return textureID;
	}

private:
	unsigned int textureID; //!< Texture ID allotted by OpenGL
	int textureWidth; //!< width of the data loaded
	int textureHeight; //!< height of the data loaded
};

#endif
