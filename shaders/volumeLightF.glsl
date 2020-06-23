/*
reference:
    http://john-chapman-graphics.blogspot.com/2013/01/good-enough-volumetrics-for-spotlights.html
*/

#version 450 core

in Vert
{
    vec2 uv;
    vec3 parentCl, n, p, i;
} v;

layout(location = 0) out vec4 rttC;
out vec4 Ci;

uniform vec4 comboU0; //vec4(volTipView, volDist)

void main()
{
    vec3 Nn = normalize(v.n);
    vec3 V = -normalize(v.i);

    float softEdge = abs(dot(Nn, V));
    softEdge = pow(softEdge, 4);

    float dist = distance(v.p, comboU0.xyz);
    float atten = 1.f - (dist / comboU0.w);
    atten = clamp(atten, 0.f, 1.f);

    rttC = vec4(v.parentCl * atten * softEdge, 1.f);
}
