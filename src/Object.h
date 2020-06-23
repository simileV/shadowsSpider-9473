#ifndef OBJECT_H
#define OBJECT_H

#include "Core.h"
#include "Setup_texShaders.h"
#include "StringManip.h"

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define NUM_BONES_PER_VERTEX 4

typedef struct
{
	glm::vec3 v1, v2, v3;
} FPlane;

typedef struct
{
	string name;
	uint ID;
} NameID;

typedef struct
{
	NameID x, y;
} TwoNameID;

typedef struct
{
	string type;
	NameID map, layer;
	vector<TwoNameID> typeMap, mapLayer;
} TexSel;

typedef struct
{
	string name, nameBone, nameMesh;
	glm::mat4 animatedXform;
} AnimBone;

struct BindSkeleton
{
	int skeletonCt;
	vector<ABindpose> skeletonData;
};

class Object
{
public:
	Object();

	Object(const Object &);
	shared_ptr<Object> Clone() const { return(shared_ptr<Object>(CloneImpl())); }
	virtual Object* CloneImpl() const { return(new Object(*this)); }
	
	bool VAO_loaded;
	GLuint VAO;
	vector<glm::vec3> pE, nE, tE;
	vector<glm::vec2> uvE;
	vector<glm::ivec4> boneIdE; //
	vector<glm::vec4> boneWtE;
	vector<GLuint> idxE;
	vector<GLushort> idxBBE;

	shared_ptr<Object> parentTo;

	vector<shared_ptr<MultiAttr>> multiObj;

	BindSkeleton myBindSkeleton;

	shared_ptr<MultiAttr> name, t, r, v, bb, anim, animAI, debugSkelGen, debugSkel, debugSkelName;
	shared_ptr<MultiAttr> tx, ty, tz;
	shared_ptr<MultiAttr> sx, sy, sz;
	shared_ptr<MultiAttr> albedoM, alphaM, anisoM, cubeM, lensM, metallicM, normalM, ruffM, dudvM;
	shared_ptr<MultiAttr> Ko, ior, ruffA, ruffOren;
	shared_ptr<MultiAttr> shadowCast, twoSided, Cwire, normWt, piv, rotOrder;

	shared_ptr<MultiAttr> albedoTile, alphaTile, anisoTile, normalTile, ruffTile;

	shared_ptr<MultiAttr> camLiType;
	shared_ptr<MultiAttr> fov, nearClip, farClip, nearShadow, farShadow, orthoFree, orthoType, orthoZoom;

	shared_ptr<MultiAttr> Cl, lInten, lSpotI, lSpotO;
	shared_ptr<MultiAttr> volCone, volDist, volS;

	shared_ptr<MultiAttr> bloomInten, bloomLensInten;
	shared_ptr<MultiAttr> adaptTime, adaptAuto, expo, Kgi, vign, vignDist;
	shared_ptr<MultiAttr> fxaaBlur, fxaaSubPix, fxaaEdgeThr, fxaaEdgeThrMin;
	shared_ptr<MultiAttr> ssaoBias, ssaoInten, ssaoRad;
	shared_ptr<MultiAttr> paintSep, clearBehav, displMode, edgeThr;
	shared_ptr<MultiAttr> ssrInten, ssrIter, ssrRefine, ssrPixStride, ssrPixZSize, ssrPixStrideZ, ssrMaxRayDist, ssrEdgeFade, ssrEyeFade0, ssrEyeFade1;
	shared_ptr<MultiAttr> transpW, ripple, dieMsgAlpha;

	float distO;
	glm::vec3 lookO, rightO, upO, targO, spotTarget;
	glm::vec3 prevTargO = glm::vec3(0.f);

	bool dirtyShadow, dirtyVM, expand, ignoreOutliner, ref, selected, deletable, gridV, selectable, hover, tempSel;

	int vertsOnObj, guiHeight, guiWidth;
	string dupeStenFix = "999";
	string type;

	glm::mat4 biasM, PM2D;
	glm::vec3 Crand;
	bool showN = 0;
	int gaussStage;
	TexSel texSel;

	glm::vec3 Cgiz, Cgiz_stored;
	string gizType;
	bool gizSideObj = 0;

	//frustum D
	glm::vec3 nc, ntl, ntr, nbl, nbr, fc, ftl, ftr, fbl, fbr;
	float Hnear, Wnear, Hfar, Wfar;
	vector<FPlane> fPlanes_temp;
	glm::vec4 fPlanes[6];
	vector<glm::vec3> AABB_WS;
	void buildFrustumPlanes();

	bool isSphereInFrustum(glm::vec3, glm::vec3);
	bool isAABBInFrustum(glm::vec3, glm::vec3);
	bool isAABBInFrustumAlt(glm::vec3, glm::vec3);
	//void frustumCull();

	const char *txt2D;
	glm::vec2 txtOrigin;

