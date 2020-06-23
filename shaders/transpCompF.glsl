/*
reference:
    http://casual-effects.blogspot.com/2014/03/weighted-blended-order-independent.html
    http://casual-effects.blogspot.com/2015/03/implemented-weighted-blended-order.html
    http://casual-effects.blogspot.com/2015/03/colored-blended-order-independent.html
    http://jcgt.org/published/0002/02/09/
*/

#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D gBuf7;
layout(location = 0) out vec4 Ci;

uniform vec4 comboU0; //vec4(depthScale, debug0, 0.f, 0.f)

void main()
{
    Ci = texture(gBuf7, v.uv); //
}