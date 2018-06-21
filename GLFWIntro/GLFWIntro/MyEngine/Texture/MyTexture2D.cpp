#include "MyTexture2D.h"

#include "Utils\utils.h"

MyTexture2D::MyTexture2D()
{
	textureID = 0;
	textureHeight = -1;
	textureWidth = -1;
}

MyTexture2D::~MyTexture2D()
{
}

void MyTexture2D::setProperties(GLenum sWrap, GLenum tWrap, GLenum minFilter, GLenum magFilter)
{
	if (textureID != 0)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}
	else
	{
		ERROR_LOG("ERROR::MYTEXTURE2D::SETPROPERTIES_FAILED", "Cannot set properties for 0 texture ID!");
	}
}

void MyTexture2D::setTexture(unsigned char* data, GLenum format, GLenum type, GLint internalFormat)
{
	if (data)
	{
		if (!textureID)
		{
			glGenTextures(1, &textureID);
		}

		if (textureWidth > 0 && textureHeight > 0)
		{
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureWidth, textureHeight,
				0, format, type, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			ERROR_LOG("ERROR::MYTEXTURE2D::SETTEXTURE_FAILED", "Cannot set texture with invalid height/width!");
		}
	}
	else
	{
		ERROR_LOG("ERROR::MYTEXTURE2D::SETTEXTURE_FAILED", "Cannot set NULL data to texture!");
	}
}

void MyTexture2D::activateTexture(unsigned int textureUnitID)
{
	if (textureID != 0)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnitID);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	else
	{
		ERROR_LOG("ERROR::MYTEXTURE2D::ACTIVATETEXTURE_FAILED", "Cannot activate 0 texture ID");
	}
}