#include "pch.h"

/*
reference:
http://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
*/

#include "Input.h"
#include "GL_render.h"


void keyCallback(GLFWwindow *myWin, int key, int scancode, int action, int mods)
{
	/* PRESS */
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_1)
		{
			//myAbj.selMode = "VERT";

			for (auto &i : myAbj.allObj)
			{
				if (i->name->val_s == "tube")
				{
					i->blendingTime = .3f;
					i->animationTime1 = 0.f;
					//switchAnim(i->name->val_s, "1_1");
				}
			}
		}

		else if (key == GLFW_KEY_2)
		{
			//myAbj.selMode = "EDGE";

			for (auto &i : myAbj.allObj)
			{
				if (i->name->val_s == "tube")
				{
					i->blendingTime = .3f;
					i->animationTime1 = 0.f;
					//switchAnim(i->name->val_s, "1_2");
				}
			}
		}

		else if (key == GLFW_KEY_3)
		{
			//myAbj.selMode = "FACE";

			for (auto &i : myAbj.allObj)
			{
				if (i->name->val_s == "tube")
				{
					i->blendingTime = .3f;
					i->animationTime1 = 0.f;
					//switchAnim(i->name->val_s, "1_3");
				}
			}
		}

		else if (key == GLFW_KEY_4)
		{
			//myAbj.selMode = "OBJ";
		}

		if (key == GLFW_KEY_LEFT_ALT)
		{
			myAbj.altTgl = 1;
			myAbj.disableSelRect = 1;
			clearCursor(myAbj.paintMode);
		}

		else if (key == GLFW_KEY_SPACE)
		{
			myAbj.spaceTgl = 1;
		}

		else if (key == GLFW_KEY_F4)
		{
			//myAbj.selB = 0;
			myAbj.selB = myAbj.myFSQ;
			myAbj.myFSQ->selected = 1;
			//fsq attr switch goes here
		}

		else if (key == GLFW_KEY_LEFT_CONTROL) myAbj.ctrlTgl = 1;
		else if (key == GLFW_KEY_LEFT_SHIFT) myAbj.shiftTgl = 1;
		else if (key == GLFW_KEY_EQUAL) myAbj.gizScale += .5f;
		else if (key == GLFW_KEY_MINUS) myAbj.gizScale -= .5f;
		else if (key == GLFW_KEY_A) myAbj.aTgl = 1;
		else if (key == GLFW_KEY_B) myAbj.bTgl = 1;
		else if (key == GLFW_KEY_C) myAbj.cTgl = 1;
		else if (key == GLFW_KEY_D) myAbj.dTgl = 1;
		else if (key == GLFW_KEY_E) myAbj.eTgl = 1;
		else if (key == GLFW_KEY_F) myAbj.fTgl = 1;
		else if (key == GLFW_KEY_G) myAbj.gTgl = 1;
		else if (key == GLFW_KEY_H) myAbj.hTgl = 1;
		
		else if (key == GLFW_KEY_I)
		{
			myAbj.iTgl = 1;
			//PaintWinTgl(1, 0);
		}

		else if (key == GLFW_KEY_J) myAbj.jTgl = 1;

		else if (key == GLFW_KEY_K)
		{
			myAbj.kTgl = 1;
			//PaintWinTgl(1, 1);
		}
		
		else if (key == GLFW_KEY_L) 
		{
			myAbj.lTgl = 1;
		}

		else if (key == GLFW_KEY_M) myAbj.mTgl = 1;
		else if (key == GLFW_KEY_N) myAbj.nTgl = 1;
		else if (key == GLFW_KEY_O) myAbj.oTgl = 1;
		else if (key == GLFW_KEY_P) myAbj.pTgl = 1;

		else if (key == GLFW_KEY_Q && mods == GLFW_MOD_CONTROL)
		{
			myAbj.quitTgl = 1;
		}
		
		else if (key == GLFW_KEY_Q) myAbj.qTgl = 1;
		else if (key == GLFW_KEY_R) myAbj.rTgl = 1;
		else if (key == GLFW_KEY_S) myAbj.sTgl = 1;
		else if (key == GLFW_KEY_T) myAbj.tTgl = 1;
		else if (key == GLFW_KEY_U) myAbj.uTgl = 1;
		else if (key == GLFW_KEY_V) myAbj.vTgl = 1;
		else if (key == GLFW_KEY_W) myAbj.wTgl = 1;
		
		else if (key == GLFW_KEY_X && mods == GLFW_MOD_ALT)
		{
			myAbj.gizSpace = myAbj.gizSpace == "local" ? "world" : "local";
		}

		else if (key == GLFW_KEY_X) myAbj.xTgl = 1;
		else if (key == GLFW_KEY_Y) myAbj.yTgl = 1;
		//else if (key == GLFW_KEY_Z) myAbj.zTgl = 1;
	}

	/* RELEASE */
	else if (action == GLFW_RELEASE)
	{
		//DELETE A CAMLI - remember to redo lightUBO

		if (myAbj.paintMode)
		{

		}

		//if (myAbj.dieTgl) { //manually input random dice rolls

		//	if (key == GLFW_KEY_0 || key == GLFW_KEY_1 || key == GLFW_KEY_2 || key == GLFW_KEY_3 || key == GLFW_KEY_4 || key == GLFW_KEY_5 || key == GLFW_KEY_6 || key == GLFW_KEY_7 || key == GLFW_KEY_8 || key == GLFW_KEY_9) {

		//		int usableInput = key - 48; //GLFW offset
		//		//cout << "usableInput = " << usableInput << endl;

		//		if (myAbj.dieFaceStrokes.size() < myAbj.dieMaxDecimalPlaces) {
		//			myAbj.dieFaceStrokes.push_back(to_string(usableInput));

		//			if (!myAbj.dieFaceStrokes.empty()) {
		//				myAbj.dieRollChoice.clear();
		//				for (int i = 0; i < myAbj.dieFaceStrokes.size(); ++i)
		//					myAbj.dieRollChoice += myAbj.dieFaceStrokes[i];
		//			}
		//		}
		//	}
		//}

		if (key == GLFW_KEY_1)
		{
			printGLM4x4(myAbj.selCamLi->MM, "MM");
			printGLM4x4(myAbj.selCamLi->VM, "VM");
			printGLM4x4(myAbj.selCamLi->PM, "PM");
		}

		else if (key == GLFW_KEY_2) {

		}

		else if (key == GLFW_KEY_3) {


			for (auto& i : myAbj.allObj)
			{
				//if (i->name->val_s == "teapot" || i->name->val_s == "sphere")
				if (i->name->val_s == "teapot")
				{
					i->bb->val_b = (i->bb->val_b) ? 0 : 1;
				}

			}
		}

		else if (key == GLFW_KEY_4) {

		}

		//BLUE SELECTION HIGHLIGHT FOR OBJ / 
		//VERT / EDGE / FACE NOT IMPLEMENTED YET

		else if (key == GLFW_KEY_5)
		{
			//myAbj.wireOverTgl = !myAbj.wireOverTgl;
		}

		else if (key == GLFW_KEY_8)
		{

		}

		else if (key == GLFW_KEY_9)
		{

		}

		else if (key == GLFW_KEY_0)
		{

		}

		else if (key == GLFW_KEY_BACKSPACE) {
			if (myAbj.dieTgl && !myAbj.dieFaceStrokes.empty()) {
				myAbj.dieFaceStrokes.resize(myAbj.dieFaceStrokes.size() - 1);
				myAbj.dieRollChoice.clear();

				for (int i = 0; i < myAbj.dieFaceStrokes.size(); ++i)
					myAbj.dieRollChoice += myAbj.dieFaceStrokes[i];
			}
		}

		else if (key == GLFW_KEY_ENTER)
		{
			//string choiceStored = "";

			//if (myAbj.dieTgl) {
			//	if (stoi(myAbj.dieRollChoice) <= 100) {
			//		for (int i = 0; i < myAbj.allDFC.size(); ++i)
			//		{
			//			if (myAbj.allDFC[i].face == stoi(myAbj.dieRollChoice)) {
			//				choiceStored = myAbj.allChoices[myAbj.allDFC[i].choice];
			//				break;
			//			}
			//		}
			//	}

			//	else {
			//		cout << "invalid number entered";
			//		//fade away over time
			//	}
			//}

			//if (myAbj.dieTgl) {
			//	myAbj.dieRollChoice = choiceStored;
			//}

		}

		else if (key == GLFW_KEY_EQUAL)
		{
			myAbj.gizScale += .5f;
		}

		else if (key == GLFW_KEY_MINUS)
		{
			myAbj.gizScale -= .5f;
			myAbj.gizScale = max(.5f, myAbj.gizScale);
		}

		else if (key == GLFW_KEY_F3)
		{
			myAbj.debug0 = !myAbj.debug0;
			//refresh "attr table"

			cout << "myAbj.debug0 = " << myAbj.debug0 << endl;
		}

		else if (key == GLFW_KEY_F4)
		{
			//fsq attr switch goes here in the future without ATB

			for (auto &i : myAbj.allObj)
			{
				i->selected = 0;

				if (i->name->val_s == "sun")
				{
					i->selected = 1;
					myAbj.selB = i;
				}
			}
		}

		else if (key == GLFW_KEY_DELETE)
		{
			deleteObj();
		}

		else if (key == GLFW_KEY_V && mods == GLFW_MOD_CONTROL)
		{
			//dupeObj();
		}

		//else if (key == GLFW_KEY_GRAVE_ACCENT)
		//{
		//	//show / hide prefs
		//	cout << "TOGGLE DIE INPUT" << endl;
		//	myAbj.dieTgl = !myAbj.dieTgl;
		//	myAbj.dieRollChoice.clear();
		//	myAbj.dieFaceStrokes.clear();
		//	
		//	//if (myAbj.dieTgl)
		//		//dieChoicesDebug();
		//}

		else if (key == GLFW_KEY_GRAVE_ACCENT)
		{
			//show / hide prefs
			cout << "TOGGLE DIE INPUT" << endl;
			
			myAbj.dieTgl = !myAbj.dieTgl;
			myAbj.dieRollChoice.clear();
			myAbj.dieFaceStrokes.clear();
			myAbj.myTxt->dieMsgAlpha->val_f = 1.f;

			myAbj.dieRollChoice = to_string(randomBetw(1, 100));

			//press Enter
			string choiceStored = "";

			if (myAbj.dieTgl) {
				if (stoi(myAbj.dieRollChoice) <= 100) {
					for (int i = 0; i < myAbj.allDFC.size(); i++)
					{
						if (myAbj.allDFC[i].face == stoi(myAbj.dieRollChoice)) {
							choiceStored = myAbj.allChoices[myAbj.allDFC[i].choice];
							break;
						}
					}
				}

				else
				{
					cout << "invalid number entered" << endl;
					//fade out over time
				}
			}

			if (myAbj.dieTgl) {
				myAbj.dieRollChoice = choiceStored;
				//myAbj.dieRollChoice = "model starcraft unit";
			}

			myAbj.myFSQ->animationTime0 = 0.f;

			//if (myAbj.dieTgl) {
			//	//myAbj.dieTime0 = 0;
			//}

			//give result
			//store number / choice into DB

			//if result over max, slip away

			//prefs with number of dice
			//faces per die
		}

		if (key == GLFW_KEY_LEFT_ALT)
		{
			myAbj.altTgl = 0;

			if (!myAbj.lmbTgl)
				myAbj.disableSelRect = 0;
		}

		else if (key == GLFW_KEY_LEFT_CONTROL)
		{
			myAbj.ctrlTgl = 0;
			clearCursor(myAbj.paintMode);
		}

		else if (key == GLFW_KEY_LEFT_SHIFT) myAbj.shiftTgl = 0;
		//else if (key == GLFW_KEY_SPACE) myAbj.spaceTgl = 0;

		else if (key == GLFW_KEY_SPACE)
		{
			myAbj.spaceTgl = 0;

			for (auto &i : myAbj.allCamLi)
			{
				if (i->camLiTypeGet("cam") && i->selected)
				{
					myAbj.selCamLi = i;
					myAbj.selCamLi->setDirty();

					matchFoundRaycast(i);

					//setlightsDirty
					//resize to redo ortho
					resize();

					myAbj.myGizNull->v->val_b = 0;
				}
			}
		}
		
		else if (key == GLFW_KEY_ESCAPE)
		{
			myAbj.altTgl = 0;
			myAbj.disableSelRect = 1;
		}

		//////////////////
		else if (key == GLFW_KEY_A)
		{
			myAbj.aTgl = 0;
		}
		
		else if (key == GLFW_KEY_B)
		{
			myAbj.bTgl = 0;
			myAbj.bakeNow = 1;

			for (auto &i : myAbj.allObj)
			{
				if (i->selected)
				{
					i->bb->val_b = !i->bb->val_b;
					cout << "name / bb = " << i->name->val_s << " " << i->bb->val_b << endl;
				}
			}
		}
		
		else if (key == GLFW_KEY_C)
		{
			if (myAbj.myFSQ->clearBehav->val_s == "Manual")
				clearCanvas();

			myAbj.cTgl = 0;
		}
		
		else if (key == GLFW_KEY_D)
		{
			myAbj.dTgl = 0;

			if (!myAbj.ctrlTgl)
				pivTgl();
		}

		else if (key == GLFW_KEY_E)
		{
			myAbj.eTgl = 0;

			if (myAbj.paintMode == 1)
			{
				myAbj.penOrientation = (myAbj.penOrientation == "ERASER") ? "PEN" : "ERASER";
				cout << "myAbj.penOrientation = " << myAbj.penOrientation << endl;
			}

			gizShow("R");
		}

		else if (key == GLFW_KEY_F)
		{
			myAbj.fTgl = 0;

			if (myAbj.selB)
			{
				auto sizeByM = myAbj.selB->MM * glm::vec4(myAbj.selB->bbSize, 0.f);
				glm::vec3 size(sizeByM.x, sizeByM.y, sizeByM.z);
				auto dist = glm::sqrt(glm::dot(size, size)) / glm::sin(glm::radians(myAbj.selCamLi->fov->val_f * .5f));

				myAbj.selCamLi->setTarg(myAbj.selB->piv->val_3, dist * .5f);
			}
		}

		else if (key == GLFW_KEY_G)
		{
			myAbj.gTgl = 0;
			myAbj.selCamLi->gridV = !myAbj.selCamLi->gridV;
		}

		else if (key == GLFW_KEY_H)
		{
			myAbj.hTgl = 0;

			cout << "RELEASING H" << endl;

			//application toggles between "channel A" and "channel B" - for protection from unwanted eyes
			//runs alternate shader
		
			myAbj.channel = !myAbj.channel;

			//channel 0 == quadro
			//channel 1 cycles between a few presets
		}

		else if (key == GLFW_KEY_I)
		{
			myAbj.iTgl = 0;

			//if (myAbj.myPaintWin->stackedMain->currentIndex() == 0)
				//myAbj.PaintWinTgl(0, 999);
		}

		else if (key == GLFW_KEY_J)
		{
			myAbj.jTgl = 0;

			myAbj.stereoSwitchLR = -myAbj.stereoSwitchLR;

			cout << "myAbj.stereoSwitchLR = " << myAbj.stereoSwitchLR << endl;
		}

		else if (key == GLFW_KEY_K)
		{
			myAbj.kTgl = 0;

			myAbj.stereoSep += .05f;
			myAbj.stereoSep = glm::clamp(myAbj.stereoSep, 0.001f, 100.f);
			if (myAbj.stereoSep == .001f) myAbj.stereoSep = 0.f;

			cout << "stereoSep = " << myAbj.stereoSep << endl;
		}

		else if (key == GLFW_KEY_L)
		{
			myAbj.lTgl = 0;

			myAbj.stereoSep -= .05f;
			myAbj.stereoSep = glm::clamp(myAbj.stereoSep, 0.001f, 100.f);
			if (myAbj.stereoSep == .001f) myAbj.stereoSep = 0.f;

			cout << "stereoSep = " << myAbj.stereoSep << endl;
		}

		else if (key == GLFW_KEY_M)
		{
			glfwRestoreWindow(myAbj.GLFWwin);
			glfwFocusWindow(myAbj.GLFWwin);

			cout << "released M" << endl;

			myAbj.mTgl = 0;
		}

		else if (key == GLFW_KEY_N)
		{
			//cout << "released N" << endl;
			myAbj.nTgl = 0;
		}

		else if (key == GLFW_KEY_O)
		{
			myAbj.oTgl = 0;
		}

		else if (key == GLFW_KEY_P)
		{
			myAbj.pTgl = 0;

			//if (!myAbj.ctrlTgl)
			//{
			//	if (myAbj.paintMode)
			//	{
			//		clearCursor(myAbj.paintMode);
			//		myAbj.paintMode = 0;
			//		clearCanvas();
			//	}

			//	else
			//	{
			//		myAbj.paintMode = 1;
			//	}
			//}

			for (auto &i : myAbj.allObj)
			{
				if (i->selected)
				{
					cout << "sel name : " << i->name->val_s << endl;
					cout << "sel T : " << glm::to_string(glm::vec3(i->tx->val_f, i->ty->val_f, i->tz->val_f)) << endl;
					cout << endl;
				}
			}
		}

		else if (key == GLFW_KEY_Q)
		{
			myAbj.qTgl = 0;

			myAbj.myGizNull->v->val_b = 0;
			myAbj.myGizNull->parentTo = 0;

			clearCursor(myAbj.paintMode);

			if (myAbj.paintMode == 1)
			{
				myAbj.paintMode = 0;
				clearCanvas();
			}

			//setcursor(arrowCursor);
		}

		else if (key == GLFW_KEY_R)
		{
			myAbj.rTgl = 0;
			gizShow("S");
		}

		else if (key == GLFW_KEY_S) myAbj.sTgl = 0;
		else if (key == GLFW_KEY_T) myAbj.tTgl = 0;
		else if (key == GLFW_KEY_U) myAbj.uTgl = 0;
		else if (key == GLFW_KEY_V) myAbj.vTgl = 0;

		else if (key == GLFW_KEY_W)
		{
			myAbj.wTgl = 0;
			gizShow("T");
		}

		else if (key == GLFW_KEY_X)
		{
			myAbj.debugX = !myAbj.debugX;
			myAbj.xTgl = 0;
		}

		else if (key == GLFW_KEY_Y) myAbj.yTgl = 0;
		//else if (key == GLFW_KEY_Z) myAbj.zTgl = 0;
		else if (key == GLFW_KEY_Z) myAbj.zTgl = !myAbj.zTgl;
	}
}

