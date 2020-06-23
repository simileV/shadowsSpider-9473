#version 450 core

out Vert
{
    vec2 uv;
} v;

uniform mat4 MVP;

void main()
{
    const vec4 vertices[] = vec4[](
		vec4(-1.f, -1.f, 0.f, 1.f),
		vec4( 1.f, -1.f, 0.f, 1.f),
		vec4(-1.f,  1.f, 0.f, 1.f),
		vec4(-1.f,  1.f, 0.f, 1.f),
		vec4( 1.f, -1.f, 0.f, 1.f),
		vec4( 1.f,  1.f, 0.f, 1.f));

    gl_Position = MVP * vertices[gl_VertexID];
    v.uv = vertices[gl_VertexID].xy * .5f + .5f;
}
