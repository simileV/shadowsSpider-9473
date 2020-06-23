#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D tex;
layout(location = 0) out vec4 Ci;

void main()
{
    Ci = texture(tex, v.uv);
}


