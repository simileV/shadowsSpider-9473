/*
reference:
    https://mynameismjp.wordpress.com/2009/03/10/reconstructing-position-from-depth/
	http://www.iquilezles.org/www/articles/fog/fog.htm
	http://in2gpu.com/2014/07/22/create-fog-shader/
	http://www.geeks3d.com/20110316/shader-library-simple-2d-effects-sphere-and-ripple-in-glsl/
	https://gist.github.com/Kuranes/3065139b10f2d85074da
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
} v;

layout(bindless_sampler, location = 0) uniform sampler2D gBuf0;
layout(bindless_sampler, location = 1) uniform usampler2D gBuf1;
layout(bindless_sampler, location = 2) uniform usampler2D gBuf2;
layout(bindless_sampler, location = 3) uniform usampler2D gBuf3;
layout(bindless_sampler, location = 4) uniform usampler2D gBuf4;
layout(bindless_sampler, location = 5) uniform usampler2D gBuf5;
layout(bindless_sampler, location = 8) uniform sampler2D ssao;
layout(bindless_sampler, location = 9) uniform sampler2D sky;
layout(binding = 10) uniform samplerCube cubeSpecMs;
layout(binding = 11) uniform samplerCube cubeIrrMs;
layout(binding = 12) uniform sampler2D gBuf_DS;

layout(location = 0) out vec4 Ci;
layout(location = 1) out vec4 Ci_dudv;

uniform mat4 MV;
uniform vec4 comboU0; //vec4(Kgi, NUM_LIGHTS, debug0, 0.f)
uniform vec4 farNearClip;
uniform float time;

int pointShadowLimit = 2;
int pointShadowIdx = 0;

vec3 reconstructP(vec2 UV)
{
    vec4 vProjectedPos = vec4(1.f);
    vProjectedPos.rg = UV * 2.f - 1.f;
    vProjectedPos.b = texture(gBuf_DS, UV).r * 2.f - 1.f;
    vec4 vPositionVS = scene.PMinv * vProjectedPos;

    return vPositionVS.rgb / vPositionVS.a;
}

float Linear01Depth(float myDepth)
{
    vec2 _ZBufferParams;
    float fn = farNearClip.x / farNearClip.y;

    _ZBufferParams.x = 1.f - fn;
    _ZBufferParams.y = fn;

    return 1.f / (_ZBufferParams.x * myDepth + _ZBufferParams.y);
}

vec3 N_TS = texture(gBuf0, v.uv).rgb;
float twoSided = texture(gBuf0, v.uv).a; //
vec3 P_VS = reconstructP(v.uv);

uvec4 data1 = texelFetch(gBuf1, ivec2(gl_FragCoord.xy), 0);
vec3 T_VS = vec3(unpackHalf2x16(data1.x), unpackHalf2x16(data1.y).x);
vec3 N_VS = vec3(unpackHalf2x16(data1.y).y, unpackHalf2x16(data1.z));
vec3 B_VS = cross(N_VS, T_VS);

uvec4 data2 = texelFetch(gBuf2, ivec2(gl_FragCoord.xy), 0);
vec3 albedoM = vec3(unpackHalf2x16(data2.x), unpackHalf2x16(data2.y).x);
float metallicM = unpackHalf2x16(data2.y).y;
//float ruffM = unpackHalf2x16(data2.z).x;
float ruffM = max(.008f, unpackHalf2x16(data2.z).x);
//float ruffM = max(.08f, unpackHalf2x16(data2.z).x);
float alphaM = unpackHalf2x16(data2.z).y;
vec2 uv_VS = unpackHalf2x16(data2.w);

uvec4 data3 = texelFetch(gBuf3, ivec2(gl_FragCoord.xy), 0);
float ior = unpackHalf2x16(data3.x).x;
float eta = 1.f / ior;
float ruffOren = unpackHalf2x16(data3.x).y;
float Ko = unpackHalf2x16(data3.y).x;
vec2 ruffA = unpackHalf2x16(data3.z);
float shadowCast = unpackHalf2x16(data3.w).x;
float ripple = unpackHalf2x16(data3.w).y;

uvec4 data4 = texelFetch(gBuf4, ivec2(gl_FragCoord.xy), 0);
//float replaceMe = unpackHalf2x16(data4.x).x;
float anisoM = unpackHalf2x16(data4.y).x;
float shadow0 = unpackHalf2x16(data4.z).x;
float shadow1 = unpackHalf2x16(data4.z).y;
float shadow2 = unpackHalf2x16(data4.w).x;
float shadow3 = unpackHalf2x16(data4.w).y;
//float allShadows[1] = { shadow0 }; //
//float allShadows[2] = { shadow0, shadow1 }; //
float allShadows[4] = { shadow0, shadow1, shadow2, shadow3 }; //

uvec4 data5 = texelFetch(gBuf5, ivec2(gl_FragCoord.xy), 0);
vec2 dudv = unpackHalf2x16(data5.x);
vec3 boneWeightViz = vec3(unpackHalf2x16(data5.z).y, unpackHalf2x16(data5.w));
vec3 animVizTemp = vec3(unpackHalf2x16(data5.z).y);

mat3 TBN = mat3(T_VS, B_VS, N_VS);
vec3 eye_TS = normalize(P_VS) * TBN;
vec3 eye_VS = normalize(P_VS);
vec3 V_TS = normalize(vec3(dot(-P_VS, T_VS), dot(-P_VS, B_VS), dot(-P_VS, N_VS)));
vec3 V_VS = -P_VS;
float NdotV_TS = dot(N_TS, V_TS);
float NdotV_VS = dot(N_VS, V_VS);
const float PI = 3.1416f;

vec3 fog(in vec3 rgb)
{
	float distance = Linear01Depth(texture(gBuf_DS, v.uv).r);
	distance = length(distance);

	float density = 40.f;

	float fogAmt = 1.f - exp(-distance * density);
	fogAmt = clamp(fogAmt, 0.f, 1.f);
	
	vec3 fogColor = vec3(.5f, .6f, .7f);

	return mix(rgb, fogColor, fogAmt);
}

vec3 ggxSmith(float NdotL, float HdotN, float LdotH)
{
	float D, G, G1, G2;
	float HdotN2 = HdotN * HdotN;
    float ruff2 = ruffM * ruffM;
	float ruff4 = ruff2 * ruff2;

	/* D */
	float denom = HdotN2 * (ruff4 - 1.f) + 1.f;
	D = ruff4 / (PI * denom * denom);

	/* F */
	vec3 F0 = (metallicM == 1.f) ? albedoM : vec3(.04f);
	vec3 F = F0 + (1.f - F0) * pow(1.f - max(LdotH, 0.f), 5.f); //schlick

	/* G */
	float r = ruffM + 1.f;
	float k = ruff2 / 8.f;

	float nom0 = NdotV_TS;
	float denom0 = NdotV_TS * (1.f - k) + k;

	float ggx0 = nom0 / denom0;

	float nom1 = NdotL;
	float denom1 = NdotL * (1.f - k) + k;
	float ggx1 = nom1 / denom1;

	G = ggx0 * ggx1;

	vec3 myGGX = D * F * G;

	return myGGX;
}

