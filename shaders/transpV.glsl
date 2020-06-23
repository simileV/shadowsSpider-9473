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

out Vert
{
    vec2 uv;
    float myDepth;
	invariant vec3 T_VS, N_VS, P_WS, P_VS;
    vec4 shadowCoord0, shadowCoord1, shadowCoord2, shadowCoord3, P_WSLightSpace;
} v;

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;

uniform mat3 NM;
uniform mat4 MVP, MV, MM;
uniform vec4 comboU2; //(myAbj.lightCt, myAbj.dudvTime, ssrInten->val_f, 0.f);
uniform mat4 lightSpaceM;

vec4 P_WS = MM * vec4(pE, 1.f);


void main()
{
    gl_Position = MVP * vec4(pE, 1.f);
    v.uv = uvE;
    v.myDepth = -(MV * vec4(pE, 1.f)).z;

	v.T_VS = normalize(NM * tE);
    v.N_VS = normalize(NM * nE);
	v.P_WS = P_WS.xyz;
	v.P_VS = (MV * vec4(pE, 1.f)).xyz;


	v.P_WSLightSpace = lightSpaceM * P_WS; //

}