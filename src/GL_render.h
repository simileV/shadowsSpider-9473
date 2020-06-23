#ifndef GL_RENDER_H
#define GL_RENDER_H

#include "Core.h"
#include "Paint.h"
#include "CreateN.h"

void renderFrame();
void timeBasedStuff();
void mpfTimerStart();

void setRenderParams_GLApi(string);
void setLightsDirty();
void resize();
void PMupOrtho(shared_ptr<Object> obj);
void VMup(shared_ptr<Object> obj);
void dupeStenFix_check(shared_ptr<Object>);
bool gridMatch(shared_ptr<Object>);
void GBuffer_BOIT();
void postFX();
void overlay2D();

bool searchUp(shared_ptr<Object>);
void searchUpRecursive(shared_ptr<Object>);

void gizShow(string);
void pivTgl();

void clearSel();
void frustumCullCPU(string);	
void bbViz();
void moveByHand_free();
void moveByHand_strafe();

glm::quat RotationBetweenVectors(glm::vec3, glm::vec3);
glm::quat LookAtQuat(glm::vec3, glm::vec3);

int findAnimPosition(float animTime, MultiAttr multi);

#endif