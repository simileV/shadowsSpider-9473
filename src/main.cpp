#include "pch.h"
#include "Core.h"
#include "Window.h"
#include "Input.h"
#include "Setup_obj.h"
#include "Setup_texShaders.h"
//#include "FBXtoAbj.h"
#include "FileSystem.h"

Abj myAbj;


int main(int argc, char *argv[]) //DEBUG FBX TO ABJ CONVERSION / CREATION
{
	srand(static_cast<int>(time(0)));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE); //

	/* WIDTH / HEIGHT */

	myAbj.monitorX = 600;
	myAbj.monitorY = 675;
	myAbj.width = 600;
	myAbj.height = 600;

	//myAbj.monitorX = 1920;
	//myAbj.monitorY = 1080;

	//myAbj.width = 1280;
	//myAbj.height = 720;

	//myAbj.width = 800;
	//myAbj.height = 600;

	//myAbj.winPosGlobal = glm::ivec2(0, -480); //
	myAbj.winPosGlobal = glm::ivec2(0, 0); //

	//CENTER
	int posHalfL = myAbj.width / 2;
	int posHalfU = myAbj.height / 2;
	int posHalfMonL = myAbj.monitorX / 2;
	int posHalfMonU = myAbj.monitorY / 2;

	myAbj.winPosGlobal = glm::ivec2(posHalfMonL - posHalfL, posHalfMonU - posHalfU); //


	myAbj.GLFWwin = glfwCreateWindow(myAbj.width, myAbj.height, "Shadows Spider", 0, 0); //windowed
	glfwSetWindowPos(myAbj.GLFWwin, myAbj.winPosGlobal.x, myAbj.winPosGlobal.y);

	glfwMakeContextCurrent(myAbj.GLFWwin);
	glewExperimental = 1;
	glewInit();
	glfwSetInputMode(myAbj.GLFWwin, GLFW_STICKY_KEYS, GL_TRUE);
	//glfwSetInputMode(myAbj.GLFWwin, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(myAbj.GLFWwin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetCursorPosCallback(myAbj.GLFWwin, cursorPosCallback);
	glfwSetMouseButtonCallback(myAbj.GLFWwin, mouseButtonCallback);
	glfwSetKeyCallback(myAbj.GLFWwin, keyCallback);
	glfwSetScrollCallback(myAbj.GLFWwin, scrollCallback);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	double mpf_oldTime = glfwGetTime();
	int mpf_framesPerSec = 0;
	glfwSwapInterval(0); //vsync off

	///////////
	myAbjInit();
	mapInit();
	proInit();
	camInit();
	gizInit();
	objInit();
	brushInit();

	for (auto &i : myAbj.allObj)
	{
		if (i->name->val_s == "persp")
			myAbj.selCamLi = i;

		//if (i->name->val_s == "third")
			//myAbj.selCamLi = i;
	}

	//myAbj.startupSceneName = "AItest";
	//myAbj.startupSceneName = "lerpTest0";
	myAbj.startupSceneName = "dirLightPosTest";
	//myAbj.startupSceneName = "stompBox";
	//myAbj.startupSceneName = "fbxAnimTest";

	startupScene(myAbj.startupSceneName);
	//startupScene("AItest"); ////
	//startupScene("fbxAnimTest"); ////


	//startupScene("AItest"); ////
	//startupScene("BBabj");
	//startupScene("BBabjAI");
	//startupScene("cascadedShadows");
	//startupScene("fbxSkellyTest");
	//startupScene("fbxAnimTest"); ////
	//startupScene("fbxTest");
	//startupScene("fixPointAndSpot");
	//startupScene("transpGrass");
	//startupScene("volumeCone");
	//startupScene("VST");
	//startupScene("VSTabj");

	//myAbj.heroObj = "testFBX";
	myAbj.heroObj = "torusExtruded";


	myAbj.myGizmo = new Gizmo();

	for (auto &i : myAbj.allCamLi)
	{
		if (i->camLiType->val_s == "DIR" || i->camLiType->val_s == "SPOT")
		{
			i->RM = i->rotOrderUse(i->rotOrder->val_s); //init RM for DIR lights
		}
	}

	addDeleteShadows("add");
	uboInit();
	myAbj.lightCt = countLights();

	resize();

	//myAbj.myFSQ->fillBoneLocArray();

	glfwFocusWindow(myAbj.GLFWwin);

	//myAbj.mpfTime = GetTickCount();
	myAbj.m_startTime = GetTickCount();
	myAbj.lastFrameTime = GetTickCount();
	myAbj.m_rippleStartTime = GetTickCount();
	myAbj.jumpTimer = GetTickCount();

	do
	{
		/* MPF TIMER */
		{
			//240fps = 4.166
			//120fps = 8.333
			//60fps = 16.667
			//30fps = 33.333

			//double mpf_currentTime = glfwGetTime();
			//++mpf_framesPerSec;

			//if (mpf_currentTime - mpf_oldTime >= 1.f) //change title / reset
			//{
			//	stringstream ss;
			//	ss << 1000.0 / mpf_framesPerSec;

			//	string mpfStr = ss.str();
			//	string myWinTitle = "Shadows Spider";
			//	myWinTitle += " | " + mpfStr + " [ms]";
			//	const char *myMPF = myWinTitle.c_str();

			//	glfwSetWindowTitle(myAbj.GLFWwin, myMPF);

			//	mpf_framesPerSec = 0;
			//	mpf_oldTime = glfwGetTime();
			//}
		}

		renderFrame();

		glfwSwapBuffers(myAbj.GLFWwin);
		glfwPollEvents();
	}

	while
		(!myAbj.quitTgl && glfwWindowShouldClose(myAbj.GLFWwin) == 0);

	quitSeq();

	return 0;
}

