#shader vertex
#version 330 core
    
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_projection;

void main(void)
{
    v_texCoord = texCoord;
    gl_Position = u_projection * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_texCoord;

uniform sampler2D u_texture;

void main(void)
{
    vec4 texColour = texture(u_texture, v_texCoord);
    colour = texColour;
};