void mouseButtonCallback(GLFWwindow *myWin, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			myAbj.lmbTgl = 1; myAbj.mmbTgl = 0; myAbj.rmbTgl = 0;

			if (!myAbj.altTgl)
			{
				myAbj.rayP = myAbj.pMouseNew; //

				if (myAbj.paintMode)
					myAbj.disableSelRect = 1;

				else
					myAbj.disableSelRect = 0;
			}

			if (!myAbj.selRectPts_color.empty())
				myAbj.selRectPts_color.clear();
		}

		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			myAbj.lmbTgl = 0; myAbj.mmbTgl = 1; myAbj.rmbTgl = 0;

			if (!myAbj.altTgl)
				myAbj.gizTransType = myAbj.myGizmo->hover();

			clearCursor(myAbj.paintMode);
		}

		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			myAbj.lmbTgl = 0; myAbj.mmbTgl = 0; myAbj.rmbTgl = 1;

			//if (!myAbj.altTgl && !myAbj.ctrlTgl && myAbj.shiftTgl)
				//radPop_GL("addObj");

			//if (!myAbj.altTgl && !myAbj.ctrlTgl && !myAbj.shiftTgl)
				//radPop_GL("viewChange");

			clearCursor(myAbj.paintMode);
		}
	}

	else if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			myAbj.lmbTgl = 0;

			if (!myAbj.altTgl && !myAbj.paintMode) //SELOBJ RAYCAST
			{
				getPtsBetweenRect();
				myAbj.singleShotRC = 0;

				if (myAbj.selRectPts_color.empty())
				{
					myAbj.singleShotRC = 1;
					myAbj.selRectPts_color.push_back(myAbj.rayP);
				}

				if (!myAbj.ctrlTgl && !myAbj.shiftTgl)
					clearSel(); //

				if (!checkForHits()) // !!!!!
				{
					//cout << "no hits" << endl;
					myAbj.myGizNull->v->val_b = 0;
				}
			}

			else if (!myAbj.altTgl && myAbj.paintMode && myAbj.penOrientation == "ERASER")
			{
				myAbj.firstPress = 1;
			}

			else if (!myAbj.altTgl && myAbj.paintMode && myAbj.penOrientation == "PEN")
			{
				//CLEAR BG1
				glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushBGN.fbo0);
				glViewport(0, 0, myAbj.brushBGN.width, myAbj.brushBGN.height);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//COPY PAINT DRAG TO BG2
				glDisable(GL_BLEND);
				glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushBGN.fbo1);
				glViewport(0, 0, myAbj.brushBGN.width, myAbj.brushBGN.height);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glUseProgram2("pCopyTex");

				myAbj.copyTgt = 5; //brushN2
				myAbj.myFSQ->render();

	            //cout << "resetting debug paint settings 0" << endl;
				myAbj.firstPress = 1;
			}
		}

		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			myAbj.mmbTgl = 0;
			myAbj.gizTransType = "NONE";
		}

		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			myAbj.rmbTgl = 0;
		}

		//setting cursor for paint / normal again to make sure...
		//	if (paintMode)
		//		setCursor(Qt::BlankCursor);

		//	else
		//		setCursor(Qt::ArrowCursor);
	}
}

