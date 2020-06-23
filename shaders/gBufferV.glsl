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
    vec3 T_VS, N_VS, N_VS_ssao, P_WS;
	vec3 boneWeightViz;
    vec4 shadowCoord0, shadowCoord1, shadowCoord2, shadowCoord3;
} v;

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;
layout(location = 4) in ivec4 boneIdE;
layout(location = 5) in vec4 boneWtE;

uniform mat3 NM;
uniform mat4 MVP, MM;
uniform vec4 comboU2; //(myAbj.lightCt, myAbj.dudvTime, ssrInten->val_f, 0.f);

vec4 P_WS = MM * vec4(pE, 1.f);

float VectorToDepth (vec3 Vec)
{
    vec3 AbsVec = abs(Vec);
    float LocalZcomp = max(AbsVec.x, max(AbsVec.y, AbsVec.z));

    const float f = 100.f;
    const float n = 1.f;

    float NormZComp = (f + n) / (f - n) - (2.f * f * n) / (f - n) / LocalZcomp;

    return (NormZComp + 1.f) * .5f;
}

vec4 getShadowCoords(int idx)
{
    vec4 myShadowCoords;
	  
    if (light[idx].Cl_type.w == 2.f) //POINT
    {
        vec3 lightDir = P_WS.xyz - light[idx].P_WS.xyz;

        myShadowCoords = vec4(lightDir, VectorToDepth(lightDir));
    }

    else //DIR / SPOT
        myShadowCoords = light[idx].ShadowCoord * vec4(pE, 1.f);

    return myShadowCoords;
}

void main()
{
	gl_Position = MVP * vec4(pE, 1.f);

	//v.boneWeightViz = vec3(0.f);
	//v.boneWeightViz = vec3(1.f, 0.f, 0.f);
	v.boneWeightViz = vec3(1.f);


    v.T_VS = normalize(NM * tE);
    v.N_VS = normalize(NM * nE);

	v.N_VS_ssao = v.N_VS;
	v.P_WS = P_WS.xyz;
    v.uv = uvE;

    for (int i = 0; i < comboU2.x; ++i)
    {
        if (i == 0)
            v.shadowCoord0 = getShadowCoords(i);

		else if (i == 1)
            v.shadowCoord1 = getShadowCoords(i);

		else if (i == 2)
            v.shadowCoord2 = getShadowCoords(i);

		else if (i == 3)
            v.shadowCoord3 = getShadowCoords(i);
    }

}