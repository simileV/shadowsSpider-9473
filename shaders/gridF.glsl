#version 450 core

layout(location = 0) out vec4 rttC;

uniform vec4 Cgrid;

void main()
{
    rttC = Cgrid;
}
