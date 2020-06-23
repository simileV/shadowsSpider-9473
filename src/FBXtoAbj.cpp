#include "pch.h"
/*
reference:
https://www.gamedev.net/forums/topic/653502-useful-things-you-might-want-to-know-about-fbxsdk/
*/

#include "FBXtoAbj.h"

FBXtoAbj::FBXtoAbj()
{
	mFBXManager = FbxManager::Create();
	FbxIOSettings *fbxIOSettings = FbxIOSettings::Create(mFBXManager, IOSROOT);
	mFBXManager->SetIOSettings(fbxIOSettings);
	mScene = FbxScene::Create(mFBXManager, IOSROOT);
	mImporter = FbxImporter::Create(mFBXManager, "FBXtoABJ_scene");
	FbxArray<FbxPose*> pPoseArray;
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames24);

	//LoadAssimp("C:/Users/aleks/source/repos/Shadows_Spider/Shadows_Spider/fbx/simpleSkinnedRect.fbx");
}

FBXtoAbj::~FBXtoAbj()
{
	mScene->Destroy();
	mImporter->Destroy();
	mFBXManager->Destroy();
}


bool FBXtoAbj::WriteAbjXML(const char *filename)
{

	mImporter->Initialize(filename, -1, mFBXManager->GetIOSettings());
	mImporter->Import(mScene);

	FbxAxisSystem SceneAxisSystem = mScene->GetGlobalSettings().GetAxisSystem();
	FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
	if (SceneAxisSystem != OurAxisSystem)
	{
		cout << "~~~~~~~~~~~~ converting scene" << endl;
		OurAxisSystem.ConvertScene(mScene);
	}

	OurAxisSystem.ConvertScene(mScene);


	FbxSystemUnit SceneSystemUnit = mScene->GetGlobalSettings().GetSystemUnit();
	if (SceneSystemUnit.GetScaleFactor() != 1.f) FbxSystemUnit::cm.ConvertScene(mScene);

	ProcessSkeletonHierarchy(mScene->GetRootNode());
	mHasAnimation = (mJoints.empty()) ? 0 : 1;
	ProcessGeometry(mScene->GetRootNode()); //OBJECT created and initialized here
	
	string inputFilePathNoSuffix = RemoveSuffix(GetFileName(string(filename)));
	string outputMeshName = "fbx/" + inputFilePathNoSuffix + ".abjmesh";
	ofstream meshOutput(outputMeshName);
	WriteMeshToStream(meshOutput);

	if (mHasAnimation)
	{
		string outputAnimName = "fbx/" + inputFilePathNoSuffix + ".abjanim";
		ofstream animOutput(outputAnimName);
		WriteAnimationToStream(animOutput);
	}

	mControlPoints.clear(); mVertices.clear(); mTriangles.clear();

	return 1;
}

glm::vec3 FBXtoAbj::toGLM(FbxDouble3 inDouble3)
{
	glm::vec3 myVec3;
	myVec3.x = (float)inDouble3[0];
	myVec3.y = (float)inDouble3[1];
	myVec3.z = (float)inDouble3[2];

	return myVec3;
}

glm::vec4 FBXtoAbj::toGLM(FbxVector4 inVec4)
{
	glm::vec4 myVec4;

	myVec4[0] = (float)inVec4[0];
	myVec4[1] = (float)inVec4[1];
	myVec4[2] = (float)inVec4[2];
	myVec4[3] = (float)inVec4[3];

	return myVec4;
}

glm::mat4 FBXtoAbj::toGLM(FbxMatrix myFbxMatrix)
{
	float bbb[16] =
	{
		(float)myFbxMatrix[0][0], (float)myFbxMatrix[0][1], (float)myFbxMatrix[0][2], (float)myFbxMatrix[0][3],
		(float)myFbxMatrix[1][0], (float)myFbxMatrix[1][1], (float)myFbxMatrix[1][2], (float)myFbxMatrix[1][3],
		(float)myFbxMatrix[2][0], (float)myFbxMatrix[2][1], (float)myFbxMatrix[2][2], (float)myFbxMatrix[2][3],
		(float)myFbxMatrix[3][0], (float)myFbxMatrix[3][1], (float)myFbxMatrix[3][2], (float)myFbxMatrix[3][3],

	};
	
	return glm::make_mat4(bbb);
}

void FBXtoAbj::WriteMatrix(ostream &inStream, FbxMatrix &inMatrix)
{
	inStream << "<mat>"
		<< static_cast<float>(inMatrix.Get(0, 0)) << "," << static_cast<float>(inMatrix.Get(0, 1)) << "," << static_cast<float>(inMatrix.Get(0, 2)) << "," << static_cast<float>(inMatrix.Get(0, 3)) << ","

		<< static_cast<float>(inMatrix.Get(1, 0)) << "," << static_cast<float>(inMatrix.Get(1, 1)) << "," << static_cast<float>(inMatrix.Get(1, 2)) << "," << static_cast<float>(inMatrix.Get(1, 3)) << ","

		<< static_cast<float>(inMatrix.Get(2, 0)) << "," << static_cast<float>(inMatrix.Get(2, 1)) << "," << static_cast<float>(inMatrix.Get(2, 2)) << "," << static_cast<float>(inMatrix.Get(2, 3)) << ","

		<< static_cast<float>(inMatrix.Get(3, 0)) << "," << static_cast<float>(inMatrix.Get(3, 1)) << "," << static_cast<float>(inMatrix.Get(3, 2)) << "," << static_cast<float>(inMatrix.Get(3, 3)) << "</mat>\n";
}

void FBXtoAbj::ProcessSkeletonHierarchy(FbxNode *inRootNode)
{
	//cout << "inRootNode->GetChildCount() = " << inRootNode->GetChildCount() << endl;

	for (int i = 0; i < inRootNode->GetChildCount(); ++i)
	{
		FbxNode *currNode = inRootNode->GetChild(i);
		ProcessSkeletonHierarchyRecursively(currNode, 0, -1);
	}
}

