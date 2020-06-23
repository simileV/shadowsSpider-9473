#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D brush;
layout(location = 0) out vec4 Ci;

uniform vec4 brushRGBA;

void main()
{
    vec4 brushT = texture(brush, v.uv);

    Ci = brushT * brushRGBA;
}
