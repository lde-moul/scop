#version 450 core

uniform sampler2D modelTexture;
in vec2 textureCoord;
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.2f, 0.2f, 0.4f, 1.f);
}
