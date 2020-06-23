/*
reference:
    http://github.prideout.net/strings-inside-vertex-buffers/
*/

#version 450 core

layout(location = 0) in int Character;

out Vert
{
    int vCharacter, vPosition;
} v;

void main()
{
    v.vCharacter = Character;
    v.vPosition = gl_VertexID;

    gl_Position = vec4(0.f, 0.f, 0.f, 1.f);
}

