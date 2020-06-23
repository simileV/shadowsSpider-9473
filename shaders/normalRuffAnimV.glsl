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
    vec3 N_VS;
} v;

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;
layout(location = 4) in ivec4 boneIdE;
layout(location = 5) in vec4 boneWtE;

uniform mat3 NM;
uniform mat4 MVP, MM;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

vec4 P_WS = MM * vec4(pE, 1.f);

void main()
{
	mat4 BoneTransform	   = gBones[boneIdE[0]] * boneWtE[0];
	BoneTransform     += gBones[boneIdE[1]] * boneWtE[1];
	BoneTransform     += gBones[boneIdE[2]] * boneWtE[2];
	BoneTransform     += gBones[boneIdE[3]] * boneWtE[3];

	gl_Position = MVP * BoneTransform * vec4(pE, 1.f);

	vec4 N_VS4 = normalize(mat4(NM) * BoneTransform * vec4(nE, 0.f)); //
	v.N_VS = N_VS4.xyz;

    v.uv = uvE;
}