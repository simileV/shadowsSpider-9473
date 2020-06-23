#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D cursorReg1k;

layout(location = 0) out vec4 Ci;

uniform vec4 Cgiz;

void main()
{
    //Ci = Cgiz;
	Ci = vec4(1.f, 0.f, 0.f, 1.f);

	Ci = texture(cursorReg1k, v.uv);
}
