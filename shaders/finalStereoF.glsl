#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D stereo0;
layout(bindless_sampler, location = 1) uniform sampler2D stereo1;

out vec3 Ci;

uniform vec4 LDRU;
uniform vec4 comboU0; //vec4(rezGateTgl, dragDrop, debug0, myAbj.dudvTime)
uniform vec4 comboU1; //vec4(farClip, nearClip, myAbj.showHideTaskbar, myAbj.stereoMethod)
uniform vec4 comboU2; //vec4(myAbj.channel, 0.f, 0.f, 0.f)


float blendScreen(float base, float blend)
{
	return 1.f - ((1.f - base) * (1.f - blend));
}

vec3 blendScreen2(vec3 base, vec3 blend)
{
	return vec3(blendScreen(base.r, blend.r), blendScreen(base.g, blend.g), blendScreen(base.b, blend.b));
}

void main()
{
	vec3 myRed, myGreen, myBlue, myCyan;
	vec3 stereoL = texture(stereo0, v.uv).rgb;
	vec3 stereoR = texture(stereo1, v.uv).rgb;

	if (comboU1.w == 0)
	{
		float grayL = dot(stereoL, vec3(.299f, .587f, .114f));
		myRed = vec3(grayL, 0.f, 0.f);

		float grayR = dot(stereoR, vec3(.299f, .587f, .114f));
		myCyan = vec3(0.f, grayR, grayR);
	}
	
	if (comboU1.w == 1)
	{
		float duboisRL = dot(stereoL, vec3(.456f, .5f, .176));
		float duboisRR = dot(stereoR, vec3(-.043f, -.088f, -.002f));
		myRed = vec3(duboisRL + duboisRR, 0.f, 0.f);

		float duboisGL = dot(stereoL, vec3(-.04f, -.038f, -.016f));
		float duboisGR = dot(stereoR, vec3(.378f, .734f, -.018f));
		float duboisBL = dot(stereoL, vec3(-.015f, -.021f, -.005f));
		float duboisBR = dot(stereoR, vec3(-.072f, -.113f, 1.226f));
		myCyan = vec3(0.f, duboisGL + duboisGR, duboisBL + duboisBR);
	}

	Ci = blendScreen2(myRed, myCyan);

	Ci = pow(Ci, vec3(1.f / 2.2f));
}