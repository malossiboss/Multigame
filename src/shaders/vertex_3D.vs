#version 330 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 iTexCoord;

out vec2 oTexCoord;

uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * vec4(iPos, 1.0);
    oTexCoord = iTexCoord;
}

