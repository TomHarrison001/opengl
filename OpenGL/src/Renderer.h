#pragma once

#include <GL/glew.h>

#include "VAO.h"
#include "IBO.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VAO& va, const IBO& ib, const Shader& shader) const;
};
