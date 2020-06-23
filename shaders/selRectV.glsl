#version 450 core

uniform vec4 LDRU;

void main()
{
     const vec4 vertices[] = vec4[](
             vec4(LDRU.xy, 0.f, 1.f),
             vec4(LDRU.z, LDRU.y, 0.f, 1.f),
             vec4(LDRU.x, LDRU.w, 0.f, 1.f),
             vec4(LDRU.zw, 0.f, 1.f));

    gl_Position = vertices[gl_VertexID];
}