void FBXtoAbj::ProcessSkeletonHierarchyRecursively(FbxNode *inNode, int myIndex, int inParentIndex)
{
	if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		//cout << "inParentIndex = " << inParentIndex << endl;

		Joint currJoint;
		currJoint.mParentIndex = inParentIndex;
		currJoint.mName = inNode->GetName();
		//currJoint.mNode = inNode;
		cout << inParentIndex << " currJoint.mName = " << currJoint.mName << " " << currJoint.mParentIndex << endl;
		mJoints.push_back(currJoint);

		allJointsOnFBX.push_back(inNode);
	}

	for (int i = 0; i < inNode->GetChildCount(); ++i)
		ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), int(mJoints.size()), myIndex);
}

void FBXtoAbj::ProcessGeometry(FbxNode *inNode)
{
	FbxNodeAttribute *lNodeAttribute = inNode->GetNodeAttribute();

	if (lNodeAttribute && lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		ProcessControlPoints(inNode);

		if (mHasAnimation)
			ProcessJointsAndAnimations(inNode);

		ProcessMesh(inNode);
	}

	//cout << "inNode->GetChildCount() = " << inNode->GetChildCount() << endl;

	for (int i = 0; i < inNode->GetChildCount(); ++i)
	{
		ProcessGeometry(inNode->GetChild(i));
	}
}

void FBXtoAbj::ProcessControlPoints(FbxNode *inNode)
{
	FbxMesh *currMesh = inNode->GetMesh();
	uint ctrlPointCount = currMesh->GetControlPointsCount();

	for (uint i = 0; i < ctrlPointCount; ++i)
	{
		CtrlPoint *currCtrlPoint = new CtrlPoint();
		glm::vec3 currP;

		for (uint j = 0; j < 3; ++j)
			currP[j] = static_cast<float>(currMesh->GetControlPointAt(i).mData[j]);

		currCtrlPoint->mPosition = currP;
		mControlPoints.push_back(currCtrlPoint);
	}
}

