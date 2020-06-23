#version 450 core

out Vert
{
    vec2 uv, uv2, uv3, uv4, uv5;
} v;

uniform vec2 texelSize;

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

    v.uv = vertices[gl_VertexID].xy * .5f + .5f;

    v.uv2 = v.uv;
    v.uv3 = v.uv + vec2(texelSize.x, 0);
    v.uv4 = v.uv + vec2(texelSize.x, texelSize.y);
    v.uv5 = v.uv + vec2(0, texelSize.y);
}
