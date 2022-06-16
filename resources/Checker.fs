#version 450 core

out vec4 FragColor;

const int checkerSize = 32;

void main()
{
    if (int(gl_FragCoord.x) / checkerSize % 2 == int(gl_FragCoord.y) / checkerSize % 2)
        FragColor = vec4(0.15f, 0.15f, 0.2f, 1.f);
    else
        FragColor = vec4(0.17f, 0.17f, 0.22f, 1.f);
}
