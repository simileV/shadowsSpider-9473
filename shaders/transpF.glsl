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

struct LightData
{
	vec4 Cl_type, falloff, DirRot, P_WS;
	mat4 ShadowCoord;
};

struct SceneData
{
	mat4 PM, PMinv, VM, VMinv, VPM;
	vec4 comboU0; //vec4(Kgi, NUM_LIGHTS, debug0, 0.f)
};

struct DebugData
{
	vec4 comboU0, comboU1;
};


#if defined(GL_core_profile)
layout(std140, binding = 0) uniform lightBuffer
{
	LightData light[50]; //indexed
};

layout(std140, binding = 1) uniform sceneBuffer
{
	SceneData scene;
};

layout(std140, binding = 2) uniform debugBuffer
{
	DebugData debug;
};

#endif

in Vert
{
    vec2 uv;
    float myDepth;
	vec3 T_VS, N_VS, P_WS, P_VS;
    vec4 shadowCoord0, shadowCoord1, shadowCoord2, shadowCoord3, P_WSLightSpace;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D albedo;
layout(bindless_sampler, location = 1) uniform sampler2D alpha;
layout(bindless_sampler, location = 4) uniform sampler2D normal;


layout(location = 0) out vec4 Ci;

uniform bool debugTgl0;

uniform vec4 comboU0; //vec4(ior, ruffOren->val_f, Ko->val_f, depthScale / transpW)
uniform vec4 comboU1; //vec4(ruffA->val_2, shadowCastF, rippleF)
uniform vec4 comboU2; //vec4(myAbj.lightCt, myAbj.dudvTime, 0.f, myAbj.myFSQ->Kgi->val_f);
uniform vec4 albedoAlphaTile, metallicRuffTile, normalTile, anisoReplaceMeTile;
uniform mat4 MVP, MV, MM;

void main()
{
    vec3 albedoM = texture(albedo, albedoAlphaTile.rg * v.uv).rgb;
    albedoM = pow(albedoM, vec3(2.2f)); //gamma space input tex req decoding

    float alphaM = texture(alpha, albedoAlphaTile.ba * v.uv).r * comboU0.z;

	Ci = vec4(0.f, 1.f, 0.f, alphaM);

	if (Ci.a < .01)
		discard; //
}