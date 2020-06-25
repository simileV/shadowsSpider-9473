#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D fxaa;
layout(bindless_sampler, location = 1) uniform sampler2D ssr;
layout(bindless_sampler, location = 2) uniform sampler2D cursor;
layout(bindless_sampler, location = 3) uniform sampler2D deferred;
layout(bindless_sampler, location = 4) uniform sampler2D brush;
layout(bindless_sampler, location = 5) uniform sampler2D normalRuff1; 
layout(bindless_sampler, location = 6) uniform sampler2D gBuf7; //BOIT reveal
layout(bindless_sampler, location = 7) uniform sampler2D bill;
layout(bindless_sampler, location = 8) uniform sampler2D tonemap;
layout(bindless_sampler, location = 9) uniform sampler2D bg;
layout(bindless_sampler, location = 10) uniform sampler2D gBuf6; //transp

//layout(bindless_sampler, location = 11) uniform sampler2D blurredBloom;
//layout(binding = 12) uniform sampler2D blurredBloom2;
//layout(bindless_sampler, location = 13) uniform sampler2D bloomPlusColor;
out vec3 Ci;

uniform vec4 LDRU;
uniform vec4 comboU0; //vec4(rezGateTgl, dragDrop, debug0, myAbj.dudvTime)
uniform vec4 comboU1; //vec4(farClip, nearClip, myAbj.showHideTaskbar, 0.f)

float rezGateAlpha(vec2 uv, vec2 pLD, vec2 pRU, float dragDrop)
{
    if ((uv.x < pLD.x || uv.x > pRU.x || uv.y < pLD.y || uv.y > pRU.y) || (dragDrop == 1.f))
        return .2f;

    else
        return 1.f;

    return 0.f;
}

float CalcLuma(vec3 rgb)
{
    vec3 luma = vec3(.299f, .587f, .114f);
    luma = pow(luma, vec3(1.f / 2.2f)); //linearize

    return dot(rgb, luma);
}

void main() //3D 
{
    float revealageT = texture(gBuf7, v.uv).x; // !!!!!!!!!
	float ssrInten = texture(normalRuff1, v.uv).r;
	//Ci = texture(fxaa, v.uv).rgb + (revealageT * (ssrInten * texture(ssr, v.uv).rgb));

	Ci = texture(fxaa, v.uv).rgb + (ssrInten * texture(ssr, v.uv).rgb);

//	Ci = texture(ssr, v.uv).rgb;
//	Ci = texture(fxaa, v.uv).rgb;

	//Ci = ssrInten * texture(ssr, v.uv).rgb;
	//Ci = texture(ssr, v.uv).rgb;

	//Ci = texture(gBuf6, v.uv).rgb;


	//Ci = texture(deferred, v.uv).rgb; //FXAA TEST
	//Ci = texture(fxaa, v.uv).rgb + (revealageT);
	//Ci = texture(fxaa, v.uv).rgb;
	//Ci = vec3(0.f, 1.f, 0.f);

	//float toGray = CalcLuma(Ci);
	//Ci = vec3(toGray, 0.f, 0.f);
	//Ci = vec3(0.f, toGray, toGray);

	//if (v.uv.x < .5f)
	//{
	//	vec4 
	//	//Ci = vec3(0.01f);
	//	Ci = vec3(0.f);
	//}

	//else
	//{
	//	Ci = vec3(0.001f);
	//	//Ci = vec3(0.2f);
	//}

	//if (comboU0.z == 1)
	//{
	//}

	//Ci = vec3(1.f, 0.f, 0.f);




	//if (comboU0.z == 0.f)
	//	Ci = texture(asdasd, v.uv).rgb;

	//else if (comboU0.z == 1.f)
	//	Ci = texture(asdasd, v.uv).rgb;

    if (comboU0.x == 1.f)
	{
        Ci *= rezGateAlpha(v.uv, LDRU.xy, LDRU.zw, comboU0.y);
	}

	Ci = pow(Ci, vec3(1.f / 2.2f));
}