float G1V(float NdotL_or_NdotV, float k)
{
	return 1.f / (NdotL_or_NdotV * (1.f - k) + k);
}

vec3 ggx(float NdotL, float HdotN, float LdotH)
{
	float D, G, G1, G2;
	float HdotN2 = HdotN * HdotN;
    float ruff2 = ruffM * ruffM;
	float ruff4 = ruff2 * ruff2;
	float NdotL2 = NdotL * NdotL;
	float NdotV2 = NdotV_TS * NdotV_TS;

	/* D */
	float denom = HdotN2 * (ruff4 - 1.f) + 1.f;
	D = ruff4 / (PI * denom * denom);

	/* F */
	vec3 F0 = (metallicM == 1.f) ? albedoM : vec3(.04f);
	vec3 F = F0 + (1.f - F0) * pow(1.f - max(LdotH, 0.f), 5.f); //schlick

	/* G */
	float k = ruff2 / 2.f;
	float vis = G1V(LdotH, k) * G1V(LdotH, k);

	vec3 myGGX = D * F * vis;

	return myGGX;
}

float ggxAniso(float NdotL, float HdotT, float HdotB, float HdotN)
{
    float ruff2 = ruffM * ruffM;
	float NdotL2 = NdotL * NdotL;
	float NdotV2 = NdotV_VS * NdotV_VS;

    float G1 = 1.f / (NdotL + sqrt(ruff2 + (1 - ruff2) * NdotL2));
    float G2 = 1.f / (NdotV_VS + sqrt(ruff2 + (1 - ruff2) * NdotV2));
    float G = G1 * G2;

    float HdotT2 = pow(HdotT / ruffA.x, 2.f);
    float HdotB2 = pow(HdotB / ruffA.y, 2.f);

    float dDenom = (HdotT2 + HdotB2 / ruffM) + (HdotN * HdotN);
    float D = (1.f / PI) * (1.f / ruff2) * (1.f / (dDenom * dDenom));

    return clamp(D * G, 0.f, 25.f);
}

