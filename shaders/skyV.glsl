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
    vec3 uv;
} v;

uniform mat4 PMinv_cube, VM;

void main()
{
    const vec4 vertices[] = vec4[](
		vec4(-1.f, -1.f, 0.f, 1.f),
		vec4( 1.f, -1.f, 0.f, 1.f),
		vec4(-1.f,  1.f, 0.f, 1.f),
		vec4(-1.f,  1.f, 0.f, 1.f),
		vec4( 1.f, -1.f, 0.f, 1.f),
		vec4( 1.f,  1.f, 0.f, 1.f));

    gl_Position = vertices[gl_VertexID];

    vec3 unproject = (PMinv_cube * vertices[gl_VertexID]).xyz;
    v.uv = transpose(mat3(scene.VM)) * unproject;
}
