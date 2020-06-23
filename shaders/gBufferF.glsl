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
    vec3 T_VS, N_VS, N_VS_ssao, P_WS;
	vec3 boneWeightViz;
    vec4 shadowCoord0, shadowCoord1, shadowCoord2, shadowCoord3;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D albedo;
layout(bindless_sampler, location = 1) uniform sampler2D alpha;
layout(bindless_sampler, location = 2) uniform sampler2D aniso;
layout(bindless_sampler, location = 3) uniform sampler2D metallic;
layout(bindless_sampler, location = 4) uniform sampler2D normal;
layout(bindless_sampler, location = 5) uniform sampler2D ruff;
layout(bindless_sampler, location = 6) uniform sampler2D dudv;
//layout(binding = 7) uniform samplerCube cubeSpecMs;
//layout(binding = 8) uniform samplerCube cubeIrrMs;
layout(binding = 9) uniform samplerCubeShadow shadowPM0;
layout(binding = 10) uniform samplerCubeShadow shadowPM1;
layout(bindless_sampler, location = 11) uniform sampler2DShadow shadowM0;
layout(bindless_sampler, location = 12) uniform sampler2DShadow shadowM1;

layout(location = 0) out vec4 gBuf0;
layout(location = 1) out uvec4 gBuf1;
layout(location = 2) out uvec4 gBuf2;
layout(location = 3) out uvec4 gBuf3;
layout(location = 4) out uvec4 gBuf4;
layout(location = 5) out uvec4 gBuf5;
layout(location = 6) out uvec4 gBuf6;
layout(location = 7) out uvec4 gBuf7;

uniform float anisoType;
uniform vec4 albedoAlphaTile, metallicRuffTile, normalTile, anisoReplaceMeTile;
uniform vec4 comboU0; //vec4(ior, ruffOren->val_f, Ko->val_f, 0.f)
uniform vec4 comboU1; //vec4(ruffA->val_2, shadowCastF, rippleF)
uniform vec4 comboU2; //(myAbj.lightCt, myAbj.dudvTime, 0.f, 0.f);
uniform mat4 MM;

vec4 allShadowCoords[2] = { v.shadowCoord0, v.shadowCoord1 };
sampler2DShadow allSampler2DShadow[2] = { shadowM0, shadowM1 };
samplerCubeShadow allSamplerCubeShadow[2] = { shadowPM0, shadowPM1 };
int sampler2DShadowIdx = 0;
int samplerCubeShadowIdx = 0;
int pointShadowLimit = 2;

vec4 poissonDisk[4] = vec4[](
  vec4( -0.94201624, -0.39906216, 0.f, 0.f ),
  vec4( 0.94558609, -0.76890725, 0.f, 0.f ),
  vec4( -0.094184101, -0.92938870, 0.f, 0.f ),
  vec4( 0.34495938, 0.29387760, 0.f, 0.f )
);

float getAniso(float type)
{
    if (type == 2.f) // CUSTOM MAP
		return texture(aniso, anisoReplaceMeTile.xy * v.uv).r;

    else
        return type; //BLANK (0) / VIEW (1)
}

float calcShadow(int idx)
{
    float myShadow;

    if (light[idx].Cl_type.w == 2.f) //POINT
    {
		//float bias = .01f;
		//allShadowCoords[idx].z -= bias;

  //      if (samplerCubeShadowIdx >= pointShadowLimit)
  //          myShadow = 999.f;

  //      else
  //          myShadow = texture(allSamplerCubeShadow[samplerCubeShadowIdx], allShadowCoords[idx]);

  //      ++samplerCubeShadowIdx;

		myShadow = 1.f;
    }

	else //DIR / SPOT
    {
		float bias = .01f; //DIR

		if (light[idx].Cl_type.w == 3.f) //SPOT
		{
			vec3 N_WS = (inverse(scene.VM) * vec4(v.N_VS, 0.f)).xyz;
			vec3 L_WS = normalize(light[idx].P_WS.xyz - v.P_WS);
			float diff0 = max(dot(N_WS, L_WS), 0.f);
			float diff = dot(N_WS, L_WS);
			bias = max(.05f * (1.f - diff), .01f);
		}

		allShadowCoords[idx].z -= bias;

        float myShadowProj = textureProj(allSampler2DShadow[sampler2DShadowIdx], allShadowCoords[idx]);
		//myShadow = (myShadowProj == 1.f) ? 1.f : 0.f;
		//myShadow = (myShadowProj == 1.f) ? 1.f : 0.1f;
		myShadow = (myShadowProj == 1.f) ? 1.f : 0.05f;



        ++sampler2DShadowIdx;
    }

    return myShadow;
}

