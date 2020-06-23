#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D adaptedLuminance;
layout(bindless_sampler, location = 1) uniform sampler2D initialLuminance;
layout(location = 0) out float Ci;

uniform float dTime;

void main()
{
    float lastLum = exp(texture(adaptedLuminance, v.uv)).r;
    float currentLum = texture(initialLuminance, v.uv).r;

    Ci = log(lastLum + (currentLum - lastLum) * (1.f - exp(-dTime)));
}
