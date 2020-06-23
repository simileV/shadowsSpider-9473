#version 450 core

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;

uniform mat3 NM;
uniform mat4 MVP, MV;
uniform vec4 parentCl;

out Vert
{
    vec2 uv;
    vec3 parentCl, n, p, i;
} v;

void main()
{
    gl_Position = MVP * vec4(pE, 1.f);
    v.p = vec3(MV * vec4(pE, 1.f));

    v.n = normalize(NM * nE);

    v.parentCl = parentCl.rgb;
    v.uv = uvE;

    v.i = vec3(MV * vec4(pE, 1.f));
}
