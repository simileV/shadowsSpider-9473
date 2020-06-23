/*
reference:
    https://en.wikipedia.org/wiki/Sobel_operator
    GLSL Cookbook Chp 5 Image Processing and Screen Space Techniques pg 153 - 157
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
out vec4 Ci;

uniform vec4 comboU0; // vec4(edgeDetect_mode, edgeThr, 0.f, 0.f)
vec2 texelSize = 1.f / textureSize(tex, 0);

uniform mat3 G2[2] = mat3[]
(
    mat3(1.f, 2.f, 1.f, 0.f, 0.f, 0.f, -1.f, -2.f, -1.f),
    mat3(1.f, 0.f, -1.f, 2.f, 0.f, -2.f, 1.f, 0.f, -1.f)
);

uniform mat3 G9[9] = mat3[]
(
    mat3(0.353553, 0.0, -0.353553, 0.5, 0.0, -0.5, 0.353553, 0.0, -0.353553),
    mat3(0.353553, 0.5, 0.353553, 0.0, 0.0, 0.0, -0.353553, -0.5, -0.353553),
    mat3(0.0, 0.353553, -0.5, -0.353553, 0.0, 0.353553, 0.5, -0.353553, 0.0),
    mat3(0.5, -0.353553, 0.0, -0.353553, 0.0, 0.353553, 0.0, 0.353553, -0.5),
    mat3(0.0, -0.5, 0.0, 0.5, 0.0, 0.5, 0.0, -0.5, 0.0),
    mat3(-0.5, 0.0, 0.5, 0.0, 0.0, 0.0, 0.5, 0.0, -0.5),
    mat3(0.166667, -0.333333, 0.166667, -0.333333, 0.666667, -0.333333, 0.166667, -0.333333, 0.166667),
    mat3(-0.333333, 0.166667, -0.333333, 0.166667, 0.666667, 0.166667, -0.333333, 0.166667, -0.333333),
    mat3(0.333333, 0.333333, 0.333333, 0.333333, 0.333333, 0.333333, 0.333333, 0.333333, 0.333333)
);

void main()
{
    if (comboU0.x == 0.f) // SOBEL
    {
        mat3 I;
        float cnv[2];
        vec3 mySample;

        /* fetch the 3x3 neighbourhood and use the RGB vector's length as intensity value */
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                mySample = texture(tex, v.uv + texelSize * vec2(i - 1.f, j - 1.f)).rgb;
                I[i][j] = length(mySample);
            }
        }

        /* calculate the convolution values for all the masks */
        for (int i = 0; i < 2; ++i)
        {
            float dp3 = dot(G2[i][0], I[0]) + dot(G2[i][1], I[1]) + dot(G2[i][2], I[2]);
            cnv[i] = dp3 * dp3;
        }

        float dist = sqrt(cnv[0] * cnv[0] + cnv[1] * cnv[1]);

        if (dist > comboU0.y)
            Ci = vec4(1.f);

        else
            Ci = vec4(0.f);
    }

    else if (comboU0.x == 1.f) // Rastergrid Frei-Chen with pre-computed mat3 values
    {
        mat3 I;
        float cnv[9];
        vec3 mySample;

        /* fetch the 3x3 neighbourhood and use the RGB vector's length as intensity value */
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                mySample = texture(tex, v.uv + texelSize * vec2(i - 1.f, j - 1.f)).rgb;
                I[i][j] = length(mySample);
            }
        }

        /* calculate the convolution values for all the masks */
        for (int i = 0; i < 9; ++i)
        {
            float dp3 = dot(G9[i][0], I[0]) + dot(G9[i][1], I[1]) + dot(G9[i][2], I[2]);
            cnv[i] = dp3 * dp3;
        }

        float M = (cnv[0] + cnv[1]) + (cnv[2] + cnv[3]);
        float S = (cnv[4] + cnv[5]) + (cnv[6] + cnv[7]) + (cnv[8] + M);

        float dist = sqrt(M / S);

        if (dist > comboU0.y)
            Ci = vec4(1.f);

        else
            Ci = vec4(0.f);
    }
}