void FBXtoAbj::ProcessJointsAndAnimations(FbxNode *inNode)
{
	FbxMesh *currMesh = inNode->GetMesh();

	uint numDeformers = currMesh->GetDeformerCount();
	for (uint i = 0; i < numDeformers; ++i)
	{
		FbxSkin *currSkin = reinterpret_cast<FbxSkin *>(currMesh->GetDeformer(i, FbxDeformer::eSkin));

		if (!currSkin)
			continue;

		uint numClusters = currSkin->GetClusterCount();

		for (uint j = 0; j < numClusters; ++j)
		{
			FbxCluster *currCluster = currSkin->GetCluster(j);
			string currJointName = currCluster->GetLink()->GetName();
			uint currJointIndex = FindJointIndexUsingName(currJointName);

			FbxAMatrix transformMatrix, transformLinkMatrix;
			FbxAMatrix geometryTransform = GetGeometryTransformation(inNode);
			//geometryTransform.SetIdentity();

			currCluster->GetTransformMatrix(transformMatrix); //the xform of the mesh at binding time
			currCluster->GetTransformLinkMatrix(transformLinkMatrix); // the xform of the cluster(jnt) at binding time from joint space to world space
			//mJoints[currJointIndex].mGlobalBindpose = transformLinkMatrix * transformMatrix * geometryTransform;
			//mJoints[currJointIndex].mGlobalBindposeInverse = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;

			mJoints[currJointIndex].mGlobalBindpose = transformLinkMatrix;
			mJoints[currJointIndex].mGlobalBindposeInverse = transformLinkMatrix.Inverse();

			//FbxAMatrix offsetM = inNode->World
			//mJoints[currJointIndex].mNode = currCluster->GetLink();

			//associate each joint with the ctrl pts it affects
			uint numIndices = currCluster->GetControlPointIndicesCount();

			for (uint k = 0; k < numIndices; ++k)
			{
				BlendingIndexWeightPair currBlendingIndexWeightPair;
				currBlendingIndexWeightPair.mBlendingIndex = currJointIndex;
				currBlendingIndexWeightPair.mBlendingWeight = currCluster->GetControlPointWeights()[k];

				//cout << "i / j / k = " << i << " " << j << " " << k << endl;
				mControlPoints[currCluster->GetControlPointIndices()[k]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
			}

			/* get animation info (for 1 "take") */
			//for (uint i = 0; i < mJoints.size(); ++i)
			{
				FbxTime::SetGlobalTimeMode(FbxTime::eFrames24);
				FbxAnimStack *currAnimStack = mScene->GetSrcObject<FbxAnimStack>(0);
				mScene->SetCurrentAnimationStack(currAnimStack);
				FbxString Name = currAnimStack->GetNameOnly();
				FbxString TakeName = currAnimStack->GetName();
				FbxTakeInfo* TakeInfo = mScene->GetTakeInfo(TakeName);
				FbxTimeSpan LocalTimeSpan = TakeInfo->mLocalTimeSpan;
				FbxTime Start = LocalTimeSpan.GetStart();
				FbxTime Stop = LocalTimeSpan.GetStop();
				FbxTime Duration = LocalTimeSpan.GetDuration();

				FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
				FbxLongLong FrameCount = Duration.GetFrameCount(TimeMode);
				double FrameRate = FbxTime::GetFrameRate(TimeMode);

				for (FbxLongLong f = Start.GetFrameCount(TimeMode); f <= Stop.GetFrameCount(TimeMode); ++f)
				{
					FbxTime Time;
					Time.SetFrame(f, TimeMode);

					//bool useDirk = 0;
					bool useDirk = 1;

					if (useDirk)
					{
						for (FbxNode *Node : allJointsOnFBX)
						{
							if (Node->GetName() == mJoints[currJointIndex].mName)
							{
								FbxAMatrix LocalTransform = Node->EvaluateGlobalTransform(Time);
								//FbxAMatrix LocalTransform = Node->EvaluateLocalTransform(Time);

								//is there a parent bone? If so, need to apply that parents global inverse transform to this node's transform

								if (FbxNode *Parent = Node->GetParent())
								{
									FbxNodeAttribute *ParentAttribute = Parent->GetNodeAttribute();

									if (ParentAttribute && ParentAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
									{
										FbxAMatrix GlobalParentTransform = Parent->EvaluateGlobalTransform(Time);
										//FbxAMatrix GlobalParentTransform = Parent->EvaluateLocalTransform(Time);
										LocalTransform = GlobalParentTransform.Inverse() * LocalTransform;
									}
								}

								mJoints[currJointIndex].keyframes.push_back(LocalTransform);
								FbxVector4 Translation(LocalTransform.GetT());
								cout << fixed << mJoints[currJointIndex].mName << " : translation : " << f << " " << Translation[0] << " " << Translation[1] << " " << Translation[2] << endl;
							}
						}
					}

					else
					{
						//FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(Time) * geometryTransform;
						//FbxAMatrix LocalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(Time);

						FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(Time) * geometryTransform;
						FbxAMatrix LocalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(Time);

						mJoints[currJointIndex].keyframes.push_back(LocalTransform);
					}

				}
			}



		}
	}

	//add dummy joints if there isnt already 4 (the max) influencers
	BlendingIndexWeightPair currBlendingIndexWeightPair;
	currBlendingIndexWeightPair.mBlendingIndex = 0;
	currBlendingIndexWeightPair.mBlendingWeight = 0;

	for (uint i = 0; i < mControlPoints.size(); ++i)
	{
		for (uint j = uint(mControlPoints[i]->mBlendingInfo.size()); j <= 4; ++j)
		{
			mControlPoints[i]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
			cout << "i / j add extra joint = " << i << " " << j << endl;
		}
	}
}

//void FBXtoAbj::ProcessJointsAndAnimations(FbxNode *inNode)
//{
//	FbxMesh *currMesh = inNode->GetMesh();
//
//	uint numDeformers = currMesh->GetDeformerCount();
//	for (uint i = 0; i < numDeformers; ++i)
//	{
//		FbxSkin *currSkin = reinterpret_cast<FbxSkin *>(currMesh->GetDeformer(i, FbxDeformer::eSkin));
//
//		if (!currSkin)
//			continue;
//
//		uint numClusters = currSkin->GetClusterCount();
//
//		for (uint j = 0; j < numClusters; ++j)
//		{
//			FbxCluster *currCluster = currSkin->GetCluster(j);
//			string currJointName = currCluster->GetLink()->GetName();
//			uint currJointIndex = FindJointIndexUsingName(currJointName);
//
//			FbxAMatrix transformMatrix, transformLinkMatrix;
//			FbxAMatrix geometryTransform = GetGeometryTransformation(inNode);
//			//geometryTransform.SetIdentity();
//
//			currCluster->GetTransformMatrix(transformMatrix); //the xform of the mesh at binding time
//			currCluster->GetTransformLinkMatrix(transformLinkMatrix); // the xform of the cluster(jnt) at binding time from joint space to world space
//			//mJoints[currJointIndex].mGlobalBindpose = transformLinkMatrix * transformMatrix * geometryTransform;
//			//mJoints[currJointIndex].mGlobalBindposeInverse = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;
//
//			mJoints[currJointIndex].mGlobalBindpose = transformLinkMatrix;
//			mJoints[currJointIndex].mGlobalBindposeInverse = transformLinkMatrix.Inverse();
//
//			//FbxAMatrix offsetM = inNode->World
//			//mJoints[currJointIndex].mNode = currCluster->GetLink();
//
//			//associate each joint with the ctrl pts it affects
//			uint numIndices = currCluster->GetControlPointIndicesCount();
//
//			for (uint k = 0; k < numIndices; ++k)
//			{
//				BlendingIndexWeightPair currBlendingIndexWeightPair;
//				currBlendingIndexWeightPair.mBlendingIndex = currJointIndex;
//				currBlendingIndexWeightPair.mBlendingWeight = currCluster->GetControlPointWeights()[k];
//
//				mControlPoints[currCluster->GetControlPointIndices()[k]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
//			}
//
//			/* get animation info (for 1 "take") */
//			//for (uint i = 0; i < mJoints.size(); ++i)
//			{
//				FbxTime::SetGlobalTimeMode(FbxTime::eFrames24);
//				FbxAnimStack *currAnimStack = mScene->GetSrcObject<FbxAnimStack>(0);
//				mScene->SetCurrentAnimationStack(currAnimStack);
//				FbxString Name = currAnimStack->GetNameOnly();
//				FbxString TakeName = currAnimStack->GetName();
//				FbxTakeInfo* TakeInfo = mScene->GetTakeInfo(TakeName);
//				FbxTimeSpan LocalTimeSpan = TakeInfo->mLocalTimeSpan;
//				FbxTime Start = LocalTimeSpan.GetStart();
//				FbxTime Stop = LocalTimeSpan.GetStop();
//				FbxTime Duration = LocalTimeSpan.GetDuration();
//
//				FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
//				FbxLongLong FrameCount = Duration.GetFrameCount(TimeMode);
//				double FrameRate = FbxTime::GetFrameRate(TimeMode);
//
//				for (FbxLongLong f = Start.GetFrameCount(TimeMode); f <= Stop.GetFrameCount(TimeMode); ++f)
//				{
//					FbxTime Time;
//					Time.SetFrame(f, TimeMode);
//
//					//bool useDirk = 0;
//					bool useDirk = 1;
//
//
//					if (useDirk)
//					{
//						for (FbxNode *Node : allJointsOnFBX)
//						{
//							if (Node->GetName() == mJoints[currJointIndex].mName)
//							{
//								FbxAMatrix LocalTransform = Node->EvaluateGlobalTransform(Time);
//								//FbxAMatrix LocalTransform = Node->EvaluateLocalTransform(Time);
//
//								//is there a parent bone? If so, need to apply that parents global inverse transform to this node's transform
//
//								if (FbxNode *Parent = Node->GetParent())
//								{
//									FbxNodeAttribute *ParentAttribute = Parent->GetNodeAttribute();
//
//									if (ParentAttribute && ParentAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
//									{
//										FbxAMatrix GlobalParentTransform = Parent->EvaluateGlobalTransform(Time);
//										//FbxAMatrix GlobalParentTransform = Parent->EvaluateLocalTransform(Time);
//										LocalTransform = GlobalParentTransform.Inverse() * LocalTransform;
//									}
//								}
//
//								mJoints[currJointIndex].keyframes.push_back(LocalTransform);
//							}
//						}
//					}
//
//					else
//					{
//						FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(Time) * geometryTransform;
//						FbxAMatrix LocalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(Time);
//
//						mJoints[currJointIndex].keyframes.push_back(LocalTransform);
//					}
//
//				}
//			}
//
//
//
//		}
//	}
//
//	//add dummy joints if there isnt already 4 (the max) influencers
//	BlendingIndexWeightPair currBlendingIndexWeightPair;
//	currBlendingIndexWeightPair.mBlendingIndex = 0;
//	currBlendingIndexWeightPair.mBlendingWeight = 0;
//
//	for (uint i = 0; i < mControlPoints.size(); ++i)
//	{
//		for (uint j = uint(mControlPoints[i]->mBlendingInfo.size()); j <= 4; ++j)
//		{
//			mControlPoints[i]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
//			cout << "i / j add extra joint = " << i << " " << j << endl;
//		}
//	}
//}


uint FBXtoAbj::FindJointIndexUsingName(string &inJointName)
{
	for (uint i = 0; i < mJoints.size(); ++i)
	{
		if (mJoints[i].mName == inJointName)
			return i;
	}

	throw exception("Skeleton information in FBX file is corrupted");
}

FbxAMatrix FBXtoAbj::GetGeometryTransformation(FbxNode *inNode)
{
	FbxVector4 lT = inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 lR = inNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 lS = inNode->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(lT, lR, lS);
}

void FBXtoAbj::ProcessMesh(FbxNode *inNode)
{
	FbxMesh *currMesh = inNode->GetMesh();

	mTriangleCount = currMesh->GetPolygonCount();
	mTriangles.reserve(mTriangleCount);
	int vertexCounter = 0;

	for (uint i = 0; i < mTriangleCount; ++i)
	{
		glm::vec3 normal[3], tangent[3], blank3;
		glm::vec2 UV[3][2], blank2; //multiple UV tiles

		Triangle currTriangle;
		mTriangles.push_back(currTriangle);

		for (uint j = 0; j < 3; ++j)
		{
			int ctrlPointIndex = currMesh->GetPolygonVertex(i, j);

			ReadTangentNormalUV(currMesh, ctrlPointIndex, vertexCounter, 0, 0, "tan", tangent[j], blank2);
			ReadTangentNormalUV(currMesh, ctrlPointIndex, vertexCounter, 0, 0, "norm", normal[j], blank2);

			for (int k = 0; k < 1; ++k) //only have diffuse texture / 1 UV
			{
				ReadTangentNormalUV(currMesh, ctrlPointIndex, vertexCounter, currMesh->GetTextureUVIndex(i, j), k, "UV", blank3, UV[j][k]);
			}

			CtrlPoint *currCtrlPoint = mControlPoints[ctrlPointIndex];

			PNTIWVertex temp;
			temp.mPosition = currCtrlPoint->mPosition;
			temp.mUV = UV[j][0];
			temp.mTangent = tangent[j];
			temp.mNormal = normal[j];

			for (uint k = 0; k < currCtrlPoint->mBlendingInfo.size(); ++k)
			{
				VertexBlendingInfo currBlendingInfo;
				currBlendingInfo.mBlendingWeight = currCtrlPoint->mBlendingInfo[k].mBlendingWeight;
				currBlendingInfo.mBlendingIndex = currCtrlPoint->mBlendingInfo[k].mBlendingIndex;
				temp.mVertexBlendingInfos.push_back(currBlendingInfo);
			} 

			temp.SortBlendingInfoByWeight(); ///////////

			mVertices.push_back(temp);
			mTriangles.back().mIndices.push_back(vertexCounter);
			++vertexCounter;
		}
	}

	for (auto itr = mControlPoints.begin(); itr != mControlPoints.end(); ++itr)
		delete *itr;

	mControlPoints.clear();

	///////////////////////
	/* create IDX buffer */
	///////////////////////
	cout << "start idx buffer create" << endl;

	vector<PNTIWVertex> uniqueVertices;
	cout << "myAbj.mTriangles.size() = " << mTriangles.size() << endl;
	cout << "mVertices.size() = " << mVertices.size() << endl;
	for (uint i = 0; i < mTriangles.size(); ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			//if current vert has not been added to uniqueVertices, add it
			if (FindVertex(mVertices[i * 3 + j], uniqueVertices) == -1)
				uniqueVertices.push_back(mVertices[i * 3 + j]);
		}
	}

	for (uint i = 0; i < mTriangles.size(); ++i) //update the IDX buffer
	{
		for (uint j = 0; j < 3; ++j)
			mTriangles[i].mIndices[j] = FindVertex(mVertices[i * 3 + j], uniqueVertices);
	}

	mVertices.clear();
	mVertices = uniqueVertices;
	uniqueVertices.clear();

	cout << "mVertices.size() = " << mVertices.size() << endl;

	sort(mTriangles.begin(), mTriangles.end());

	cout << "end idx buffer create" << endl;
}

int FBXtoAbj::FindVertex(PNTIWVertex &inTargetVertex, vector<PNTIWVertex> &uniqueVertices)
{
	for (uint i = 0; i < uniqueVertices.size(); ++i)
	{
		if (inTargetVertex == uniqueVertices[i])
			return i;
	}

	return -1;
}

void FBXtoAbj::ReadTangentNormalUV(FbxMesh *inMesh, int inCtrlPointIndex, int inVertexCounter, int inTextureUVIndex, int inUVLayer, string type, glm::vec3 &out, glm::vec2 &out2)
{
	FbxGeometryElementTangent *vertexTangent = inMesh->GetElementTangent(0);
	FbxGeometryElementNormal *vertexNormal = inMesh->GetElementNormal(0);
	FbxGeometryElementUV *vertexUV = inMesh->GetElementUV(inUVLayer);

	if (type == "tan")
	{
		if (vertexTangent->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			if (vertexTangent->GetReferenceMode() == FbxGeometryElement::eDirect)
			{
				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[i]);
			}

			else if (vertexTangent->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				int index = vertexTangent->GetIndexArray().GetAt(inCtrlPointIndex);

				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[i]);
			}
		}

		else if (vertexTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			if (vertexTangent->GetReferenceMode() == FbxGeometryElement::eDirect)
			{
				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[i]);
			}

			else if (vertexTangent->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				int index = vertexTangent->GetIndexArray().GetAt(inVertexCounter);

				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[i]);
			}
		}
	}

	else if (type == "norm")
	{
		if (vertexNormal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			if (vertexNormal->GetReferenceMode() == FbxGeometryElement::eDirect)
			{
				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[i]);
			}

			else if (vertexNormal->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				int index = vertexNormal->GetIndexArray().GetAt(inCtrlPointIndex);

				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[i]);
			}
		}

		else if (vertexNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			if (vertexNormal->GetReferenceMode() == FbxGeometryElement::eDirect)
			{
				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[i]);
			}

			else if (vertexNormal->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				int index = vertexNormal->GetIndexArray().GetAt(inVertexCounter);

				for (uint i = 0; i < 3; ++i)
					out[i] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[i]);
			}
		}
	}

	else if (type == "UV")
	{
		if (vertexUV->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			if (vertexUV->GetReferenceMode() == FbxGeometryElement::eDirect)
			{
				for (uint i = 0; i < 2; ++i)
					out2[i] = static_cast<float>(vertexUV->GetDirectArray().GetAt(inCtrlPointIndex).mData[i]);
			}

			else if (vertexUV->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				int index = vertexUV->GetIndexArray().GetAt(inCtrlPointIndex);

				for (uint i = 0; i < 2; ++i)
					out2[i] = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[i]);
			}
		}

		else if (vertexUV->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			if (vertexUV->GetReferenceMode() == FbxGeometryElement::eDirect || vertexUV->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				for (uint i = 0; i < 2; ++i)
					out2[i] = static_cast<float>(vertexUV->GetDirectArray().GetAt(inTextureUVIndex).mData[i]);
			}
		}
	}
}

