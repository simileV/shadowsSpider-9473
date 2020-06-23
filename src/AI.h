#ifndef AI_H
#define AI_H

#include "Core.h"
#include "Setup_obj.h"
#include "Object.h"


class AI
{
public:

	AI::AI();
	~AI();

	//ASSIMP
	const aiScene* m_pScene;
	Assimp::Importer m_Importer;
	//aiMatrix4x4 m_GlobalInverseTransform;
	glm::mat4 m_GlobalInverseTransform;

	glm::mat4 toGLM(aiMatrix4x4);
	glm::mat4 toGLM4(aiMatrix4x4);

	void LoadAssimp(string, string);
	void InitFromScene(const aiScene *, string);
	void upGLBuffers(shared_ptr<Object> myObj);
	void switchAnim(string, string);

protected:
	//

private:
	//
};

#endif