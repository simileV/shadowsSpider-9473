/*
reference:
    http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
*/

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

uniform int gaussStage;

float offset[3] = float[3](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[3](0.2270270270, 0.3162162162, 0.0702702703);
vec2 texelSize = 1.f / textureSize(tex, 0);

void main()
{
    Ci = texture(tex, v.uv) * weight[0];

    for (int i = 1; i < 3; ++i)
    {
        if (gaussStage == 0) //vertical
        {
            Ci += texture(tex, v.uv + vec2(0.f, offset[i]) * texelSize) * weight[i];
            Ci += texture(tex, v.uv - vec2(0.f, offset[i]) * texelSize) * weight[i];
        }

        else if (gaussStage == 1) //horizontal
        {
            Ci += texture(tex, v.uv + vec2(offset[i], 0.f) * texelSize) * weight[i];
            Ci += texture(tex, v.uv - vec2(offset[i], 0.f) * texelSize) * weight[i];
        }
    }
}
