#version 450 core

layout(location = 0) in vec3 pE;

uniform mat4 MVP;

out Vert
{
    vec3 p;
} v;

void main()
{
    gl_Position = MVP * vec4(pE, 1.f);
}
