#ifndef CREATEN_H
#define CREATEN_H

#include "Core.h"
#include "Setup_texShaders.h"

bool fboPrep();
AbjNode gBufN_create();
AbjNode normalRuffN_create();
AbjNode defN_create();
AbjNode depthRevN_create(int, int);
AbjNode bgN_create(int, int);
AbjNode tonemapN_create();
AbjNode singleN_create(string, GLenum, int, int);
AbjNode dualN_create(string, GLenum, int, int);
void bloomBufferCreate();

void resizeTexClearMem();

#endif