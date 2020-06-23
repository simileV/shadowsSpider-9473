#version 450 core

layout(location = 0) out vec4 rttGiz;

uniform vec4 comboU0; //vec4(Csel / Cwire, 1.f)

void main()
{
    rttGiz = comboU0;
}
