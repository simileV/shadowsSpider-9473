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
} v;

layout(bindless_sampler, location = 0) uniform sampler2D ruff;

layout(location = 0) out vec4 normalRuff0;
layout(location = 1) out vec4 normalRuff1;

uniform mat4 MM;
uniform vec4 metallicRuffTile;
uniform vec4 comboU0; //vec4(ssrInten->val_f, 0.f, 0.f, 0.f)

void main()
{
    float ruffT = texture(ruff, metallicRuffTile.ba * v.uv).r;

    ///////////
    normalRuff0 = vec4(v.N_VS, ruffT);
	normalRuff1 = vec4(comboU0.x, 0.f, 0.f, 0.f);
}