void FBXtoAbj::WriteMeshToStream(ostream& inStream)
{
	inStream << fixed << setprecision(3);

	inStream << "<?xml version='1.0' encoding='UTF-8' ?>" << endl;
	inStream << "<abjmesh>" << endl;

	if (mHasAnimation)
	{
		inStream << "\t<!-- position, normal, skinning weights, skinning indices, texture -->" << endl;
		inStream << "\t<format>pnst</format>" << endl;
	}

	else
		inStream << "\t<format>pnt</format>" << endl;

	inStream << "\t<triangles count='" << mTriangleCount << "'>" << endl;
	for (uint i = 0; i < mTriangleCount; ++i)
	{
		inStream << "\t\t<idx>" << mTriangles[i].mIndices[0] << "," << mTriangles[i].mIndices[1] << "," << mTriangles[i].mIndices[2] << "</idx>" << endl;
	}
	inStream << "\t</triangles>" << endl;

	inStream << "\t<vertices count='" << mVertices.size() << "'>" << endl;
	for (uint i = 0; i < mVertices.size(); ++i)
	{
		//inStream << "\t\t<vtx>" << endl;
		inStream << "\t\t<vtx count='" << i << "'>" << endl;


		inStream << "\t\t\t<pos>" << mVertices[i].mPosition.x << "," << mVertices[i].mPosition.y << "," << mVertices[i].mPosition.z << "</pos>" << endl;

		inStream << "\t\t\t<uv>" << mVertices[i].mUV.x << "," << mVertices[i].mUV.y << "</uv>" << endl;

		inStream << "\t\t\t<tan>" << mVertices[i].mTangent.x << "," << mVertices[i].mTangent.y << "," << mVertices[i].mTangent.z << "</tan>" << endl;

		inStream << "\t\t\t<norm>" << mVertices[i].mNormal.x << "," << mVertices[i].mNormal.y << "," << mVertices[i].mNormal.z << "</norm>" << endl;

		if (mHasAnimation)
		{
			///* normalize weights to 1 */
			//float sumWeights = 0.f;

			//for (int z = 0; z < 4; ++z)
			//{
			//	sumWeights += (float)mVertices[i].mVertexBlendingInfos[z].mBlendingWeight;
			//}

			//sumWeights = glm::min(sumWeights, 1.f);

			//float normalizedWts[4];

			//for (int z = 0; z < 4; ++z)
			//{
			//	normalizedWts[z] = glm::min((float)mVertices[i].mVertexBlendingInfos[z].mBlendingWeight / sumWeights, 1.f);
			//	//normalizedWts[z] = (float)mVertices[i].mVertexBlendingInfos[z].mBlendingWeight / sumWeights;
			//}

			//inStream << "\t\t\t<sw>"
			//	<< static_cast<float>(normalizedWts[0]) << ","
			//	<< static_cast<float>(normalizedWts[1]) << ","
			//	<< static_cast<float>(normalizedWts[2]) << ","
			//	<< static_cast<float>(normalizedWts[3]) << "</sw>" << endl;

			inStream << "\t\t\t<sw>"
				<< static_cast<float>(mVertices[i].mVertexBlendingInfos[0].mBlendingWeight) << ","
				<< static_cast<float>(mVertices[i].mVertexBlendingInfos[1].mBlendingWeight) << ","
				<< static_cast<float>(mVertices[i].mVertexBlendingInfos[2].mBlendingWeight) << ","
				<< static_cast<float>(mVertices[i].mVertexBlendingInfos[3].mBlendingWeight) << "</sw>" << endl;

			inStream << "\t\t\t<si>"
				<< mVertices[i].mVertexBlendingInfos[0].mBlendingIndex
				<< "," << mVertices[i].mVertexBlendingInfos[1].mBlendingIndex
				<< "," << mVertices[i].mVertexBlendingInfos[2].mBlendingIndex
				<< "," << mVertices[i].mVertexBlendingInfos[3].mBlendingIndex << "</si>" << endl;
		}

		inStream << "\t\t</vtx>" << endl;
	}

	inStream << "\t</vertices>" << endl;
	inStream << "</abjmesh>" << endl;
}

