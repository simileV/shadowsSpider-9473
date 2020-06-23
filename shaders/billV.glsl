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
} v;

uniform mat3 NM;
uniform mat4 MVP, MM;
uniform vec4 camRight_WS, camUp_WS;

void main()
{
    const vec4 vertices[] = vec4[](
		vec4(-1.f, -1.f, 0.f, 1.f),
		vec4( 1.f, -1.f, 0.f, 1.f),
		vec4(-1.f,  1.f, 0.f, 1.f),
		vec4(-1.f,  1.f, 0.f, 1.f),
		vec4( 1.f, -1.f, 0.f, 1.f),
		vec4( 1.f,  1.f, 0.f, 1.f));

	v.uv = vertices[gl_VertexID].xy * .5f + .5f;

	vec3 P_WS_d0 = vec3(0.f, -8.f, 0.f);
    //vec3 P_WS_d = vec3(0.f);
	vec3 P_WS_d = vec3(0.f, -8.f, 0.f);

    //vec3 mySize = vec3(5.f);
	//vec3 mySize = vec3(10.f);
	
	///////////////
	/* METHOD 1 */
	//////////////
	//gl_Position = scene.VPM * vertices[gl_VertexID];
	////gl_Position = scene.VPM * vec4(400, 200, 0.f, 1.f);
	//gl_Position /= gl_Position.w;

	/////////////////
	///* METHOD 2 */
	////////////////
	vec3 P_WS_d2 = vec3(0.f, 0.f, 0.f);
	vec3 mySize2 = vec3(5.f, 2.f, 5.f);
	vec3 vertexP_WS2 = P_WS_d2 + (camRight_WS.xyz * vertices[gl_VertexID].x * mySize2.x) + (camUp_WS.xyz * vertices[gl_VertexID].y * mySize2.y);

	gl_Position = scene.VPM * vec4(vertexP_WS2, 1.f); //GL_POSITION
	//gl_Position /= gl_Position.w;

	///////////////
	/* METHOD 3 */
	//////////////
	//vec2 mySize3 = vec2(.5f, .5f);
	//gl_Position = scene.VPM * vec4(P_WS_d, 1.f); //GL_POSITION
	//gl_Position /= gl_Position.w;
	//gl_Position.xy += vertices[gl_VertexID].xy * mySize3;
	
    
}