void scrollCallback(GLFWwindow *myWin, double wheelX, double wheelY)
{
	glm::vec2 myMouseWheel = glm::vec2(wheelX, wheelY);

	float wheelDiff = float(wheelY);
	//myAbj.selCamLi->distO = glm::max(.01f, myAbj.selCamLi->distO - wheelDiff * myAbj.dollySpeed_wheel); //no flip

	if (myAbj.selCamLi->camLiTypeGet("dirOrtho"))
	{
		//myAbj.selCamLi->orthoZoom->val_f = glm::max(.001f, myAbj.selCamLi->orthoZoom->val_f - wheelDiff * myAbj.dollySpeed_wheel); //no flip

		//PMupOrtho(myAbj.selCamLi);

		cout << "ortho zooming disabled because it doesnt go far enough (not inf)" << endl;
	}

	else
	{
		myAbj.selCamLi->distO = glm::max(.01f, myAbj.selCamLi->distO - wheelDiff * myAbj.dollySpeed_wheel); //no flip
	}

	myAbj.selCamLi->setDirty();
}

void cursorPosCallback(GLFWwindow *myWin, double xPos, double yPos)
{
	//dont have LMB + MMB at the same time;
	myAbj.pMouseOld = myAbj.pMouseNew;
	myAbj.pMouseNew = glm::vec2(xPos, yPos);
	myAbj.pMouseDiff = myAbj.pMouseNew - myAbj.pMouseOld;

	//cout << "xyPos = " << glm::to_string(glm::vec2(xPos, yPos)) << endl;
	//cout << "pMouseOld = " << glm::to_string(myAbj.pMouseOld) << endl;
	//cout << "pMouseNew = " << glm::to_string(myAbj.pMouseNew) << endl; //////
	//cout << "pMouseDiff = " << glm::to_string(myAbj.pMouseDiff) << endl;
	//cout << endl;

	float clipSpaceX = myAbj.pMouseNew.x / myAbj.width;
	float clipSpaceY = myAbj.pMouseNew.y / myAbj.height;

	float viewSpaceX = clipSpaceX * 2.f - 1.f;
	float viewSpaceY = -(clipSpaceY * 2.f - 1.f);

	//cout << "myAbj.pMouseNew = " << glm::to_string(myAbj.pMouseNew) << endl;
	//cout << "clipSpaceX = " << clipSpaceX << endl;
	//cout << "viewSpaceX = " << viewSpaceX << endl;

	glm::vec2 viewSpacePt(viewSpaceX, viewSpaceY); //0 - 1

	//cout << "myAbj.gizTransType = " << myAbj.gizTransType << endl;

	myAbj.showHideTaskbar = (viewSpacePt.y > .95f) ? 1 : 0; // test taskbar dropdown for desktop overlay
	//myAbj.showHideTaskbar = (viewSpacePt.y == 1) ? 1 : 0; // test taskbar dropdown for desktop overlay
	
	//cout << "viewSpacePt = " << glm::to_string(viewSpacePt) << " : " << myAbj.showHideTaskbar << endl;


	if (myAbj.ctrlTgl && myAbj.shiftTgl) //move window XY - CODEX
	{
		int posHalfL = myAbj.width / 2;
		int posHalfU = myAbj.height / 2;

		myAbj.winPosGlobal = glm::ivec2((myAbj.winPosGlobal.x + (int)xPos) - posHalfL, (myAbj.winPosGlobal.y + (int)yPos) - posHalfU);
		glfwSetWindowPos(myAbj.GLFWwin, myAbj.winPosGlobal.x, myAbj.winPosGlobal.y);
	}

	if (myAbj.myGizNull->parentTo)
	{
		//cout << "myAbj.myGizNull->parentTo->name->val_s = " << myAbj.myGizNull->parentTo->name->val_s << endl;

		if (myAbj.gizTransType == "NONE")
		{
			myAbj.gizHoverType = myAbj.myGizmo->hover();
			myAbj.myGizmo->resetSetCol(myAbj.gizHoverType);
		}

		else //dragging with MMB
		{
			myAbj.myGizmo->transform();
		}
	}

	//else
	//cout << "NO myAbj.myGizNull->parentTo" << endl;

	if (myAbj.paintMode && myAbj.paintCursorResizeTgl)
	{
		auto paintCursorScaleSpeed = .005f;
		myAbj.selBrush->scale = clamp(myAbj.selBrush->scale + myAbj.pMouseDiff.x * paintCursorScaleSpeed, glm::vec3(0.25f), glm::vec3(1.f));
	}

	if (myAbj.lmbTgl && myAbj.altTgl)
	{
		//cout << "should be rotating cam 0" << endl;

		//setCursor(Qt::SizeAllCursor);

		//if (!(myAbj.selCamLi->camLiType->val_s == "ORTHO"))
		//{
		//	cout << "debug 0" << endl;


		//	if (!myAbj.selCamLi->orthoFree->val_b)
		//	{
		//		cout << "debug 1" << endl;
		//	}

		//}

		if (!(myAbj.selCamLi->camLiType->val_s == "ORTHO" && myAbj.selCamLi->orthoFree->val_b == 0))
		{
			myAbj.selCamLi->r->val_3.x -= myAbj.tumbleSpeed * myAbj.pMouseDiff.x;
			myAbj.selCamLi->r->val_3.y = glm::clamp(myAbj.selCamLi->r->val_3.y - myAbj.tumbleSpeed * myAbj.pMouseDiff.y, -89.99f, 89.99f); //no flip

			//cout << "should be rotating cam 1 to : " << glm::to_string(myAbj.selCamLi->r->val_3) << endl;

		}

		myAbj.selCamLi->setDirty();
	}

	else if (myAbj.mmbTgl && myAbj.altTgl) //pan
	{
		//setCursor(Qt::ClosedHandCursor);

		if (myAbj.selCamLi->camLiTypeGet("dirOrtho"))
		{
			//myAbj.selCamLi->targO -= myAbj.selCamLi->rightO * (float)myAbj.pMouseDiff.x * myAbj.panSpeed_ortho;
			//myAbj.selCamLi->targO += myAbj.selCamLi->upO * (float)myAbj.pMouseDiff.y * myAbj.panSpeed_ortho;

			glm::vec3 panOrtho0 = myAbj.selCamLi->rightO * (float)myAbj.pMouseDiff.x * myAbj.panSpeed;
			glm::vec3 panOrtho1 = myAbj.selCamLi->upO * (float)myAbj.pMouseDiff.y * myAbj.panSpeed;

			//cout << "stock right0 / up0 = " << glm::to_string(myAbj.selCamLi->rightO) << " " << glm::to_string(myAbj.selCamLi->upO) << endl;
			cout << "panOrtho0 = " << glm::to_string(panOrtho0) << endl;
			cout << "panOrtho1 = " << glm::to_string(panOrtho1) << endl;

			myAbj.selCamLi->targO -= myAbj.selCamLi->rightO * (float)myAbj.pMouseDiff.x * myAbj.panSpeed;
			myAbj.selCamLi->targO += myAbj.selCamLi->upO * (float)myAbj.pMouseDiff.y * myAbj.panSpeed;

			//myAbj.selCamLi->tx->val_f -= (float)myAbj.pMouseDiff.x * myAbj.panSpeed;
			//myAbj.selCamLi->ty->val_f -= (float)myAbj.pMouseDiff.y * myAbj.panSpeed;

			cout << "myAbj.selCamLi->targO = " << glm::to_string(myAbj.selCamLi->targO) << endl;
			cout << endl;
		}

		else
		{
			myAbj.selCamLi->targO -= myAbj.selCamLi->rightO * (float)myAbj.pMouseDiff.x * myAbj.panSpeed;
			myAbj.selCamLi->targO += myAbj.selCamLi->upO * (float)myAbj.pMouseDiff.y * myAbj.panSpeed;

			//cout << "myAbj.selCamLi->targO = " << glm::to_string(myAbj.selCamLi->targO) << endl;
		}

		myAbj.selCamLi->setDirty();
	}

	else if (myAbj.rmbTgl && myAbj.altTgl) //zoom
	{
		//cout << "zooming \n" << endl;

		//setCursor(Qt::SizeVerCursor);

		//if (myAbj.selCamLi->camLiTypeGet("dirOrtho"))
		//{
		//	myAbj.selCamLi->orthoZoom->val_f = glm::max(.001f, myAbj.selCamLi->orthoZoom->val_f - myAbj.pMouseDiff.x * myAbj.dollySpeed_ortho); //no flip

		//PMupOrtho(myAbj.selCamLi);

		//}

		//else
		{
			myAbj.selCamLi->distO = glm::max(.01f, myAbj.selCamLi->distO - myAbj.pMouseDiff.x * myAbj.dollySpeed); //no flip
			//cout << "myAbj.selCamLi->distO = " << myAbj.selCamLi->distO << endl;
		}

		myAbj.selCamLi->setDirty();
	}
}

