#shader vertex
#version 330 core
    
layout(location = 0) in vec4 position;

void main(void)
{
    gl_Position = position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 colour;

void main(void)
{
    colour = vec4(1.f, 1.f, 0.f, 1.f);
};
