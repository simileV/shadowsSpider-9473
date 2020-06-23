#version 450 core

layout(location = 0) in vec3 pE;
layout(location = 1) in vec2 uvE;
layout(location = 2) in vec3 tE;
layout(location = 3) in vec3 nE;
layout(location = 4) in ivec4 boneIdE;
layout(location = 5) in vec4 boneWtE;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];
uniform mat4 MVP;

void main()
{
	mat4 BoneTransform	   = gBones[boneIdE[0]] * boneWtE[0];
		BoneTransform     += gBones[boneIdE[1]] * boneWtE[1];
		BoneTransform     += gBones[boneIdE[2]] * boneWtE[2];
		BoneTransform     += gBones[boneIdE[3]] * boneWtE[3];

    gl_Position = MVP * BoneTransform * vec4(pE, 1.f);
}