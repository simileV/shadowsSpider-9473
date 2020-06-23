#version 450 core

in Vert
{
    vec3 uv;
} v;

layout(binding = 0) uniform samplerCube cubeM_spec;
layout(location = 0) out vec4 simp_sky;

void main()
{
    simp_sky = texture(cubeM_spec, v.uv);
}