bool checkForHits()
{
	myAbj.colorPickTgl = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram2("pColorID"); //gets Crand

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "CAMLI" || i->type == "OBJ")
		{
			if (!i->anim->val_b && i->v->val_b)
			{
				i->mvpGet();
				i->render();
			}
		}
	}

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "CAMLI" || i->type == "OBJ")
		{
			if (i->anim->val_b) //if animated and BB or not
			{
				if (i->bb->val_b)
				{
					
					//for (auto &j : i->bbSkelAll)
					//{
					//	for (auto &k : i->animBones)
					//	{
					//		if (k.name == j.name)
					//		{
					//			//cout << "match for bone transform...k / bbSkel = " << k.name << " " << myAbj.bbSkelAll[j].name << endl;

					//			i->obbMVP = glm::transpose(k.animatedXform) * j.obbMVP; // !!!!!!!!

					//			break;
					//		}
					//	}

					//	i->mvpGet();
					//	i->render();
					//}
				}
			}
		}
	}

	glUseProgram2("pColorIDAnim"); //gets Crand

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "CAMLI" || i->type == "OBJ")
		{
			if (i->anim->val_b) //if animated and BB or not
			{
				if (!i->bb->val_b)
				{
					//use the pColorIDAnim shader and upload aiGBone

					i->mvpGet();
					i->render();
				}
			}
		}
	}

	glDisable(GL_DEPTH_TEST);

	glFlush();
	glFinish();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	bool foundNonOBJ = 0;

	for (auto it = myAbj.selRectPts_color.begin(); it != myAbj.selRectPts_color.end(); )
	{
		unsigned char data[4];
		glReadPixels(int((*it).x), myAbj.height - int((*it).y), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

		int pickedID = data[0] + data[1] * 256 + data[2] * 256 * 256;

		if (pickedID != 0x00ffffff)
		{
			int r = (pickedID & 0x000000FF) >> 0;
			int g = (pickedID & 0x0000FF00) >> 8;
			int b = (pickedID & 0x00FF0000) >> 16;

			glm::vec3 compareID(r / 255.f, g / 255.f, b / 255.f);

			for (auto &i : myAbj.frustumObjs)
			{
				if (i->Crand == compareID)
				{
					if (i->selectable)
					{
						matchFoundRaycast(i);
						foundNonOBJ = 1;
					}
				}
			}
		}

		if (myAbj.singleShotRC)
			++it;

		else
		{
			size_t it_curr = it - myAbj.selRectPts_color.begin();
			size_t it_end = myAbj.selRectPts_color.size();

			if (it_curr + myAbj.selAccuracy <= it_end)
				advance(it, myAbj.selAccuracy);

			else
				++it;
		}
	}

	/* CLEANUP */
	glEnable(GL_DEPTH_TEST);
	myAbj.colorPickTgl = 0;
	//gizPivAutoShow(); //

	return foundNonOBJ;
}