float oren(float NdotL, vec3 L)
{
    float ruffOren2 = ruffOren * ruffOren;
	
	//if (comboU0.z == 1.f)
	//{
	//    ruffOren2 = ruffM * ruffM;
	//}

    float A = 1.f - .5f * (ruffOren2 / (ruffOren2 + .33f));
    float B = .45f * (ruffOren2 / (ruffOren2 + .09f));

    float acosNdotV = acos(NdotV_TS);

    vec3 VperpN = normalize(V_TS - N_TS * NdotV_TS);
    float cos_phi = max(0.f, dot(VperpN, normalize(L - N_TS * NdotL)));
    float acosNdotL = acos(NdotL);
    float alpha = max(acosNdotL, acosNdotV);
    float beta = min(acosNdotL, acosNdotV);

    return NdotL * (A + B * cos_phi * sin(alpha) * tan(beta));
}

vec3 cubeRefl_TS()
{
    return mat3(scene.VMinv) * TBN * reflect(eye_TS, N_TS);
}

vec3 cubeRefl_VS()
{
    return mat3(scene.VMinv) * reflect(eye_VS, N_VS);
}

vec3 cubeRefr(float ca)
{
    return mat3(scene.VMinv) * TBN * refract(eye_TS, N_TS, eta + ca);
}

float calcSpot(vec3 dist, vec3 LDirRot, vec3 falloff)
{
    float angle = dot(normalize(dist), LDirRot);

    return clamp((angle - falloff.z) / (falloff.y - falloff.z), 0.f, 1.f);
}

float luma(vec3 col)
{
    return max(dot(col, vec3(.2125f, .7154f, .0721f)), .0001f);
}

float getShadow(int idx)
{
    float myShadow;

    if (light[idx].Cl_type.w == 2.f) //POINT
    {
        if (pointShadowIdx >= pointShadowLimit)
            myShadow = 1.f;

        else
			myShadow = allShadows[pointShadowIdx];

        ++pointShadowIdx;
    }

    else //DIR / SPOT
        myShadow = allShadows[idx];

    return myShadow;
}

