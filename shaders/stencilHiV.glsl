#version 450 core

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;

uniform mat4 MVP;

out Vert
{
    vec3 p;
} v;

void main()
{
    gl_Position = MVP * vec4(pE, 1.f);
}