void main()
{
    vec3 albedoT = texture(albedo, albedoAlphaTile.rg * v.uv).rgb;
	albedoT = pow(albedoT, vec3(2.2f)); //gamma space input tex req decoding

    float anisoM  = getAniso(anisoType);
    float alphaT = texture(alpha, albedoAlphaTile.ba * v.uv).r * comboU0.z;
    float metallicT = texture(metallic, metallicRuffTile.rg * v.uv).r;

    float ruffT = texture(ruff, metallicRuffTile.ba * v.uv).r;
    ruffT = pow(ruffT, 2.2f); ////gamma space input tex req decoding

	/* DUDV RIPPLE */
	float uvTileDuDv = 4.f;
	float waveDepth = .04f;
	vec2 distortedUV = texture(dudv, uvTileDuDv * vec2(v.uv.x + comboU2.y, v.uv.y)).rg * waveDepth;
	distortedUV = v.uv + vec2(distortedUV.x, distortedUV.y + comboU2.y);

	vec2 dudvT = (texture(dudv, uvTileDuDv * vec2(v.uv.x + comboU2.y, v.uv.y)).rg * 2.f - 1.f) * waveDepth;
	vec2 dudvT2 = (texture(dudv, uvTileDuDv * vec2(-v.uv.x + comboU2.y, v.uv.y + comboU2.y)).rg * 2.f - 1.f) * waveDepth;
	dudvT += dudvT2;


    vec3 N_TS = normalize(texture(normal, normalTile.rg * v.uv).rgb * 2.f - 1.f);
    N_TS = vec3(N_TS.r, -N_TS.g, N_TS.b);
    //N_TS = vec3(N_TS.r * normalTile.b, N_TS.g * normalTile.b, N_TS.b);

	if (texture(dudv, v.uv).rg != vec2(0.f))
	{
		/*REG TAN NORMAL, FLATTER */
		N_TS = normalize(texture(normal, normalTile.rg * distortedUV).rgb * 2.f - 1.f);
		N_TS = vec3(N_TS.r, -N_TS.g, N_TS.b);
		//N_TS = vec3(N_TS.r * normalTile.b, N_TS.g * normalTile.b, N_TS.b);
	}

    float shadowRead0, shadowRead1, shadowRead2, shadowRead3;

    for (int i = 0; i < comboU2.x; ++i)
    {
        if (i == 0)
            shadowRead0 = calcShadow(i);

		else if (i == 1)
            shadowRead1 = calcShadow(i);

		else if (i == 2)
            shadowRead2 = calcShadow(i);

		else if (i == 3)
            shadowRead3 = calcShadow(i);
    }

    ///////////
	gBuf0 = vec4(N_TS, gl_FrontFacing); //determine front / back face
	//gBuf0 = vec4(1.f);
	//gBuf0 = vec4(0.f, 1.f, 0.f, 1.f);



    gBuf1.x = packHalf2x16(v.T_VS.rg);
    gBuf1.y = packHalf2x16(vec2(v.T_VS.b, v.N_VS.r));
    gBuf1.z = packHalf2x16(vec2(v.N_VS.g, v.N_VS.b));
    gBuf1.w = packHalf2x16(vec2(0.f));

    gBuf2.x = packHalf2x16(albedoT.rg);
    gBuf2.y = packHalf2x16(vec2(albedoT.b, metallicT));
    gBuf2.z = packHalf2x16(vec2(ruffT, alphaT));
    gBuf2.w = packHalf2x16(v.uv); //

    gBuf3.x = packHalf2x16(vec2(comboU0.xy));
    gBuf3.y = packHalf2x16(vec2(comboU0.zw));
    gBuf3.z = packHalf2x16(vec2(comboU1.xy));
    gBuf3.w = packHalf2x16(vec2(comboU1.zw));

    gBuf4.x = packHalf2x16(vec2(0.f, 0.f));
    gBuf4.y = packHalf2x16(vec2(anisoM, 0.f));
    gBuf4.z = packHalf2x16(vec2(shadowRead0, shadowRead1));
    gBuf4.w = packHalf2x16(vec2(shadowRead2, shadowRead3));

	gBuf5.x = packHalf2x16(dudvT);
    gBuf5.y = packHalf2x16(vec2(v.N_VS_ssao.xy));
    gBuf5.z = packHalf2x16(vec2(v.N_VS_ssao.z, 1.f));
    gBuf5.w = packHalf2x16(v.boneWeightViz.yz);

	gBuf6.x = packHalf2x16(vec2(0.f));
	gBuf6.y = packHalf2x16(vec2(0.f));
	gBuf6.z = packHalf2x16(vec2(1.f));
	gBuf6.w = packHalf2x16(vec2(0.f));
}