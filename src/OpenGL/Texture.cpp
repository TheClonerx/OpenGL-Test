#include <GL/glew.h>
#include <OpenGL/Texture.hpp>
#include <array>

void OpenGL::Texture::create() noexcept
{
    glGenTextures(1, &m_handle);
}

OpenGL::Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
    m_handle = invalid_handle;
}

void OpenGL::Texture::bind() noexcept
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void OpenGL::Texture::parameter(int32_t name, int32_t value) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, name, value);
}

void OpenGL::Texture::image(int mipmap, int internalFormat, int width, int height, unsigned format, int type, const char* data) noexcept
{
    glTexImage2D(GL_TEXTURE_2D, mipmap, internalFormat, width, height, 0, format, type, data);
}

#include <SFML/Graphics/Image.hpp>

void OpenGL::Texture::image(int mipmap, const sf::Image& image) noexcept
{
    glTexImage2D(GL_TEXTURE_2D, mipmap, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
}