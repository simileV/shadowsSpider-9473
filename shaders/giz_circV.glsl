#version 450 core

layout(location = 0) in vec3 pE;

uniform vec4 circRight;
uniform vec4 comboU0; //vec4(circUpOrFront, fullCirc)

const float PI = 3.14159;
uniform mat4 MVP;

void main()
{
    int seg = 30;
    float mult = (comboU0.w == 1.f) ? 2.f : 1.f;

    float theta = mult * PI * gl_VertexID / seg;

    vec3 rotPt = circRight.xyz * cos(theta);
    rotPt += comboU0.xyz * sin(theta);

    gl_Position = MVP * vec4(rotPt, 1.f);
}
