#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D prevStereo;

out vec3 Ci;

uniform vec4 comboU0; //vec4(rezGateTgl, dragDrop, debug0, myAbj.dudvTime)

void main() //3D 
{
	Ci = texture(prevStereo, v.uv).rgb;
	//Ci = vec3(0.f, 1.f, 0.f);
	//Ci = pow(Ci, vec3(1.f / 2.2f));
}