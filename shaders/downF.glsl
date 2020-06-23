#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv, uv2, uv3, uv4, uv5;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D downSamp;
layout(location = 0) out vec4 Ci;

void main()
{
    Ci = (  texture(downSamp, v.uv2) +
            texture(downSamp, v.uv3) +
            texture(downSamp, v.uv4) +
            texture(downSamp, v.uv5)) * .25f;

    Ci = max(Ci, 0.f);
}
