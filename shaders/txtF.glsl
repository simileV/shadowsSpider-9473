/*
reference:
    http://github.prideout.net/strings-inside-vertex-buffers/
*/

#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Geo
{
    vec2 uv;
} g;

layout(bindless_sampler, location = 0) uniform sampler2D txtAtlasT;
out vec4 Ci;

uniform vec4 Ctxt;

void main()
{
    float A = texture(txtAtlasT, g.uv).r;

    Ci = vec4(Ctxt.rgb, A);
}
