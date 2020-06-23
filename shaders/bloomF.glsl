/*
reference:
    http://forum.unity3d.com/threads/se-natural-bloom-dirty-lens.243430/
*/

#version 450 core
#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D bloom_gauss0;
layout(bindless_sampler, location = 1) uniform sampler2D bloom_gauss1;
layout(bindless_sampler, location = 2) uniform sampler2D bloom_gauss2;
layout(bindless_sampler, location = 3) uniform sampler2D bloom_gauss3;
layout(bindless_sampler, location = 4) uniform sampler2D bloom_gauss4;
layout(bindless_sampler, location = 5) uniform sampler2D bloom_gauss5;
layout(bindless_sampler, location = 6) uniform sampler2D def;
layout(bindless_sampler, location = 7) uniform sampler2D lens;

layout(location = 0) out vec4 Ci;

uniform vec4 comboU0; //vec4(bloomInten, bloomLensInten, debug0, 0.f)

vec3 b0 = texture(bloom_gauss0, v.uv).rgb;
vec3 b1 = texture(bloom_gauss1, v.uv).rgb;
vec3 b2 = texture(bloom_gauss2, v.uv).rgb;
vec3 b3 = texture(bloom_gauss3, v.uv).rgb;
vec3 b4 = texture(bloom_gauss4, v.uv).rgb;
vec3 b5 = texture(bloom_gauss5, v.uv).rgb;
vec4 defT = texture(def, v.uv);
vec4 lensT = texture(lens, v.uv);

void main()
{
    Ci = defT;

    vec3 bloom = (b0*.5f + b1*.6f + b2*.6f + b3*.45f + b4*.35f + b5*.23f) / 2.2f;
    vec3 lensBloom = (b0 + b1*.8f + b2*.6f + b3*.45f + b4*.35f + b5*.23f) / 3.2f;


    Ci.rgb = mix(Ci.rgb, bloom, comboU0.x);

    Ci.r = mix(Ci.r, lensBloom.r, lensT.r * comboU0.y);
    Ci.g = mix(Ci.g, lensBloom.g, lensT.g * comboU0.y);
    Ci.b = mix(Ci.b, lensBloom.b, lensT.b * comboU0.y);

	//if (comboU0.z == 1.f)
		//Ci = defT;

}
