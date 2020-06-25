#ifndef CORE_H
#define CORE_H

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

using namespace std;
namespace fs = std::filesystem;

class Object;
class Gizmo;

#define PI 3.14159f

struct BoneInfo
{
	//glm::mat4 BoneOffset;
	glm::mat4 FinalTransformation;

	Matrix4f BoneOffset;
	//Matrix4f FinalTransformation;

};

struct AbjNode
{
	string name;
	int width, height;
	GLuint fbo0, tex0_32;
	GLuint64 tex0_64;
	GLuint fbo1, tex1_32;
	GLuint64 tex1_64;
	GLuint DS_32;
	GLuint64 DS_64;
	int idx;
	uint ID;
} ;

struct GLSharedData
{
	shared_ptr<Object> obj;
	GLuint VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX, VBO_BONEID, VBO_BONEWT;
} ;

struct Pro
{
	string name;
	GLuint pro;
} ;

struct TexMap
{
	string name, type, flat;
	uint ID;
	vector<AbjNode> layer;
	bool loaded;
} ;

 struct Brush
{
	string name;
	glm::vec3 scale;
	float opac;
	uint ID;
	glm::vec2 coord;
} ;

struct Stroke
{
	glm::vec2 coord;
	glm::vec3 scale;
	float opac;
} ;

//struct
//{
//
//};

//struct
//{
//	glm::vec2 posOnEdge; //LRUD
//	glm::vec2 pos; //inside
//	bool on1x1andHidden;
//	double openTime, closeTime;
//	int whichMonitor;
//
//	//when its been scaled down to so far its no longer visible
//
//	//posOnEdge
//	//string which edge : URBL
//
//} pixel;

struct CubeIrradSpec
{
	string name, irrad, spec;
} ;

 struct NameIdx
{
	string name;
	int idx;
} ;

struct aiSceneStored
{
	const aiScene *scene;
	string name;
	bool animated;
	//glm::mat4 globalInvXform;
	Matrix4f globalInvXform;
	int groupIdx;
	NameIdx nameIdx;
} ;

 struct bbSkel
{
	string name, nameBone, nameMesh;
	glm::mat4 obbMVP;
	glm::vec3 min, max;
	int linkedGrp;
} ;

struct BlendingIndexWeightPair
{
	uint mBlendingIndex;
	double mBlendingWeight;

	BlendingIndexWeightPair() : mBlendingIndex(0), mBlendingWeight(0)
	{

	}
};

struct CtrlPoint
{
	glm::vec3 mPosition;
	vector<BlendingIndexWeightPair> mBlendingInfo;

	CtrlPoint()
	{
		mBlendingInfo.reserve(4); //4 bone influence
	}
};

struct VertexBlendingInfo
{
	uint mBlendingIndex;
	double mBlendingWeight;

	bool operator < (const VertexBlendingInfo &rhs)
	{
		return (mBlendingWeight > rhs.mBlendingWeight);
	}
};

struct PNTIWVertex
{
	glm::vec3 mPosition, mNormal, mTangent;
	glm::vec2 mUV;
	vector<VertexBlendingInfo> mVertexBlendingInfos;

	void SortBlendingInfoByWeight()
	{
		sort(mVertexBlendingInfos.begin(), mVertexBlendingInfos.end());
	}

	bool operator == (PNTIWVertex &rhs)
	{
		bool sameBlendingInfo = 1;

		//only compare the blending infos when there is any
		if (!(mVertexBlendingInfos.empty() && rhs.mVertexBlendingInfos.empty()))
		{
			//each vert should have 4 index-weight blending info pairs because games typically distribute weights to 4 joints
			for (uint i = 0; i < 4; ++i)
			{
				if (mVertexBlendingInfos[i].mBlendingIndex != rhs.mVertexBlendingInfos[i].mBlendingIndex ||
					abs(mVertexBlendingInfos[i].mBlendingWeight - rhs.mVertexBlendingInfos[i].mBlendingWeight) > .001
					)
				{
					sameBlendingInfo = 0;
					break;
				}
			}
		}

		bool result0 = (mPosition == rhs.mPosition);
		bool result1 = (mNormal == rhs.mNormal);
		bool result2 = (mUV == rhs.mUV);
		bool result3 = (mTangent == rhs.mTangent);

		return result0 && result1 && result2 && result3 && sameBlendingInfo;
	}
};

struct Keyframe
{
	FbxLongLong mFrameNum;
	FbxAMatrix mGlobalTransform;
	Keyframe *mNext;

	Keyframe() : mNext(nullptr)
	{

	}
};

