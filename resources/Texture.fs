#version 450 core

uniform sampler2D modelTexture;
in vec2 textureCoord;
out vec4 FragColor;

void main()
{
    FragColor = texture(modelTexture, textureCoord);
}
