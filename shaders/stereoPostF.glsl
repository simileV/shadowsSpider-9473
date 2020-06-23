#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D fxaa;
layout(bindless_sampler, location = 1) uniform sampler2D ssr;
layout(bindless_sampler, location = 2) uniform sampler2D def;
layout(bindless_sampler, location = 5) uniform sampler2D normalRuff1_64; 
//layout(bindless_sampler, location = 6) uniform sampler2D gBuf7; //BOIT reveal

//out float Ci;
out vec3 Ci;

uniform vec4 comboU0; //vec4(rezGateTgl, dragDrop, debug0, myAbj.dudvTime)

float CalcLuma(vec3 rgb)
{
    vec3 luma = vec3(.299f, .587f, .114f);
    luma = pow(luma, vec3(1.f / 2.2f)); //linearize

    return dot(rgb, luma);
}

void main() //3D 
{
//    float revealageT = texture(gBuf7, v.uv).x; //
	float ssrInten = texture(normalRuff1_64, v.uv).r;
//	vec3 withColor = texture(fxaa, v.uv).rgb + (revealageT * (ssrInten * texture(ssr, v.uv).rgb));
	vec3 withColor = texture(fxaa, v.uv).rgb + (ssrInten * texture(ssr, v.uv).rgb);


	Ci = withColor;
	//Ci =  texture(fxaa, v.uv).rgb;
	//Ci =  texture(def, v.uv).rgb;
	//Ci =  texture(def, v.uv).a;

	//Ci = CalcLuma(withColor);
	//Ci = pow(Ci, vec3(1.f / 2.2f));
	//Ci = pow(Ci, 1.f / 2.2f);
}