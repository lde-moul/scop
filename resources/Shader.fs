#version 450 core

uniform sampler2D modelTexture;
uniform float viewTypeTransition[4];

in vec2 textureCoord;

out vec4 FragColor;

const int numColors = 16;

void main()
{
    vec4 a = vec4(0.2f, 0.2f, 0.4f, 1.f);

    float color = float(gl_PrimitiveID % numColors) / numColors / 4;
    vec4 b = vec4(color, color, color + 0.15f, 1.f);

    vec4 c = texture(modelTexture, textureCoord);

    FragColor = a * viewTypeTransition[0] + b * viewTypeTransition[1] + c * viewTypeTransition[2] + b * viewTypeTransition[3];
}
