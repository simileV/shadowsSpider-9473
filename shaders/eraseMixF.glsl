#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D bg;
layout(bindless_sampler, location = 1) uniform sampler2D eraser;
layout(location = 0) out vec4 Ci;

void main()
{
    vec4 bgT = texture(bg, v.uv);
    vec4 eraserT = texture(eraser, v.uv);

    if (eraserT.a > 0.f)
        Ci = vec4(0.f);

    else
        Ci = bgT;
}
