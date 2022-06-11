#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vertexTextureCoord;

uniform mat4 matrix;
out vec2 textureCoord;

void main()
{
    gl_Position = matrix * vec4(position, 1.f);
    textureCoord = vertexTextureCoord;
}