void matchFoundRaycast(shared_ptr<Object> obj)
{
	if (myAbj.ctrlTgl)
	{
		if (obj->selected == 0)
		{
			obj->selected = 1;
		}

		if (obj->selected)
		{
			// deselect and move giz to other obj
			obj->selected = 0;

			for (auto &i : myAbj.allObj)
			{
				if (i->selected)
					myAbj.selB = i;
			}

			if (myAbj.myGizNull->v->val_b == 1)
			{
				string gizTypeShowing = myAbj.myGizNull->gizType;
				gizShow(gizTypeShowing);
			}
		}
	}

	if (!myAbj.ctrlTgl)
	{
		auto type = obj->type;

		obj->selected = 1;
		myAbj.selB = obj;

		//if gizmo is visible, move it to the currently selected obj
		//if (myAbj.myGizNull->v->val_b)
		if (myAbj.myGizNull->v->val_b == 1)
		{
			string gizTypeShowing = myAbj.myGizNull->gizType;
			gizShow(gizTypeShowing);
		}

		if (type == "GIZ_CIRC" || type == "GIZ_CONE" || type == "GIZ_CUBE" || type == "GIZ_DUAL_HANDLE" || type == "GIZ_LINE")
			obj->parentTo->parentTo->selected = 1; //keep obj selected w/ manips
	}
}

