#include "pch.h"
#include "AI.h"

AI::AI()
{

	//LoadAssimp("C:/Users/aleks/source/repos/Shadows_Spider/Shadows_Spider/fbx/simpleSkinnedRect.fbx");
}

AI::~AI()
{
}

void AI::LoadAssimp(string filename, string animName)
{
	myAbj.aiNameUnknown.clear();

	aiSceneStored myNewAiScene;
	//myNewAiScene.scene = NULL;

	myNewAiScene.scene = m_Importer.ReadFile(filename, aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights);

	//myNewAiScene.scene = m_Importer.ReadFile(filename, aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights);

	if (myNewAiScene.scene)
	{
		myNewAiScene.globalInvXform = myNewAiScene.scene->mRootNode->mTransformation.Inverse();

		glm::mat4 globalInvXformGLM0 = toGLM(myNewAiScene.scene->mRootNode->mTransformation.Inverse());
		glm::mat4 globalInvXformGLM1 = toGLM4(myNewAiScene.scene->mRootNode->mTransformation.Inverse());

		//cout << "myNewAiScene.globalInvXform GLM0 = " << glm::to_string(globalInvXformGLM0) << endl;
		//cout << "myNewAiScene.globalInvXform GLM1 = " << glm::to_string(globalInvXformGLM1) << endl;

		InitFromScene(myNewAiScene.scene, filename);

		int numBones = 0;

		for (uint i = 0; i < myNewAiScene.scene->mNumMeshes; i++)
			numBones += myNewAiScene.scene->mMeshes[i]->mNumBones;

		bool hasBoneAnimation = (numBones > 0) ? 1 : 0;
		myNewAiScene.animated = hasBoneAnimation;

		myNewAiScene.name = animName;
		myNewAiScene.nameIdx = { animName, myAbj.aiLoadCt };
		myNewAiScene.groupIdx = myAbj.aiLoadCt;

		myAbj.aiAnimScenes.push_back(myNewAiScene);
	}

	else
	{
		printf("Error::ASSIMP::parsing '%s': '%s'\n", filename.c_str(), m_Importer.GetErrorString());
	}
}

