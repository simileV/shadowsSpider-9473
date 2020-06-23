#version 450 core

in Vert
{
    vec2 uv;
} v;

layout(location = 0) out vec4 Ci;

void main()
{
	Ci = vec4(0.f, 0.f, 1.f, 1.f);
}