struct Joint
{
	string mName;
	int mParentIndex;
	FbxAMatrix mGlobalBindposeInverse;
	FbxAMatrix mGlobalBindpose;
	FbxNode *mNode;
	vector<FbxAMatrix> keyframes;
};

struct Triangle
{
	vector<uint> mIndices;
	string mMaterialName;
	uint mMaterialIndex;

	bool operator < (const Triangle &rhs)
	{
		return (mMaterialIndex < rhs.mMaterialIndex);
	}
};

struct MultiAttrKey {
	int frame;
	float val;
} ;

class MultiAttr
{
public:
	MultiAttr() { ; }
	shared_ptr<MultiAttr> Clone() const { return(shared_ptr<MultiAttr>(CloneImpl())); }

	string typeX = "ALL";
	string grp, name, type, val_s;

	bool repop = 1;
	bool val_b;
	int val_i, idx_3;
	int tab = 0;
	int idx;
	float min = -9999.f;
	float max = 9999.f;
	float val_f;
	glm::vec2 val_2;
	glm::vec3 val_3;
	glm::vec4 val_4;
	vector<string> comboList;
	string cut;

	vector<MultiAttrKey> keys;

	//if only 1 key has been set, it stays at that value forever
	//set a second key at a different time with a different value
	//<int, float>

	//protected:
	virtual MultiAttr* CloneImpl() const { return(new MultiAttr(*this)); }
};

struct IndentSpacingAI
{
	string nodeName;
	int spacing;
};

struct FrameData
{
	int frame;
	glm::mat4 transform;
	glm::vec3 decompT;
	glm::quat decompR;
};

struct TrackData
{
	int id;
	string name, parent;
	vector<FrameData> frameData;
};

struct SingleAnim
{
	string name;
	int length, numJoints;
	vector<TrackData> trackData;
};

struct ABindpose
{
	string name, parent;
	glm::mat4 inverseBindpose;
	glm::vec3 decompT;
	glm::quat decompR;
};

struct DieFaceChoice {
	int die;
	int face;
	int choice;
};

struct Abj
{
	vector<string> allChoices;
	vector<string> dieFaceStrokes;
	vector<DieFaceChoice> allDFC;
	bool dieTgl;
	string dieRollChoice;
	int dieMaxDecimalPlaces;
	
	long dieLerpTimeStart;
	//float dieTimeDelta;
	float dieMsgStartA;
	float dieMsgEndA;
	float dieMsgDurSec;





	vector<SingleAnim> allAnims;

	vector <IndentSpacingAI> allIndents;
	string indent = "";

	bool debugX = 0;
	bool cursorUse;
	string cursorName, startupSceneName;

	vector<TexMap> allTexMaps;
	vector<Pro> allPro;;
	vector<shared_ptr<Object>> allCamLi, allGiz, allGizSide, allGrid, allObj, newObj, frustumObjs;
	vector<CubeIrradSpec> allCubeIrradSpec;
	string myCube = "ENNIS"; //GLACIER GRACE PISA UFFIZI

	vector<AbjNode> allShadow;
	vector<shared_ptr<Brush>> allBrushes;

	shared_ptr<Object> selB, selCamLi, myBB, myTxt, myFSQ, myPivot, myGizNull, myVolCone, paintStroke, mySelRect, shadowObj, shadowObjUBO, myGui, myBill, createNonFBX;
	shared_ptr<Brush> selBrush, selEraser;
	vector<GLSharedData> GLDataSh;

	float gamma, gizScale;
	string gizSpace;

	int lightCt, lightIter, brushSize, brushHard;
	GLuint cubeM_specular_32, cubeM_irradiance_32;

	GLuint pro, uboLight, uboScene, uboDebug;
	GLuint64 uboLight_64, uboScene_64, uboDebug_64;
	string proN;
	int width, height;
	int monitorX, monitorY;

	//timer (make sep struct)
	bool mpfTgl;
	string mpf;
	uint tick_frames;
	double tick_new, tick_old, tick_diff;
	float mpfTime, dTime;

	bool searchB;
	bool lmbTgl, mmbTgl, rmbTgl, altTgl, ctrlTgl, shiftTgl, spaceTgl;
	bool aTgl, bTgl, cTgl, dTgl, eTgl, fTgl, gTgl, hTgl, iTgl, jTgl, kTgl, lTgl, mTgl, nTgl, oTgl, pTgl, qTgl, rTgl, sTgl, tTgl, uTgl, vTgl, wTgl, xTgl, yTgl, zTgl;
	bool colorPickTgl, disableSelRect, gizSideTgl, gizSpaceTgl, singleShotRC, statsTgl, wireOverTgl;

