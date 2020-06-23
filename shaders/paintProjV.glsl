#version 450 core

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;

uniform mat3 NM;
uniform mat4 MVP, MM, ProjectorM;

out Vert
{
    vec2 uv;
    vec3 N_VS;
    vec4 bakeCoord;
} v;

void main()
{
    vec2 transformUV = uvE * 2.f - 1.f;
    gl_Position = vec4(transformUV, 0.f, 1.f);

    v.uv = uvE;
    v.N_VS = normalize(NM * nE);
    v.bakeCoord = ProjectorM * vec4(pE, 1.f);
}