bool FBXtoAbj::readAbjStaticXML(const char *filename, shared_ptr<Object> myObj)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError eResult = doc.LoadFile(filename); XMLCheckResult(eResult);
	tinyxml2::XMLElement *abjmesh = doc.FirstChildElement("abjmesh"); XMLCheckElement(abjmesh, "abjmesh");
	tinyxml2::XMLElement *format = abjmesh->FirstChildElement("format"); XMLCheckElement(format, "format");
	tinyxml2::XMLElement *triangles = abjmesh->FirstChildElement("triangles"); XMLCheckElement(triangles, "triangles");
	tinyxml2::XMLElement *vertices = abjmesh->FirstChildElement("vertices"); XMLCheckElement(vertices, "vertices");

	tinyxml2::XMLElement *idx = triangles->FirstChildElement("idx"); XMLCheckElement(idx, "idx");
	tinyxml2::XMLElement *vtx = vertices->FirstChildElement("vtx"); XMLCheckElement(vtx, "vtx");
	tinyxml2::XMLElement *pos, *uv, *tan, *norm, *boneWt, *boneId;

	const char *objFormat = format->GetText();
	//cout << "objFormat = " << objFormat << endl;

	/*GET ATTRIBUTE DATA FOR NUM TRIANGLES / VERTS */
	int outTriCt, outVertCt;
	triangles->QueryIntAttribute("count", &outTriCt);
	vertices->QueryIntAttribute("count", &outVertCt);

	for (int i = 0; i < outTriCt; ++i) //separate by comma and convert to 3 ints to push back into idx buffer
	{
		vector<string> triIndices = stringSplit(idx->GetText(), ",");

		for (auto &j : triIndices)
		{
			int toInt = atoi(j.c_str());
			//cout << toInt << endl;
			myObj->idxE.push_back(toInt);
		}

		idx = idx->NextSiblingElement("idx");
	}

	//cout << "outVertCt = " << outVertCt << endl;

	string animFile = RemoveSuffix(string(filename));
	animFile.append(".abjanim");

	if (FILE *file = fopen(animFile.c_str(), "r")) {
		fclose(file);
		myObj->anim->val_b = 1;
	}

	//cout << "myObj->anim->val_b = " << myObj->anim->val_b << endl;

	/* push back pos, uv, tan, norm, boneWt, boneId */
	for (int i = 0; i < outVertCt; ++i) //separate by comma and convert to floats
	{
		pos = vtx->FirstChildElement("pos"); XMLCheckElement(pos, "pos");
		uv = vtx->FirstChildElement("uv"); XMLCheckElement(uv, "uv");
		tan = vtx->FirstChildElement("tan"); XMLCheckElement(tan, "tan");
		norm = vtx->FirstChildElement("norm"); XMLCheckElement(norm, "norm");

		if (myObj->anim->val_b)
		{
			boneId = vtx->FirstChildElement("si"); XMLCheckElement(boneId, "si");
			boneWt = vtx->FirstChildElement("sw"); XMLCheckElement(boneWt, "sw");
		}

		glm::vec3 posT, tanT, normT;
		glm::vec2 uvT;
		glm::ivec4 boneIdT;
		glm::vec4 boneWtT;

		vector<string> vtxPos = stringSplit(pos->GetText(), ",");
		vector<string> vtxUV = stringSplit(uv->GetText(), ",");
		vector<string> vtxTan = stringSplit(tan->GetText(), ",");
		vector<string> vtxNorm = stringSplit(norm->GetText(), ",");

		if (myObj->anim->val_b)
		{
			vector<string> vtxBoneId = stringSplit(boneId->GetText(), ",");
			vector<string> vtxBoneWt = stringSplit(boneWt->GetText(), ",");

			for (int j = 0; j < 4; ++j)
			{
				boneIdT[j] = stoi(vtxBoneId[j]);
				boneWtT[j] = stof(vtxBoneWt[j]);
			}
		}

		for (int j = 0; j < 3; ++j)
		{
			posT[j] = stof(vtxPos[j]);
			tanT[j] = stof(vtxTan[j]);
			normT[j] = stof(vtxNorm[j]);
		}

		for (int j = 0; j < 2; ++j)
			uvT[j] = stof(vtxUV[j]);

		myObj->pE.push_back(posT);
		myObj->uvE.push_back(uvT);
		myObj->tE.push_back(tanT);
		myObj->nE.push_back(normT);

		if (myObj->anim->val_b)
		{
			myObj->boneIdE.push_back(boneIdT);
			myObj->boneWtE.push_back(boneWtT);
		}

		vtx = vtx->NextSiblingElement("vtx");
	}

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

	if (myObj->anim->val_b || myObj->debugSkelGen->val_b)
		readAbjAnimXML(filename, myObj);

	myObj->BBup();

	myAbj.allObj.push_back(myObj);

	return 1;
}