	//FBO
	bool fboReady;
	int currLum;

	GLuint gBuf0_32, gBuf1_32, gBuf2_32, gBuf3_32, gBuf4_32, gBuf5_32, gBuf6_32, gBuf7_32, gBuf_DS_32;
	GLuint64 gBuf0_64, gBuf1_64, gBuf2_64, gBuf3_64, gBuf4_64, gBuf5_64, gBuf6_64, gBuf7_64, gBuf_DS_64;

	GLuint normalRuff0_32, normalRuff1_32, gBufAddT_DS_32;
	GLuint64 normalRuff0_64, normalRuff1_64, gBufAddT_DS_64;

	GLuint rttGaussIn32, tempGauss;
	GLuint64 rttGaussIn64, downSamp_64, extractHLfromSrc_64;

	AbjNode gBufN, normalRuffN, gui_gBufN, bloomN, bloomGaussN[6], defN, depthRevN, downN[6], fxaaN, lumaAdaptN[2], lumaInitN, bgN, stereoPrevN, stereoN[2], ssaoN, ssaoGaussN, ssrN, tonemapN, alphaGaussN, billN, guiN, gui_DepthRevN;
	AbjNode brushN, brushBGN, brushTempN, eraserN, cursorN, sobelN;
	bool bakeNow;

	glm::mat4 PMd, PMstored, PM_cube, VM_cube, MM_cube;

	float tabletPressure;
	string penOrientation, paintType;
	bool paintMode, dragDrop;
	int edgeDetect_mode;

	bool quitTgl, stereoTgl, stereoLR;
	int stereoSwitchLR, stereoMethod;
	float stereoSep;

	//GL
	float aspect, aspectSide, NDC_x, NDC_y, rayIntersectDist, fpsMouseSpeed, tumbleSpeed, panSpeed, panSpeed_ortho, dollySpeed, dollySpeed_ortho, dollySpeed_wheel;
	glm::mat4 VMgizSide, PM, PMgizSide, PMinv_cube;
	glm::vec2 pMouseNew, pMouseNew_stored, pMouseOld, pMouseDiff, rayP, texelSize;
	glm::vec2 selRect_LD, selRect_RU, rezGate_LD, rezGate_RU;
	glm::vec3 upWorld, from_OBB, to_OBB, aspectXYZ;
	vector<Stroke> strokes_brush, strokes_eraser, strokes_brush_cursor, strokes_eraser_cursor, strokes_cursor;
	string selMode;

	glm::vec3 gizSideS, Csel, CselManip, Ctxt, Cwire, Cgrid;
	int gridLines;

	bool UBO_light_needsUp, brushOutlineUpB, debug0;
	int copyTgt;
	string pDefDyn;

	glm::vec3 brushRGB;
	glm::vec4 brushRGBA;
	float brushA;

	vector<glm::vec2> selRectPts_color, selRectPts_usable;

	string gizHoverType, gizTransType;
	glm::vec3 gizN, gizMouseDown, giz_rayOrigin, giz_rayDir, gizHoverCheckX, gizHoverCheckY, gizHoverCheckZ;

	int blendModeD, selAccuracy;
	bool moveDist_paint, firstPress, doEraserDebug, paintCursorResizeTgl;
	float distDragPaint;
	glm::vec2 paintCursorResize_p;
	glm::vec2 P_currF, P_prevF;
	TexMap myLayerIdx, sobelMap;

	Gizmo *myGizmo;

	long m_startTime, m_rippleStartTime;
	long lastFrameTime = 0;
	bool isInAir = 0;
	float deltaFrameTime;
	static const uint MAX_BONES = 100;

	double jumpTimer;
	float storedCharRotYPlane = 0.f;
	float storedCharRotYPlaneMatch = 0.f;
	float storedTeapotY = 0.f;
	bool prevFrameHoldControllerY = 0;
	float leftStickAnglePrev = 0;

	float dudvTime = 0;
	long dudvStartTime;

	string heroObj = "yourName";
	vector<string> heroObjects;

	//////////
	//aiAnim
	//////////
	vector<aiSceneStored> aiAnimScenes;
	glm::mat4 translateSphereVol;
	int myNewObjNumVerts;

	vector<string> aiNameUnknown;
	string linkedName;
	int aiLoadCt = 0;

	float _blendTimeMult = .3f;
	bool showHideTaskbar = 0;
	bool channel = 0;



	//////////////////////
	GLFWwindow *GLFWwin;
	glm::ivec2 winPosGlobal;

	bool matchCamera = 1;

};

void myAbjInit();

extern Abj myAbj;

#endif