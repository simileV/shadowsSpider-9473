#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D rttC;
layout(location = 0) out float Ci;

void main()
{
    vec4 color = texture(rttC, v.uv);

    Ci = max(dot(color.rgb, vec3(.2125f, .7154f, .0721f)), .0001f);
}