void main()
{
	//if (comboU0.z == 1.f)
	//	ruffM = max(.008f, unpackHalf2x16(data2.z).x);


    /* DIRECT */
    vec3 sumDirect;
	float sumShadow;

    for (int i = 0; i < comboU0.y; ++i)
    {
		//vec3 L_VS = normalize(vec3(scene.VM * vec4(light[i].P_WS.xyz, 1.f)) - P_VS);
        vec3 L_VS = vec3(scene.VM * vec4(light[i].P_WS.xyz, 1.f)) - P_VS;
		//L_VS = normalize(L_VS);
        vec4 myLDirRot = -normalize(scene.VM * light[i].DirRot);

        float myAtten = light[i].falloff.x * 1.f / dot(L_VS, L_VS);

        if      (light[i].Cl_type.w == 1.f) L_VS = myLDirRot.xyz; //DIR

  //      float atten = 1.f;
		//if      (light[i].Cl_type.w == 1.f) atten = light[i].falloff.x; //DIR
  //      else if (light[i].Cl_type.w == 2.f) atten = myAtten; //POINT
  //      else if (light[i].Cl_type.w == 3.f) atten = calcSpot(L_VS, myLDirRot.xyz, light[i].falloff.xyz) * myAtten; //SPOT
  //      vec3 atten2 = atten * light[i].Cl_type.rgb;


          float atten = 1.f;
		if      (light[i].Cl_type.w == 1.f) atten = light[i].falloff.x; //DIR
        else if (light[i].Cl_type.w == 2.f) atten = myAtten; //POINT
        else if (light[i].Cl_type.w == 3.f) atten = calcSpot(L_VS, myLDirRot.xyz, light[i].falloff.xyz) * myAtten; //SPOT
		//else if (light[i].Cl_type.w == 3.f) atten = 1.f;
        vec3 atten2 = atten * light[i].Cl_type.rgb;


		L_VS = normalize(L_VS);
        vec3 L_TS = normalize(vec3(dot(L_VS, T_VS), dot(L_VS, B_VS), dot(L_VS, N_VS)));
        vec3 H_TS = normalize(L_TS + V_TS);
        vec3 H_VS = normalize(L_VS + V_VS);
		float LdotH = dot(L_TS, H_TS);
		float HdotV_TS = dot(H_TS, V_TS);
		float HdotV_VS = dot(H_VS, V_VS);

        float HdotN_TS = dot(H_TS, N_TS);
        float HdotN_VS = dot(H_VS, N_VS);
        float NdotL_TS = clamp(dot(N_TS, L_TS), 0, 100000);
        float NdotL_VS = clamp(dot(N_VS, L_VS), 0, 100000);

        float HdotT = dot(H_TS, T_VS);
        float HdotB = dot(H_TS, B_VS);

        vec3 metallicTint = (metallicM == 1.f) ? albedoM : vec3(1.f);
        vec3 directDiff, directSpec;

        if (anisoM == 0.f) //ANISOM == "BLANK"
        {
            directDiff = oren(NdotL_TS, L_TS) * albedoM;

			if (metallicM == 1.f)
				directDiff = vec3(0.f);

			//directSpec = ggx(NdotL_TS, HdotN_TS, LdotH) * metallicTint;
			directSpec = ggxSmith(NdotL_TS, HdotN_TS, LdotH) * metallicTint;

			sumShadow = getShadow(i);
        }

        else if (anisoM != 0.f) //ANISOM == "VIEW" (1) OR CUSTOM MAP
        {
            vec3 T_VS_use = T_VS;
            vec3 B_VS_use = B_VS;

            if (anisoM != 1.f) //CUSTOM MAP
            {
                vec3 anisoDir = vec3(1.f - anisoM, anisoM, 0.f);
                T_VS_use = normalize(cross(N_VS, vec3(anisoDir)));
                B_VS_use = normalize(cross(N_VS, T_VS_use));
            }

            float HdotT_VS = dot(H_VS, T_VS_use);
            float HdotB_VS = dot(H_VS, B_VS_use);

            directDiff = vec3(0.f);
			//directDiff = oren(NdotL_TS, L_TS) * albedoM;

			//if (NdotL_VS > 0.f)
				//directSpec = ggxAniso(NdotL_VS, HdotT_VS, HdotB_VS, HdotN_VS) * metallicTint;

            sumShadow = getShadow(i);
        }

		//if (comboU0.z == 1.f)
		//	directSpec = clamp(directSpec, 0.f, 5.f);


		//vec3 N_VS = vec3(unpackHalf2x16(data1.y).y, unpackHalf2x16(data1.z));
		//vec3 T_VS = vec3(unpackHalf2x16(data1.x), unpackHalf2x16(data1.y).x);
		//vec3 B_VS = cross(N_VS, T_VS);

		//sumDirect += albedoM;
		//sumDirect += N_VS;
		//sumDirect += T_VS;
		//sumDirect += B_VS;



        sumDirect += atten2 * sumShadow * (directSpec + directDiff); // WITH SHADOW
		//sumDirect += atten2 * 1.f * (directSpec + directDiff); // NO SHADOWS

		//sumDirect += atten2 * sumShadow * (directSpec);
		//sumDirect += atten2 * sumShadow * (directDiff);
		//sumDirect += atten2 * 1.f * (directSpec);
		//sumDirect += atten2 * sumShadow;
		
		//sumDirect = vec3(sumShadow); ///////////////////////////
		//sumDirect = vec3(shadow0);

		//sumDirect += directSpec;
		//sumDirect += directDiff;
		//sumDirect += atten2 * sumShadow * (directSpec);
		//sumDirect += atten2 * sumShadow * (directDiff);

		//sumDirect += atten2 * 1.f * (directDiff); //FBX TEST
		//sumDirect += (directDiff); //FBX TEST

		//sumDirect += vec3(NdotL_VS); //FBX TEST
		//sumDirect += albedoM; //FBX TEST
		//sumDirect += N_VS;
		//sumDirect += T_VS; //FBX TEST
		//sumDirect += vec3(1.f);
		//sumDirect += B_VS;
		//sumDirect += vec3(HdotT);


		//sumDirect += vec3(HdotN_VS);
		//sumDirect += vec3(.01f);

    }

    /* INDIRECT */
    vec3 indirDiff_TS, indirDiff_VS, indirSpec_TS, indirSpec_VS, indirRefr, sumIndirect;
    float mipIdx = ruffM * (textureQueryLevels(cubeSpecMs) - 1.f);
    float ssaoT = clamp(texture(ssao, v.uv).r, 0.f, 1.f);

	vec3 F0 = (metallicM == 1.f) ? albedoM : vec3(.04f);
	vec3 fresnelRefl_PMREM = F0 + (max(vec3(1.f -  ruffM), F0) - F0) * pow(1.f - NdotV_TS, 5.f);

	indirDiff_TS = (1.f - fresnelRefl_PMREM) * texture(cubeIrrMs, cubeRefl_TS()).rgb * albedoM * vec3(ssaoT); //
	//indirDiff_TS = texture(cubeIrrMs, cubeRefl_TS()).rgb * albedoM * ssaoT;
	//indirDiff_TS = vec3(ssaoT);

    //indirRefr = textureLod(cubeSpecMs, cubeRefr(0.f), mipIdx).rgb;
    indirSpec_TS = fresnelRefl_PMREM * textureLod(cubeSpecMs, cubeRefl_TS(), mipIdx).rgb;
	indirSpec_VS = fresnelRefl_PMREM * textureLod(cubeSpecMs, cubeRefl_VS(), mipIdx).rgb; 

    sumIndirect = (indirDiff_TS + indirSpec_TS) * comboU0.x; //////////
	
	//if (comboU0.z == 1.f)
	//{
	//	sumIndirect = (indirDiff_TS + indirSpec_TS) * .75f; //////////
	//}


	if (anisoM != 0.f) // !NONE
		sumIndirect = indirSpec_VS * (comboU0.x / 1.f);

    if (shadowCast == 1.f)
	{
		float sumShadow2;
		for (int i = 0; i < comboU0.y; ++i)
		{
			sumShadow2 = getShadow(i);

			if (sumShadow2 == 0.f)
			{
				//sumShadow2 = .005f;
				sumShadow2 = .04f;
			}

			sumIndirect *= sumShadow2;
		}
	}

    ///////////
    if (alphaM == 0.f)
        Ci = vec4(0.f);

    else
    {
        Ci = vec4(sumDirect + sumIndirect, alphaM); //
        //Ci = vec4(sumDirect, alphaM);
		//Ci = vec4(sumIndirect, alphaM);
		//Ci = vec4(0.f, 1.f, 0.f, 1.f);

		//Ci = vec4(vec3(ssaoT), alphaM);

		//Ci = vec4(fresnelRefl_PMREM, alphaM);

		//if (comboU0.z == 1.f)
		//	Ci = vec4(1.f - fresnelRefl_PMREM, alphaM);

		//Ci = vec4(boneWeightViz, alphaM);
		//Ci = vec4(animVizTemp, alphaM);

        Ci.rgb *= twoSided; //
    }

	//Ci.rgb = fog(Ci.rgb);

	/* TEMP DISABLED */
    vec4 skyT = texture(sky, v.uv);
    Ci.rgb = mix(skyT.rgb, Ci.rgb, Ci.a);


	//if (comboU0.z == 1.f)
	//{
		Ci = clamp(Ci, vec4(0.f), vec4(40.f)); //
		//Ci = clamp(Ci, vec4(0.f), vec4(10.f)); //

	//}

	///////////////////////////////
	//DUDV IN SECOND RENDER TARGET
	///////////////////////////////
	dudv = clamp(dudv, .001f, .999f);
	Ci_dudv = vec4(dudv, 0.f, 0.f);
}