void FBXtoAbj::WriteAnimationToStream(ostream& inStream)
{
	inStream << fixed << setprecision(3);

	inStream << "<?xml version='1.0' encoding='UTF-8' ?>" << endl;
	inStream << "<abjanim>" << endl;
	inStream << "\t<skeleton count='" << mJoints.size() << "'>" << endl;
 
	for (uint i = 0; i < mJoints.size(); ++i)
	{
		string usableParentName = (i == 0) ? "ROOT" : mJoints[mJoints[i].mParentIndex].mName;

		inStream << "\t\t<joint name='" << mJoints[i].mName << "' parent='" << usableParentName << "'>\n";

		/* DECOMPOSE MATRIX INTO T / RQ */
		{
			//FbxMatrix out = (myAbj.skeletalViz) ? mJoints[i].mGlobalBindpose : mJoints[i].mGlobalBindposeInverse;
			//FbxMatrix out = mJoints[i].mGlobalBindpose; //
			FbxMatrix out = mJoints[i].mGlobalBindposeInverse; //

			inStream << "\t\t\t";
			WriteMatrix(inStream, out);

			//glm::mat4 globalBindposeM = toGLM(out);
			//cout << mJoints[i].mName << " " << glm::to_string(globalBindposeM) << endl << endl;

			FbxVector4 decompT, decompShear, decompScale;
			FbxQuaternion decompR;
			double decompSign;

			out.GetElements(decompT, decompR, decompShear, decompScale, decompSign);

			inStream << "\t\t\t";
			inStream << "<decompT>" << static_cast<float>(decompT.mData[0]) << "," << static_cast<float>(decompT.mData[1]) << "," << static_cast<float>(decompT.mData[2]) << "</decompT>\n";

			inStream << "\t\t\t";
			inStream << "<decompR>" << static_cast<float>(decompR.mData[0]) << "," << static_cast<float>(decompR.mData[1]) << "," << static_cast<float>(decompR.mData[2]) << "," << static_cast<float>(decompR.mData[3]) << "</decompR>\n";
		}

		inStream << "\t\t</joint>\n";
	}

	inStream << "\t</skeleton>\n";

	inStream << "\t<animations count='" << 1 << "'>" << endl;

	FbxAnimStack *currAnimStack = mScene->GetSrcObject<FbxAnimStack>(0);
	FbxString animStackName = currAnimStack->GetName();
	mAnimationName = animStackName.Buffer();

	FbxTakeInfo *takeInfo = mScene->GetTakeInfo(animStackName);
	FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
	FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
	mAnimationLength = end.GetFrameCount(FbxTime::GetGlobalTimeMode()) - start.GetFrameCount(FbxTime::GetGlobalTimeMode()) + 1;

	inStream << "\t\t<animation name='" << mAnimationName << "' length='" << mAnimationLength << "' numJoints='" << mJoints.size() << "'>\n";

	for (uint i = 0; i < mJoints.size(); ++i)
	{
		string usableParentName = (i == 0) ? "ROOT" : mJoints[mJoints[i].mParentIndex].mName;

		//inStream << "\t\t\t<track id='" << i << "' name='" << mJoints[i].mName << "'>\n";
		inStream << "\t\t\t<track id='" << i << "' name='" << mJoints[i].mName << "' parent='" << usableParentName << "'>\n";

		FbxTime::SetGlobalTimeMode(FbxTime::eFrames24);
		FbxAnimStack *currAnimStack = mScene->GetSrcObject<FbxAnimStack>(0);
		mScene->SetCurrentAnimationStack(currAnimStack);
		FbxString Name = currAnimStack->GetNameOnly();
		FbxString TakeName = currAnimStack->GetName();
		FbxTakeInfo* TakeInfo = mScene->GetTakeInfo(TakeName);
		FbxTimeSpan LocalTimeSpan = TakeInfo->mLocalTimeSpan;
		FbxTime Start = LocalTimeSpan.GetStart();
		FbxTime Stop = LocalTimeSpan.GetStop();
		FbxTime Duration = LocalTimeSpan.GetDuration();

		FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
		FbxLongLong FrameCount = Duration.GetFrameCount(TimeMode);
		double FrameRate = FbxTime::GetFrameRate(TimeMode);

		for (FbxLongLong f = Start.GetFrameCount(TimeMode); f <= Stop.GetFrameCount(TimeMode); ++f)
		{
			FbxTime Time;
			Time.SetFrame(f, TimeMode);

			for (FbxNode *Node : allJointsOnFBX)
			{
				if (Node->GetName() == mJoints[i].mName)
				{
					inStream << "\t\t\t\t <frame num='" << f << "'>\n";

						//cout << "f = " << f << endl;
						FbxAMatrix out = mJoints[i].keyframes[f - 1]; //

						FbxVector4 Translation(out.GetT());
						inStream << "\t\t\t\t\t";
						inStream << "<decompT>" << static_cast<float>(Translation.mData[0]) << "," << static_cast<float>(Translation.mData[1]) << "," << static_cast<float>(Translation.mData[2]) << "</decompT>\n";

						FbxQuaternion Rotation(out.GetQ());
						inStream << "\t\t\t\t\t";
						inStream << "<decompR>" << static_cast<float>(Rotation.mData[0]) << "," << static_cast<float>(Rotation.mData[1]) << "," << static_cast<float>(Rotation.mData[2]) << "," << static_cast<float>(Rotation.mData[3]) << "</decompR>\n";

					inStream << "\t\t\t\t </frame>\n";
				}
			}
		}

		inStream << "\t\t\t </track>\n";
	}

	inStream << "\t\t</animation>\n";
	inStream << "\t</animations>\n";
	inStream << "</abjanim>\n";
}

