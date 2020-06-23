#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

//layout(bindless_sampler, location = 0) uniform sampler2D stereoTest;
layout(bindless_sampler, location = 0) uniform sampler2D stereo0;
layout(bindless_sampler, location = 1) uniform sampler2D stereo1;
layout(bindless_sampler, location = 2) uniform sampler2D gBuf0;

out vec3 Ci;

uniform vec4 LDRU;
uniform vec4 comboU0; //vec4(rezGateTgl, dragDrop, debug0, myAbj.dudvTime)
uniform vec4 comboU1; //vec4(farClip, nearClip, myAbj.showHideTaskbar, 0.f)

float rezGateAlpha(vec2 uv, vec2 pLD, vec2 pRU, float dragDrop)
{
    if ((uv.x < pLD.x || uv.x > pRU.x || uv.y < pLD.y || uv.y > pRU.y) || (dragDrop == 1.f))
        return .2f;

    else
        return 1.f;

    return 0.f;
}

float blendScreen(float base, float blend)
{
	return 1.f - ((1.f - base) * (1.f - blend));
}

vec3 blendScreen(vec3 base, vec3 blend)
{
	return vec3(blendScreen(base.r, blend.r), blendScreen(base.g, blend.g), blendScreen(base.b, blend.b));
}

void main() //3D 
{
	vec3 myRed = texture(stereo0, v.uv).rgb;
	myRed = vec3(myRed.r);
	myRed = vec3(myRed.r, 0.f, 0.f);

	vec3 myCyan = texture(stereo1, v.uv).rgb;
	myCyan = vec3(myCyan.r);
	myCyan = vec3(0.f, myCyan.g, myCyan.b);
	//myCyan = texture(stereo1, v.uv).rgb;

	//Ci = myRed;
	//Ci = myCyan;
	Ci = myRed + myCyan;
	//Ci = blendScreen(myRed, myCyan);
	//Ci = blendScreen(myCyan, myRed);

	if (comboU1.z == 1)
	{
		if (v.uv.y > .75f)
		{
			Ci = vec3(0.f);
		}
	}

	Ci = vec3(1.f);

	//Ci = vec3(0.f);

 //   if (comboU0.x == 1.f)
	//{
 //       Ci *= rezGateAlpha(v.uv, LDRU.xy, LDRU.zw, comboU0.y);
	//}

	Ci = pow(Ci, vec3(1.f / 2.2f));
}

//void main() //3D 
//{
//	vec3 myRed = texture(stereo0, v.uv).rgb;
//	myRed = vec3(myRed.r);
//	myRed = vec3(myRed.r, 0.f, 0.f);

//	vec3 myCyan = texture(stereo1, v.uv).rgb;
//	myCyan = vec3(myCyan.r);
//	myCyan = vec3(0.f, myCyan.g, myCyan.b);
//	//myCyan = texture(stereo1, v.uv).rgb;

//	//Ci = myRed;
//	//Ci = myCyan;
//	Ci = myRed + myCyan;
//	//Ci = blendScreen(myRed, myCyan);
//	//Ci = blendScreen(myCyan, myRed);


// //   if (comboU0.x == 1.f)
//	//{
// //       Ci *= rezGateAlpha(v.uv, LDRU.xy, LDRU.zw, comboU0.y);
//	//}

//	Ci = pow(Ci, vec3(1.f / 2.2f));
//}