void AI::InitFromScene(const aiScene *pScene, string filename)
{
	myAbj.myNewObjNumVerts = 0;
	int numBones = 0;

	for (uint i = 0; i < pScene->mNumMeshes; i++)
	{
		myAbj.myNewObjNumVerts += pScene->mMeshes[i]->mNumVertices;
		numBones += pScene->mMeshes[i]->mNumBones;
	}

	cout << "myAbj.myNewObjNumVerts = " << myAbj.myNewObjNumVerts << endl;
	bool hasBoneAnimation = (numBones > 0) ? 1 : 0;
	cout << "hasBoneAnimation / myMesh->mNumBones = " << (int)hasBoneAnimation << " " << numBones << endl;

	for (unsigned int i = 0; i < pScene->mNumMeshes; i++)
	{
		auto myObj = make_shared<Object>();
		//myObj->rename(pScene->mMeshes[i]->mName.C_Str());
		myObj->rename(pScene->mMeshes[i]->mName.data);
		//myObj->rename("pCube1");
		myObj->type = "OBJ";
		myObj->animAI->val_b = hasBoneAnimation;
		myObj->anim->val_b = hasBoneAnimation;
		//myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//myObj->albedoTile->val_2 = glm::vec2(4.f);

		if (myObj->anim->val_b)
			myObj->linkedGrp = myAbj.aiLoadCt;

		myAbj.aiNameUnknown.push_back(myObj->name->val_s);

		cout << myObj->name->val_s << endl;

		aiMesh *myMesh = pScene->mMeshes[i];

		for (uint j = 0; j < myMesh->mNumVertices; j++)
		{
			myObj->pE.push_back({ myMesh->mVertices[j].x, myMesh->mVertices[j].y, myMesh->mVertices[j].z });
			myObj->nE.push_back({ myMesh->mNormals[j].x, myMesh->mNormals[j].y, myMesh->mNormals[j].z });
			myObj->tE.push_back({ myMesh->mTangents[j].x, myMesh->mTangents[j].y, myMesh->mTangents[j].z });
			myObj->uvE.push_back({ myMesh->mTextureCoords[0][j].x, myMesh->mTextureCoords[0][j].y });
		}

		for (uint j = 0; j < myMesh->mNumFaces; j++)
		{
			aiFace myFace = myMesh->mFaces[j];

			for (uint k = 0; k < myFace.mNumIndices; k++)
				myObj->idxE.push_back(myFace.mIndices[k]);
		}

		if (myObj->anim->val_b)
		{
			myObj->Bones.resize(myAbj.myNewObjNumVerts);
			myObj->boneIdE.resize(myAbj.myNewObjNumVerts);
			myObj->boneWtE.resize(myAbj.myNewObjNumVerts);

			//LOAD BONES
			for (uint j = 0; j < myMesh->mNumBones; j++)
			{
				uint BoneIndex = 0;
				string BoneName = myMesh->mBones[j]->mName.data;

				//cout << "j / BoneName / Bones.size() = " << i << " " << BoneName << " " << myObj->Bones.size() << endl;

				if (myObj->m_BoneMapping.find(BoneName) == myObj->m_BoneMapping.end())
				{
					// Allocate an index for a new bone
					//cout << "new spot for BoneName : " << BoneName << " for obj : " << myObj->name->val_s << endl;

					BoneIndex = myObj->m_NumBones;
					myObj->m_NumBones++;

					//cout << "i / BoneIndex = " << i << " " << BoneIndex << endl;

					BoneInfo bi;
					myObj->m_BoneInfo.push_back(bi);
					//myObj->m_BoneInfo[BoneIndex].BoneOffset = toGLM4(myMesh->mBones[j]->mOffsetMatrix);
					myObj->m_BoneInfo[BoneIndex].BoneOffset = myMesh->mBones[j]->mOffsetMatrix;

					Matrix4f myConvert = myMesh->mBones[j]->mOffsetMatrix;

					myConvert.Print(); //////////
					glm::mat4 myConvertGLM = toGLM(myMesh->mBones[j]->mOffsetMatrix);
					glm::mat4 myConvertGLM4 = toGLM4(myMesh->mBones[j]->mOffsetMatrix);


					cout << "j, offset = " << j << " " << glm::to_string(myConvertGLM) << endl;
					cout << "j, offset4 = " << j << " " << glm::to_string(myConvertGLM4) << endl;

					//if (myObj->name->val_s == "pCube1" && BoneName == "joint2")
					//{
					//	cout << "myConvert for : = " << myObj->name->val_s << " " << BoneName << endl;
					//	cout << fixed << myConvert.m[0][0] << " " << myConvert.m[0][1] << " " << myConvert.m[0][2] << " " << myConvert.m[0][3] << endl;
					//	cout << fixed << myConvert.m[1][0] << " " << myConvert.m[1][1] << " " << myConvert.m[1][2] << " " << myConvert.m[1][3] << endl;
					//	cout << fixed << myConvert.m[2][0] << " " << myConvert.m[2][1] << " " << myConvert.m[2][2] << " " << myConvert.m[2][3] << endl;
					//	cout << fixed << myConvert.m[3][0] << " " << myConvert.m[3][1] << " " << myConvert.m[3][2] << " " << myConvert.m[3][3] << endl;

					//	cout << "~~~~~~~~~" << endl;

					//	cout << myConvertGLM[0][0] << " " << myConvertGLM[1][0] << " " << myConvertGLM[2][0] << " " << myConvertGLM[3][0] << " " << endl;
					//	cout << myConvertGLM[0][1] << " " << myConvertGLM[1][1] << " " << myConvertGLM[2][1] << " " << myConvertGLM[3][1] << " " << endl;
					//	cout << myConvertGLM[0][2] << " " << myConvertGLM[1][2] << " " << myConvertGLM[2][2] << " " << myConvertGLM[3][2] << " " << endl;
					//	cout << myConvertGLM[0][3] << " " << myConvertGLM[1][3] << " " << myConvertGLM[2][3] << " " << myConvertGLM[3][3] << " " << endl;

					//	cout << endl;
					//}

					myObj->m_BoneMapping[BoneName] = BoneIndex;

					//cout << "j / BoneMapping = " << j << " " << myObj->m_BoneMapping[BoneName] << endl;
				}

				else
				{
					cout << "found pre-existing BoneName : " << BoneName << " for obj : " << myObj->name->val_s << endl;
					BoneIndex = myObj->m_BoneMapping[BoneName]; /////////////////////
				}

				//cout << "~~~~~~~~~~~~~~~ j / myMesh->mBones[j]->mNumWeights : " << j << " " << myMesh->mBones[j]->mNumWeights << endl;

				for (uint k = 0; k < myMesh->mBones[j]->mNumWeights; k++)
				{
					uint VertexID = myMesh->mBones[j]->mWeights[k].mVertexId;
					float Weight = myMesh->mBones[j]->mWeights[k].mWeight;
					//cout << "VertexID = " << VertexID << endl;

					//cout << "j / vertexID / weight = " << j << " " << VertexID << " " << Weight << endl;
					//cout << "j / k / vertexID / weight = " << j << " " << k << " " << VertexID << " " << Weight << endl;

					//cout << "Weight = " << Weight << endl;
					myObj->Bones[VertexID].AddBoneData(BoneIndex, Weight, myObj, VertexID);
				}
			}

			//PRECALC BOUNDING BOX AROUND BONES
			for (uint i = 0; i < myMesh->mNumBones; i++)
			{
				bbSkel mybbSkel;

				vector<glm::vec3> bbSkelInfl;

				for (uint j = 0; j < myMesh->mBones[i]->mNumWeights; j++)
				{
					uint VertexID = myMesh->mBones[i]->mWeights[j].mVertexId;
					float Weight = myMesh->mBones[i]->mWeights[j].mWeight;

					if (Weight != 0.f)
					{
						glm::vec3 bbInfl = myObj->pE[VertexID];
						//cout << obj->pE.size() << endl;

						//cout << "bbSkelPossible = " << VertexID << " " << glm::to_string(obj->pE[VertexID]) << endl;
						//cout << "bbSkelPossible = " << VertexID << " " << obj->pE[VertexID] << endl;
						bbSkelInfl.push_back(bbInfl);
					}
				}

				glm::vec3 bbSkelMin, bbSkelMax;
				bbSkelMin = (bbSkelInfl.empty()) ? glm::vec3(0.f) : bbSkelInfl[0];
				bbSkelMax = (bbSkelInfl.empty()) ? glm::vec3(0.f) : bbSkelInfl[0];

				//cout << "bbSkelInfl.size() = " << bbSkelInfl.size() << endl;
				for (auto &j : bbSkelInfl)
				{
					bbSkelMin = glm::min(j, bbSkelMin);
					bbSkelMax = glm::max(j, bbSkelMax);
				}

				glm::vec3 bbSize = bbSkelMax - bbSkelMin;
				glm::vec3 bbCenter = .5f * (bbSkelMin + bbSkelMax);
				glm::mat4 obbMVP = glm::translate(glm::mat4(), bbCenter) * glm::scale(glm::mat4(), bbSize);

				//cout << "mybbSkel.name = " << mybbSkel.name << endl;
				mybbSkel.name = myMesh->mBones[i]->mName.data;

				string gBonesName;
				gBonesName.append("gBones[");
				gBonesName.append(to_string(i));
				gBonesName.append("]");

				mybbSkel.name = gBonesName;
				//cout << "mybbSkel.name = " << mybbSkel.name << endl;

				string BoneName(myMesh->mBones[i]->mName.data);
				mybbSkel.nameBone = BoneName;
				mybbSkel.nameMesh = myMesh->mName.data;
				//cout << "mybbSkel.nameMesh = " << mybbSkel.nameMesh << endl;

				mybbSkel.min = bbSkelMin;
				mybbSkel.max = bbSkelMax;
				mybbSkel.obbMVP = obbMVP;
				mybbSkel.linkedGrp = myObj->linkedGrp;

				myObj->bbSkelAll.push_back(mybbSkel);
			}

			//CALC AABB  
			//if only 1 obj...(in obj)

			glm::vec3 aabbMin = (myObj->bbSkelAll.empty()) ? glm::vec3(0.f) : myObj->bbSkelAll[0].min;
			glm::vec3 aabbMax = (myObj->bbSkelAll.empty()) ? glm::vec3(0.f) : myObj->bbSkelAll[0].max;

			for (auto &i : myObj->bbSkelAll)
			{
				aabbMin = glm::min(i.min, aabbMin);
				aabbMax = glm::max(i.max, aabbMax);
			}

			glm::vec3 aabbSize = aabbMax - aabbMin;
			glm::vec3 aabbCenter = .5f * (aabbMin + aabbMax);
			myObj->aabbMVP = glm::translate(glm::mat4(), aabbCenter) * glm::scale(glm::mat4(), aabbSize);
		}

		upGLBuffers(myObj);
	}
}

