#version 450 core

layout(location = 0) out vec4 Ci;

uniform vec4 Cgiz;

void main()
{
    Ci = Cgiz;
}
