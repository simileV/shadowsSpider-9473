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
    vec3 N_VS;
    vec4 bakeCoord;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D paintStroke;
layout(bindless_sampler, location = 1) uniform sampler2D layerOld;
layout(location = 0) out vec4 Ci;

void main()
{
    vec3 V_VS = normalize(scene.VM * vec4(10.f, 10.f, 10.f, 0.f)).xyz;
    vec4 paintStrokeT = textureProj(paintStroke, v.bakeCoord);
    vec4 layerOldT = texture(layerOld, v.uv);

    if (v.bakeCoord.q > 0.f) // prevents reverse projection
    {
        Ci = mix(layerOldT, paintStrokeT, paintStrokeT.a);

//        if (dot(v.N_VS, V_VS) > 0.f) //NdotV prevents backfacing proj
//        {
//            Ci = mix(layerOldT, paintStrokeT, paintStrokeT.a);
//        }
    }

    else //set original tex w/o stroke projection
    {
        Ci = layerOldT;
    }

    Ci.a = 1.f;
}
