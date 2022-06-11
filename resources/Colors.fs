#version 450 core

uniform sampler2D modelTexture;
in vec2 textureCoord;
out vec4 FragColor;

const int numColors = 16;

void main()
{
    float color = float(gl_PrimitiveID % numColors) / numColors / 4;
    FragColor = vec4(color, color, color + 0.15f, 1.f);
}
