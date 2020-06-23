/*
reference:
https://www.gamedev.net/forums/topic/653502-useful-things-you-might-want-to-know-about-fbxsdk/
*/


#ifndef FBXTOABJ_H
#define FBXTOABJ_H

#include "Core.h"
#include "Object.h"
#include "StringManip.h"

class FBXtoAbj
{
public:
	FBXtoAbj::FBXtoAbj();
	~FBXtoAbj();

	glm::vec3 toGLM(FbxDouble3);
	glm::vec4 toGLM(FbxVector4);
	glm::mat4 toGLM(FbxMatrix);
	

	void WriteMatrix(ostream &, FbxMatrix &);

	void ProcessGeometry(FbxNode *);
	void ProcessControlPoints(FbxNode *);
	void ProcessSkeletonHierarchy(FbxNode *);
	void ProcessSkeletonHierarchyRecursively(FbxNode *, int, int);
	void ProcessJointsAndAnimations(FbxNode *);
	void ProcessMesh(FbxNode *);

	void ReadTangentNormalUV(FbxMesh *, int, int, int, int, string, glm::vec3 &, glm::vec2 &);
	int FindVertex(PNTIWVertex &, vector<PNTIWVertex> &);
	FbxAMatrix GetGeometryTransformation(FbxNode *);
	uint FindJointIndexUsingName(string &);

	bool WriteAbjXML(const char *);
	void WriteMeshToStream(ostream &);
	void WriteAnimationToStream(ostream &);

	bool readAbjStaticXML(const char *, shared_ptr<Object>);
	bool readAbjAnimXML(const char *, shared_ptr<Object>);

	vector<Triangle> mTriangles;
	vector<PNTIWVertex> mVertices;
	vector<CtrlPoint *> mControlPoints;
	vector<Joint> mJoints;
	vector<FbxNode *> allJointsOnFBX;

	bool mHasAnimation;
	uint mTriangleCount;
	string mAnimationName;
	FbxLongLong mAnimationLength;



protected:
	//

private:
	FbxManager *mFBXManager;
	FbxScene *mScene;
	FbxImporter *mImporter;
};

#ifndef XMLCheckElement
#define XMLCheckElement(a, b) if (a == nullptr) { cout << "could not find " << b << endl; return 0; }
#endif

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { cout << "XML Error: " << a_eResult << endl; return 0; }
#endif

#endif