	glm::mat3 NM;
	glm::mat4 MVP, MV, MM, PM, VM, TM, RM, SM;
	glm::mat4 debugSkellyMM;
	glm::mat4 bbScaleM, bbrotM, bbtransM, obbMVP;
	glm::mat4 pivM, pivRtM, rpM, rM;
	glm::vec3 bbMin, bbMax, bbCenter, bbSize, bbSizeFull;
	glm::vec3 pivRt;

	NameIdx curSceneNI = { "ZZZ" , 1 };
	NameIdx prevSceneNI = { "ZZZ" , 1 };

	void VAO_load();
	void render();
	void shadowMatrixPass(string);

	void BBup();

	void deleteVAO_VBO();
	void glErrorPrint(const char *);
	void rename(string);
	void parentObj(string);
	void setTarg(glm::vec3, float);
	bool camLiTypeGet(string);
	void setDirty();
	glm::mat4 rotOrderUse(string);
	void tileMaps(GLuint);
	void mvpGet();
	void setTexSel_init();

	/* START ASSIMP ANIM */
	static const uint MAX_BONES = 100;

	struct VertexBoneData
	{
		//remember, NUM_BONES_PER_VERTEX == 4
		uint IDs[NUM_BONES_PER_VERTEX];
		float Weights[NUM_BONES_PER_VERTEX];

		VertexBoneData()
		{
			//Reset();
			ZERO_MEM(IDs);
			ZERO_MEM(Weights);
		};

		//void Reset()
		//{
		//	ZERO_MEM(IDs);
		//	ZERO_MEM(Weights);
		//}

		void AddBoneData(uint BoneID, float Weight, shared_ptr<Object> myObj, uint VertexID);
	};

	/* AI */
	void boneTransformGrp_AI(int grpIdx, uint numBones);
	void boneTransform_AI(vector<glm::mat4> &Transforms, int grpIdx, uint numBones);
	void setAnim(string animName);
	void ApplyPose_AI(float, const aiNode *, Matrix4f, const aiScene *, int);
	glm::mat4 toGLM(aiMatrix4x4);
	glm::mat4 toGLM(Matrix4f);
	glm::mat4 toMatrix4f(glm::mat4);

	void CalcInterpolatedRotationAI_stock(float, const aiNodeAnim *, aiQuaternion &);
	void CalcInterpolatedPositionAI_stock(float, const aiNodeAnim *, aiVector3D &);
	uint FindRotationAI(float AnimationTime, const aiNodeAnim *pNodeAnim);
	uint FindPositionAI(float AnimationTime, const aiNodeAnim *pNodeAnim);

	/* SOLO */
	void boneTransformGrpABJ_solo();
	void CalcInterpolatedPositionGLM_solo(float, TrackData, glm::vec3 &);
	void CalcInterpolatedRotationGLM_solo(float, TrackData, glm::quat &);
	void ApplyPose(float, TrackData, const glm::mat4 &);
	uint FindPositionGLM_solo(float AnimationTime, TrackData track);

	vector<AnimBone> animBones;

	void boneTransformGrpABJ();
	//void ReadNodeHiNoBlendABJ(float, ABindpose, const glm::mat4 &);
	void ReadNodeHiNoBlendABJ(float, TrackData, const glm::mat4 &);


	//void Object::boneTransformGrpAI(int grpIdx, uint numBones);
	//void ReadNodeHiNoBlendAI(float, const aiNode *, const Matrix4f &, const aiScene *, int);
	//void ReadNodeHiBlendAI(float, float, const aiNode *, const aiNode *, const aiScene *, const aiScene *, const Matrix4f &, int);
	const aiNodeAnim* FindNodeAnim(const aiAnimation *, const string);

	map<string, uint> m_BoneMapping; // maps a bone name to its index
	uint m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	vector<VertexBoneData> Bones;

	//uint FindPosition(float, const aiNodeAnim *);
	//void CalcInterpolatedPosition(float, const aiNodeAnim *, aiVector3D &);
	//void CalcInterpolatedPositionGLM(float, const ABindpose *, glm::vec3 &);
	//void CalcInterpolatedPositionGLM(float, glm::vec3 &);
	void CalcInterpolatedPositionGLM(float, TrackData, glm::vec3 &);
	uint FindPositionGLM(float, TrackData);


	//uint FindRotation(float, const aiNodeAnim *);
	//void CalcInterpolatedRotation(float, const aiNodeAnim *, aiQuaternion &);
	//void setAnim(string);
	void CalcInterpolatedRotationGLM(float, TrackData, glm::quat &);


	int linkedGrp;
	vector<bbSkel> bbSkelAll;
	glm::mat4 aabbMVP;
	bool aabbTgl = 0;
	bool obbTgl = 0;
	bool spherebbTgl = 0;
	vector<glm::vec4> aabbV4OS, aabbV4WS;
	glm::vec3 bbMinOS, bbMaxOS;
	float blendingTime = 0.f;
	float animationTime0 = 0.f;
	float animationTime1 = 0.f;


	/* END ASSIMP ANIM */


protected:
	void proUse();
//
	glm::vec3 genColorID();
	string getIncName(string);
};

#endif
