#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D debugT;
layout(location = 0) out vec4 Ci;

void main()
{
    vec4 myDebug = texture(debugT, v.uv);
    Ci = vec4(myDebug.rgb, 1.f);
}
