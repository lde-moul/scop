#version 450 core

out vec4 FragColor;

const int checkerSize = 32;

void main()
{
    if (int(gl_FragCoord.x) / checkerSize % 2 == int(gl_FragCoord.y) / checkerSize % 2)
        FragColor = vec4(0.3f, 0.3f, 0.35f, 1.f);
    else
        FragColor = vec4(0.27f, 0.27f, 0.32f, 1.f);
}
