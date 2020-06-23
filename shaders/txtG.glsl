/*
reference:
    http://github.prideout.net/strings-inside-vertex-buffers/
*/

#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in Vert
{
    int vCharacter, vPosition;
} v[];

uniform vec4 comboU0; //vec4(txtCellSize, txtCellOffset)
uniform vec4 comboU1; //vec4(txtSize, txtOrigin)

out Geo
{
    vec2 uv;
} g;

void main()
{
    // Determine the final quad's position and size:
    float x = comboU1.z + float(v[0].vPosition) * comboU1.x * 2;
    float y = comboU1.w;
    vec4 P = vec4(x, y, 0, 1);
    vec4 U = vec4(1, 0, 0, 0) * comboU1.x;
    vec4 V = vec4(0, 1, 0, 0) * comboU1.y;

    // Determine the texture coordinates:
    int letter = v[0].vCharacter;
    letter = clamp(letter - 32, 0, 96);
    int row = letter / 16 + 1;
    int col = letter % 16;
    float S0 = comboU0.z + comboU0.x * col;
    float T0 = comboU0.w + 1 - comboU0.y * row;
    float S1 = S0 + comboU0.x - comboU0.z;
    float T1 = T0 + comboU0.y;

    // Output the quad's vertices:
    g.uv = vec2(S0, 1 - T1); gl_Position = P - U - V; EmitVertex();
    g.uv = vec2(S1, 1 - T1); gl_Position = P + U - V; EmitVertex();
    g.uv = vec2(S0, 1 - T0); gl_Position = P - U + V; EmitVertex();
    g.uv = vec2(S1, 1 - T0); gl_Position = P + U + V; EmitVertex();

    EndPrimitive();
}
