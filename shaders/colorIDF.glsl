#version 450 core

layout(location = 0) out vec4 rttC;

uniform vec4 comboU0; //vec4(Crand, 1.f) (COLORPICK)

void main()
{
    rttC = comboU0;
}
