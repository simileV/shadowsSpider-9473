#ifndef INPUT_H
#define INPUT_H

#include "Core.h"
#include "Window.h"
#include "Paint.h"
#include "AI.h"
#include "Gizmo.h"
#include "FileSystem.h"


void keyCallback(GLFWwindow *, int, int, int, int);
void cursorPosCallback(GLFWwindow *, double, double);
void mouseButtonCallback(GLFWwindow *, int, int, int);
void scrollCallback(GLFWwindow *, double, double);

bool checkForHits();
void matchFoundRaycast(shared_ptr<Object>);


#endif