#ifndef GIZMO_H
#define GIZMO_H

#include "Core.h"
#include "Object.h"
#include "GL_render.h"

class Gizmo
{
public:
	Gizmo();
	~Gizmo();

	string hover();
	void transform();

	glm::vec3 rayCast(glm::vec2);
	glm::vec3 rayInter(glm::vec3, bool, string);
	bool rotatePlane(glm::vec3, glm::vec3);
	glm::vec3 dotInterAx(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

	void resetSetCol(string); //ep


protected:
};


#endif