#version 450 core

layout(location = 0) in vec3 pE;

uniform mat4 depthMVP;

void main()
{
    gl_Position = depthMVP * vec4(pE, 1.f);
}
