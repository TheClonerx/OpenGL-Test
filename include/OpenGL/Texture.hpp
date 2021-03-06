#pragma once

#include <OpenGL/Object.hpp>

namespace OpenGL {

class Texture : public Object {
public:
    inline Texture() noexcept
        : Object {}
    {
    }

    ~Texture();

    void create() noexcept final;

    void bind() noexcept;

    void parameter(int32_t name, int32_t value) noexcept;

    void image(int mipmap, int internalFormat, int width, int height, unsigned format, int type, const uint8_t* data) noexcept;
};

} // namespace OpenGL