//void matchFoundRaycast(shared_ptr<Object> obj)
//{
//	if (obj->selected && myAbj.ctrlTgl)
//	{
//		// deselect and move giz to other obj
//		obj->selected = 0;
//
//		for (auto &i : myAbj.allObj)
//		{
//			if (i->selected)
//				myAbj.selB = i;
//		}
//
//		if (myAbj.myGizNull->v->val_b == 1)
//		{
//			string gizTypeShowing = myAbj.myGizNull->gizType;
//			gizShow(gizTypeShowing);
//		}
//	}
//
//	if (!myAbj.ctrlTgl)
//	{
//		auto type = obj->type;
//
//		obj->selected = 1;
//		myAbj.selB = obj;
//
//		//if gizmo is visible, move it to the currently selected obj
//		//if (myAbj.myGizNull->v->val_b)
//		if (myAbj.myGizNull->v->val_b == 1)
//		{
//			string gizTypeShowing = myAbj.myGizNull->gizType;
//			gizShow(gizTypeShowing);
//		}
//
//		if (type == "GIZ_CIRC" || type == "GIZ_CONE" || type == "GIZ_CUBE" || type == "GIZ_DUAL_HANDLE" || type == "GIZ_LINE")
//			obj->parentTo->parentTo->selected = 1; //keep obj selected w/ manips
//	}
//}