void myAbjInit()
{
	/* STEREO */
	myAbj.stereoTgl = 0;
	//myAbj.stereoTgl = 1;

	myAbj.stereoMethod = 1;
	myAbj.stereoSwitchLR = -1;
	//myAbj.stereoSwitchLR = 1;

	myAbj.stereoLR = 0;
	//myAbj.stereoSep = 0.1f;
	//myAbj.stereoSep = 0.15f;
	myAbj.stereoSep = 0.2f;
	//myAbj.stereoSep = .3f;


	myAbj.dieTgl = 0;
	myAbj.dieMaxDecimalPlaces = 3;

	myAbj.quitTgl = 0;
	myAbj.gamma = 1.f / 2.2f;
	myAbj.gizScale = 1.75f;
	myAbj.gizSpace = "world";
	myAbj.upWorld = glm::vec3(0.f, 1.f, 0.f);
	myAbj.lightCt = 0;
	myAbj.brushSize = 10;
	myAbj.brushHard = 100;
	myAbj.fboReady = 0;
	myAbj.currLum = 0;
	myAbj.gizSideS = glm::vec3(80.f, 40.f, 3.f);
	myAbj.UBO_light_needsUp = 1; //update first by default
	myAbj.gridLines = 20;
	//myAbj.gridLines = 100;

	myAbj.cursorUse = 1;
	myAbj.cursorName = "ROUND_BRUSH";
	//myAbj.cursorName = "SQUARE_BRUSH";

	myAbj.bakeNow = 0;
	myAbj.penOrientation = "PEN";
	myAbj.paintType = "NONE";
	myAbj.paintMode = 0;
	myAbj.dragDrop = 0;
	myAbj.edgeDetect_mode = 0;
	myAbj.selMode = "OBJ";
	myAbj.disableSelRect = 0;

	myAbj.colorPickTgl = 0;
	myAbj.statsTgl = myAbj.wireOverTgl = 0;
	myAbj.mpfTgl = 1; //
	myAbj.gizSideTgl = 1;
	myAbj.gizSpaceTgl = 1;

	myAbj.Csel = glm::vec3(.3f, 1.f, 1.f);
	myAbj.CselManip = glm::vec3(.557f, .333f, .067f);
	myAbj.Ctxt = glm::vec3(1.f, 1.f, 0.f);
	myAbj.Cwire = glm::vec3(0.f);
	myAbj.Cgrid = glm::vec3(0.f);

	myAbj.altTgl = myAbj.ctrlTgl = myAbj.shiftTgl = myAbj.lmbTgl = myAbj.mmbTgl = myAbj.rmbTgl = myAbj.spaceTgl = myAbj.colorPickTgl = 0;
	myAbj.wTgl = myAbj.sTgl = myAbj.aTgl = myAbj.dTgl = myAbj.rTgl = myAbj.fTgl = myAbj.vTgl = 0;

	myAbj.debug0 = 0;
	myAbj.copyTgt = 0;
	myAbj.blendModeD = 999;
	myAbj.moveDist_paint = 0;
	myAbj.firstPress = 1;
	myAbj.doEraserDebug = 1;
	myAbj.paintCursorResizeTgl = 0;
	myAbj.distDragPaint = 15.f;
	myAbj.fpsMouseSpeed = .01f;
	myAbj.tumbleSpeed = .15f;
	myAbj.panSpeed = .07f;
	myAbj.panSpeed_ortho = .03f;
	myAbj.dollySpeed = .05f;
	myAbj.dollySpeed_ortho = .01f;
	myAbj.dollySpeed_wheel = 2.f;
	myAbj.selAccuracy = 30;

	myAbj.gizHoverType = "NONE";
	myAbj.gizTransType = "NONE";
}