bool FBXtoAbj::readAbjAnimXML(const char *filename, shared_ptr<Object> myObj)
{
	string animFile = RemoveSuffix(string(filename));
	animFile.append(".abjanim");

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError eResult = doc.LoadFile(animFile.c_str()); XMLCheckResult(eResult);
	tinyxml2::XMLElement *abjanim = doc.FirstChildElement("abjanim"); XMLCheckElement(abjanim, "abjanim");
	tinyxml2::XMLElement *skeleton = abjanim->FirstChildElement("skeleton"); XMLCheckElement(skeleton, "skeleton");
	tinyxml2::XMLElement *joint = skeleton->FirstChildElement("joint"); XMLCheckElement(joint, "joint");
	tinyxml2::XMLElement *animations = abjanim->FirstChildElement("animations"); XMLCheckElement(animations, "animations");
	tinyxml2::XMLElement *animation = animations->FirstChildElement("animation"); XMLCheckElement(animation, "animation");
	tinyxml2::XMLElement *track = animation->FirstChildElement("track"); XMLCheckElement(track, "track");
	tinyxml2::XMLElement *frame = track->FirstChildElement("frame"); XMLCheckElement(frame, "frame");

	int skeletonCt, animCt;
	skeleton->QueryIntAttribute("count", &skeletonCt);
	animations->QueryIntAttribute("count", &animCt);

	myObj->myBindSkeleton.skeletonCt = skeletonCt;

	cout << "numBones = " << skeletonCt << endl;

	/* BINDPOSE */
	auto mySkellyObj = make_shared<Object>();

	for (int i = 0; i < skeletonCt; ++i)
	{
		const char *jointName;
		jointName = joint->Attribute("name");

		const char *parentName;
		parentName = joint->Attribute("parent");

		tinyxml2::XMLElement *mat = joint->FirstChildElement("mat"); XMLCheckElement(mat, "mat");
		tinyxml2::XMLElement *decompT = joint->FirstChildElement("decompT"); XMLCheckElement(decompT, "decompT");
		tinyxml2::XMLElement *decompR = joint->FirstChildElement("decompR"); XMLCheckElement(decompR, "decompR");

		ABindpose myBindpose;
		myBindpose.name = jointName;
		myBindpose.parent = parentName;

		vector<string> mat_split = stringSplit(mat->GetText(), ",");
		vector<string> decompT_split = stringSplit(decompT->GetText(), ",");
		vector<string> decompR_split = stringSplit(decompR->GetText(), ",");

		myBindpose.decompT = glm::vec3(stof(decompT_split[0]), stof(decompT_split[1]), stof(decompT_split[2]));

		myBindpose.decompR = glm::quat(stof(decompR_split[3]), stof(decompR_split[0]), stof(decompR_split[1]), stof(decompR_split[2]));

		float bbb[16] =
		{
			stof(mat_split[0]), stof(mat_split[1]), stof(mat_split[2]), stof(mat_split[3]),
			stof(mat_split[4]), stof(mat_split[5]), stof(mat_split[6]), stof(mat_split[7]),
			stof(mat_split[8]), stof(mat_split[9]), stof(mat_split[10]), stof(mat_split[11]),
			stof(mat_split[12]), stof(mat_split[13]), stof(mat_split[14]), stof(mat_split[15]),
		};
		myBindpose.inverseBindpose = glm::make_mat4(bbb);

		myObj->myBindSkeleton.skeletonData.push_back(myBindpose);
		joint = joint->NextSiblingElement("joint");
	}

	cout << "should be root = " << myObj->myBindSkeleton.skeletonData[0].name << " " << glm::to_string(myObj->myBindSkeleton.skeletonData[0].inverseBindpose) << endl;

	//myAbj.allBindSkeletons.push_back(myBindSkeleton);

	/* FRAME DATA */
	for (int i = 0; i < animCt; ++i) //1
	{
		const char *animationName;
		animationName = animation->Attribute("name");

		int animationLength;
		animation->QueryIntAttribute("length", &animationLength);

		int animationNumJoints;
		animation->QueryIntAttribute("numJoints", &animationNumJoints);

		SingleAnim mySingleAnim;
		mySingleAnim.name = animationName;
		mySingleAnim.length = animationLength;
		mySingleAnim.numJoints = animationNumJoints;

		for (int j = 0; j < animationNumJoints; ++j)
		{
			int trackID;
			track->QueryIntAttribute("id", &trackID);

			const char *trackName, *trackParent;
			trackName = track->Attribute("name");
			trackParent = track->Attribute("parent");

			TrackData myTrackData;
			myTrackData.id = trackID;
			myTrackData.name = trackName;
			myTrackData.parent = trackParent;

			frame = track->FirstChildElement("frame"); XMLCheckElement(frame, "frame");

			for (int k = 0; k < animationLength; ++k) //24
			{
				int frameNum;
				frame->QueryIntAttribute("num", &frameNum);

				FrameData myFrameData;
				myFrameData.frame = frameNum;

				tinyxml2::XMLElement *decompT = frame->FirstChildElement("decompT"); XMLCheckElement(decompT, "decompT");
				tinyxml2::XMLElement *decompR = frame->FirstChildElement("decompR"); XMLCheckElement(decompR, "decompR");

				vector<string> decompT_split = stringSplit(decompT->GetText(), ",");
				vector<string> decompR_split = stringSplit(decompR->GetText(), ",");

				myFrameData.decompT = glm::vec3(stof(decompT_split[0]), stof(decompT_split[1]), stof(decompT_split[2]));

				myFrameData.decompR = glm::quat(stof(decompR_split[3]), stof(decompR_split[0]), stof(decompR_split[1]), stof(decompR_split[2]));

				myTrackData.frameData.push_back(myFrameData);
				frame = frame->NextSiblingElement("frame");
			}

			mySingleAnim.trackData.push_back(myTrackData);
			track = track->NextSiblingElement("track");

		}

		myAbj.allAnims.push_back(mySingleAnim);
		animation = animation->NextSiblingElement("animation");


	}

	return 1;
}