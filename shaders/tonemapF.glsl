/*
reference:
    http://content.gpwiki.org/index.php/D3DBook:High-Dynamic_Range_Rendering#Luminance_History_Function e10 - auto exp
*/

#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif
#pragma optimize (off)

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D bloom;
layout(bindless_sampler, location = 1) uniform sampler2D luma;
layout(bindless_sampler, location = 2) uniform sampler2D giz;
layout(location = 0) out vec3 Ci;
layout(location = 1) out vec3 Ci_noGiz;

uniform vec4 comboU0; //vec4(expo, adaptAuto, vign, vignDist)
uniform vec4 comboU1; //vec4(myAbj.debug0, 0.f, 0.f, 0.f);

float log10(float x)
{
    return log2(x) / log2(10);
}

vec3 filmicHabel(vec3 x)
{
    float A = .15f;
    float B = .5f;
    float C = .1f;
    float D = .2f;
    float E = .02f;
    float F = .3f;

    return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
}

float vignetteOverlay(vec2 pos, float inner, float outer)
{
    float r = length(pos);

    return 1.f - smoothstep(inner, outer, r);
}

void main()
{
    vec4 bloomT = texture(bloom, v.uv);
	float lumaT = clamp(exp(textureLod(luma, v.uv, 10.f).r), .001f, .999f);

    if (comboU0.z == 1.f)
        bloomT.rgb *= vignetteOverlay(v.uv * 2.f - 1.f, .55f, comboU0.w);

    float expoAdapt = comboU0.x;

    if (comboU0.y == 1.f)
        expoAdapt = 1.03f - (2.f / (2.f + log10(lumaT + 1.f)));

    Ci = bloomT.rgb * expoAdapt / lumaT;
    Ci = filmicHabel(Ci) / filmicHabel(vec3(11.2f));
    Ci_noGiz = Ci;

    vec4 gizT = texture(giz, v.uv);
    Ci = mix(Ci.rgb, gizT.rgb, gizT.a);

	///////////////////////////////////////////////////

	//if (comboU1.x == 1.f)
		//Ci = bloomT.rgb;
		//Ci = vec3(1.f, 0.f, 0.f);

	//Ci = mix(Ci.rgb, gizT.rgb, gizT.a);

	//Ci = vec3(1.f, 1.f, 0.f);
	//Ci = vec3(lumaT);
	//Ci = vec3(expoAdapt);
	//Ci = texture(luma, v.uv).rgb;
	//Ci = vec3(texture(luma, v.uv).r);
	//Ci = vec3(textureLod(luma, v.uv, 5.5f).r);
}

