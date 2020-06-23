#version 450 core

layout(location = 0) out vec4 rttGiz;

uniform vec4 CstencilHi;

void main()
{
    rttGiz = CstencilHi;
}
