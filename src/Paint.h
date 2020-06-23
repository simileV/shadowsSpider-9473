#ifndef PAINT_H
#define PAINT_H

#include "Core.h"
#include "Setup_texShaders.h"
#include "GL_render.h"

///////////////
// PAINT - try again with reset fbo 2/1 to fbo 1/0
//////////////
void paintSomething0();
void paintSomething1(string);

void brushOutlineUp();
void clearCursor(bool);
void clearCanvas();
TexMap getCurrPaintLayer();
void bakeSomething();
vector<glm::vec2> bresenham(glm::ivec2, glm::ivec2, int);

#endif