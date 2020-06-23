#ifndef SETUP_OBJ_H
#define SETUP_OBJ_H

#include "Core.h"
#include "StringManip.h"
#include "AI.h"
#include "FBXtoAbj.h"


typedef struct
{
	string type, name;
	glm::vec3 t;
} CamSetup;

typedef struct
{
	string name;
	glm::vec3 r;
} GridSetup;

typedef struct
{
	string type, name;
	glm::vec3 Cgiz, r, t;
} GizSetup;

void camInit();
void gizInit();
void gridInit();
void objInit();

void startupScene(string);
void cubeKeys(shared_ptr<Object>);
void dieChoicesDebug();
int randomBetw(int, int);

shared_ptr<Object> nonFBX_VBOup(string, string, shared_ptr<Object>);
void upGLBuffersNonFBX(shared_ptr<Object>, bool, bool);

void lightArrowAdd(shared_ptr<Object>, float, float, float, string);

#endif