/*
reference:
    http://www.gamedev.net/page/resources/_/technical/graphics-programming-and-theory/a-simple-and-practical-approach-to-ssao-r2753
    http://anki3d.org/screen-space-ambient-occlusion/
    https://mynameismjp.wordpress.com/2009/03/10/reconstructing-position-from-depth/
    http://www.learnopengl.com/#!Advanced-Lighting/SSAO
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

layout(bindless_sampler, location = 0) uniform usampler2D gBuf_5; //N_VS_ssao
layout(binding = 1) uniform sampler2D gBuf_DS;
layout(bindless_sampler, location = 2) uniform sampler2D noise;

layout(location = 0) out float Ci;

uniform vec4 comboU0; //vec4(ssaoBias, ssaoInten, ssaoRad)

vec3 reconstructP(vec2 UV)
{
    vec4 vProjectedPos = vec4(1.f);
    vProjectedPos.rg = UV * 2.f - 1.f;
    vProjectedPos.b = texture(gBuf_DS, UV).r * 2.f - 1.f;
    vec4 vPositionVS = scene.PMinv * vProjectedPos;

    return vPositionVS.rgb / vPositionVS.a;
}

const vec3 kernel64[64] = vec3[](
    vec3(0.049771, -0.044709, 0.049963),
    vec3(0.014575, 0.016531, 0.002239),
    vec3(-0.040648, -0.019375, 0.031934),
    vec3(0.013778, -0.091582, 0.040924),
    vec3(0.055989, 0.059792, 0.057659),
    vec3(0.092266, 0.044279, 0.015451),
    vec3(-0.002039, -0.054402, 0.066735),
    vec3(-0.000331, -0.000187, 0.000369),
    vec3(0.050045, -0.046650, 0.025385),
    vec3(0.038128, 0.031402, 0.032868),
    vec3(-0.031883, 0.020459, 0.022515),
    vec3(0.055702, -0.036974, 0.054492),
    vec3(0.057372, -0.022540, 0.075542),
    vec3(-0.016090, -0.003768, 0.055473),
    vec3(-0.025033, -0.024829, 0.024951),
    vec3(-0.033688, 0.021391, 0.025402),
    vec3(-0.017530, 0.014386, 0.005348),
    vec3(0.073359, 0.112052, 0.011015),
    vec3(-0.044056, -0.090284, 0.083683),
    vec3(-0.083277, -0.001683, 0.084987),
    vec3(-0.010406, -0.032867, 0.019273),
    vec3(0.003211, -0.004882, 0.004164),
    vec3(-0.007383, -0.065835, 0.067398),
    vec3(0.094141, -0.007998, 0.143350),
    vec3(0.076833, 0.126968, 0.106999),
    vec3(0.000393, 0.000450, 0.000302),
    vec3(-0.104793, 0.065445, 0.101737),
    vec3(-0.004452, -0.119638, 0.161901),
    vec3(-0.074553, 0.034449, 0.224138),
    vec3(-0.002758, 0.003078, 0.002923),
    vec3(-0.108512, 0.142337, 0.166435),
    vec3(0.046882, 0.103636, 0.059576),
    vec3(0.134569, -0.022512, 0.130514),
    vec3(-0.164490, -0.155644, 0.124540),
    vec3(-0.187666, -0.208834, 0.057770),
    vec3(-0.043722, 0.086925, 0.074797),
    vec3(-0.002564, -0.002001, 0.004070),
    vec3(-0.096696, -0.182259, 0.299487),
    vec3(-0.225767, 0.316061, 0.089156),
    vec3(-0.027505, 0.287187, 0.317177),
    vec3(0.207216, -0.270839, 0.110132),
    vec3(0.054902, 0.104345, 0.323106),
    vec3(-0.130860, 0.119294, 0.280219),
    vec3(0.154035, -0.065371, 0.229842),
    vec3(0.052938, -0.227866, 0.148478),
    vec3(-0.187305, -0.040225, 0.015926),
    vec3(0.141843, 0.047163, 0.134847),
    vec3(-0.044268, 0.055616, 0.055859),
    vec3(-0.023583, -0.080970, 0.219130),
    vec3(-0.142147, 0.198069, 0.005194),
    vec3(0.158646, 0.230457, 0.043715),
    vec3(0.030040, 0.381832, 0.163825),
    vec3(0.083006, -0.309661, 0.067413),
    vec3(0.226953, -0.235350, 0.193673),
    vec3(0.381287, 0.332041, 0.529492),
    vec3(-0.556272, 0.294715, 0.301101),
    vec3(0.424490, 0.005647, 0.117578),
    vec3(0.366500, 0.003588, 0.085702),
    vec3(0.329018, 0.030898, 0.178504),
    vec3(-0.082938, 0.512848, 0.056555),
    vec3(0.867363, -0.002734, 0.100138),
    vec3(0.455745, -0.772006, 0.003841),
    vec3(0.417291, -0.154846, 0.462514),
    vec3(-0.442722, -0.679282, 0.186503)
);

void main()
{
    vec3 P_VS = reconstructP(v.uv);

    uvec4 data5 = texelFetch(gBuf_5, ivec2(gl_FragCoord.xy), 0);
    vec3 N_VS = vec3(unpackHalf2x16(data5.y), unpackHalf2x16(data5.z).x);

    vec2 screenSize = textureSize(gBuf_5, 0);
    vec3 randomVec = normalize(texture(noise, v.uv * screenSize / 4).rgb * 2.f - 1.f);

    // Create TBN change-of-basis matrix: from tangent-space to view-space
//    vec3 tangent = normalize(randomVec - N_VS * dot(randomVec, N_VS));
    vec3 tangent = randomVec - N_VS * dot(randomVec, N_VS);
    vec3 bitangent = cross(N_VS, tangent);
    mat3 TBN = mat3(tangent, bitangent, N_VS);

    float ao = 0.f;

    for (int i = 0; i < 64; ++i)
    {
        vec3 sampleP = TBN * kernel64[i]; // From tangent to view-space
        sampleP = sampleP * comboU0.z + P_VS;

        // project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = scene.PM * vec4(sampleP, 1.f); // from view to clip-space
        offset.xy /= offset.w; // perspective divide
        offset.xy = offset.xy * .5f + .5f; // transform to range 0.f - 1.f

        float sampleDepth = reconstructP(offset.xy).z;
        float rangeCheck = smoothstep(0.f, 1.f, comboU0.z / abs(P_VS.z - sampleDepth));

        ao += (sampleDepth - comboU0.x >= sampleP.z ? 1.f : 0.f) * rangeCheck * comboU0.y;
    }

    Ci = 1.f - (ao / 64.f);
}