void AI::upGLBuffers(shared_ptr<Object> myObj)
{
	GLuint VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX;

	glCreateBuffers(1, &VBO_P);
	glNamedBufferData(VBO_P, myObj->pE.size() * sizeof(glm::vec3), &myObj->pE[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &VBO_UV);
	glNamedBufferData(VBO_UV, myObj->uvE.size() * sizeof(glm::vec2), &myObj->uvE[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &VBO_T);
	glNamedBufferData(VBO_T, myObj->tE.size() * sizeof(glm::vec3), &myObj->tE[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &VBO_N);
	glNamedBufferData(VBO_N, myObj->nE.size() * sizeof(glm::vec3), &myObj->nE[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &VBO_IDX);
	glNamedBufferData(VBO_IDX, myObj->idxE.size() * sizeof(GLuint), &myObj->idxE[0], GL_STATIC_DRAW);

	if (myObj->anim->val_b)
	{
		GLuint VBO_BONEID, VBO_BONEWT;

		glCreateBuffers(1, &VBO_BONEID);
		glNamedBufferData(VBO_BONEID, myObj->boneIdE.size() * sizeof(glm::ivec4), &myObj->boneIdE[0], GL_STATIC_DRAW);

		glCreateBuffers(1, &VBO_BONEWT);
		glNamedBufferData(VBO_BONEWT, myObj->boneWtE.size() * sizeof(glm::vec4), &myObj->boneWtE[0], GL_STATIC_DRAW);

		//for (int i = 0; i < myObj->boneIdE.size(); i++)
		//{
		//	cout << glm::to_string(myObj->boneIdE[i]) << " " << i << endl;
		//}

		//for (int i = 0; i < myObj->boneWtE.size(); i++)
		//{
		//	cout << glm::to_string(myObj->boneWtE[i]) << " " << i << endl;
		//}

		myAbj.GLDataSh.push_back({ myObj, VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX, VBO_BONEID, VBO_BONEWT });
	}

	else
		myAbj.GLDataSh.push_back({ myObj, VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX, 0, 0 });

	myObj->BBup();

	myAbj.allObj.push_back(myObj);
}

glm::mat4 AI::toGLM(aiMatrix4x4 myAiMatrix)
{
	float bbb[16] =
	{
		(float)myAiMatrix[0][0], (float)myAiMatrix[0][1], (float)myAiMatrix[0][2], (float)myAiMatrix[0][3],
		(float)myAiMatrix[1][0], (float)myAiMatrix[1][1], (float)myAiMatrix[1][2], (float)myAiMatrix[1][3],
		(float)myAiMatrix[2][0], (float)myAiMatrix[2][1], (float)myAiMatrix[2][2], (float)myAiMatrix[2][3],
		(float)myAiMatrix[3][0], (float)myAiMatrix[3][1], (float)myAiMatrix[3][2], (float)myAiMatrix[3][3],

	};

	return glm::make_mat4(bbb);
}

glm::mat4 AI::toGLM4(aiMatrix4x4 myAiMatrix)
{
	float bbb[16] =
	{
		(float)myAiMatrix.a1, (float)myAiMatrix.b1, (float)myAiMatrix.c1, (float)myAiMatrix.d1,
		(float)myAiMatrix.a2, (float)myAiMatrix.b2, (float)myAiMatrix.c2, (float)myAiMatrix.d2,
		(float)myAiMatrix.a3, (float)myAiMatrix.b3, (float)myAiMatrix.c3, (float)myAiMatrix.d3,
		(float)myAiMatrix.a4, (float)myAiMatrix.b4, (float)myAiMatrix.c4, (float)myAiMatrix.d4,

		//myAiMatrix.a1, myAiMatrix.b1, myAiMatrix.c1, myAiMatrix.d1,
		//myAiMatrix.a2, myAiMatrix.b2, myAiMatrix.c2, myAiMatrix.d2,
		//myAiMatrix.a3, myAiMatrix.b3, myAiMatrix.c3, myAiMatrix.d3,
		//myAiMatrix.a4, myAiMatrix.b4, myAiMatrix.c4, myAiMatrix.d4,

	};

	//float bbb[16] =
	//{
	//	(float)myAiMatrix.a1, (float)myAiMatrix.a2, (float)myAiMatrix.a3, (float)myAiMatrix.a4,
	//	(float)myAiMatrix.b1, (float)myAiMatrix.b2, (float)myAiMatrix.b3, (float)myAiMatrix.b4,
	//	(float)myAiMatrix.c1, (float)myAiMatrix.c2, (float)myAiMatrix.c3, (float)myAiMatrix.c4,
	//	(float)myAiMatrix.d1, (float)myAiMatrix.d2, (float)myAiMatrix.d3, (float)myAiMatrix.d4,

	//};

	return glm::make_mat4(bbb);
}

void AI::switchAnim(string objName, string animName)
{
	for (auto &i : myAbj.allObj)
	{
		if (i->name->val_s == objName)
		{
			//for (auto &j : myAbj.aiAnimScenes)
			//{
			//	if (j.nameIdx.name == animName)
			//	{
			//		i->prevSceneNI.name = i->curSceneNI.name;
			//		i->prevSceneNI.idx = i->curSceneNI.idx;

			//		i->curSceneNI.name = j.nameIdx.name;
			//		i->curSceneNI.idx = j.nameIdx.idx;
			//	}
			//}
		}
	}
}

