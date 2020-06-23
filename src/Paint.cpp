#include "Paint.h"

///////////////
// PAINT
//////////////
void paintSomething0()
{
	//cout << "in paintSomething0" << endl;

	glm::vec2 widthHeight(myAbj.width, myAbj.height);

	auto pt0 = toNDC(myAbj.pMouseOld, "SELRECT") * widthHeight; //-1..1
	auto pt1 = toNDC(myAbj.pMouseNew, "SELRECT") * widthHeight; //-1..1

	myAbj.strokes_cursor.clear();

	vector<glm::vec2> bresenham_cursor = bresenham(pt0, pt1, 500);
	auto distDrag = glm::distance(pt0, pt1);

	if (myAbj.penOrientation == "PEN") //CURSOR - BRUSH
	{
		//cout << "myAbj.lmbTgl = " << myAbj.lmbTgl << endl;

		if (myAbj.lmbTgl) //STROKE - BRUSH
		{
			if (myAbj.firstPress || distDrag > myAbj.distDragPaint)
			{
				myAbj.strokes_brush.clear();

				vector<glm::vec2> bresenham_brush = bresenham(pt0, pt1, 1);
				//vector<glm::vec2> bresenham_brush = bresenham(pt0, pt1, 10);
				//vector<glm::vec2> bresenham_brush = bresenham(pt0, pt1, 50); // !!!
				//vector<glm::vec2> bresenham_brush = bresenham(pt0, pt1, 100); //

				for (auto &i : bresenham_brush)
					myAbj.strokes_brush.push_back({ i, myAbj.selBrush->scale, myAbj.selBrush->opac });

				//cout << "myAbj.strokes_brush.size() = " << myAbj.strokes_brush.size() << endl;

				paintSomething1("BRUSH");
				myAbj.firstPress = 0;
			}
		}
	}

	else if (myAbj.penOrientation == "ERASER")
	{
		for (auto &i : bresenham_cursor)
			myAbj.strokes_cursor.push_back({ i, myAbj.selEraser->scale, myAbj.selEraser->opac });

		if (myAbj.lmbTgl) //STROKE - ERASER
		{
			if (myAbj.firstPress || distDrag > 10.f)
			{
				myAbj.strokes_eraser.clear();

				vector<glm::vec2> bresenham_eraser = bresenham(pt0, pt1, 1);
				//vector<glm::vec2> bresenham_eraser = bresenham(pt0, pt1, 2);

				for (auto &i : bresenham_eraser)
					myAbj.strokes_eraser.push_back({ i, myAbj.selEraser->scale, myAbj.selEraser->opac });

				paintSomething1("ERASER");
				myAbj.firstPress = 0;
			}
		}
	}

	if (myAbj.bakeNow && myAbj.selB)
	{
		bakeSomething();

		if (myAbj.myFSQ->clearBehav->val_s != "Manual")
		{
			clearCanvas();
		}
	}
}

void paintSomething1(string type)
{
	/* PAINT A STROKE */
	myAbj.paintType = type;

	if (type == "BRUSH")
	{
		//myAbj.brushRGB = glm::vec3(1.f);
		myAbj.brushRGB = glm::vec3(0.f, 0.f, 1.f);
		myAbj.brushA = myAbj.selBrush->opac;
		myAbj.brushRGBA = glm::vec4(myAbj.brushRGB * glm::vec3(myAbj.brushA), myAbj.brushA);

		//***************************** STROKE *******************************
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushTempN.fbo0);
		glViewport(0, 0, myAbj.brushTempN.width, myAbj.brushTempN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pPaintStroke");

		for (auto &i : myAbj.strokes_brush)
		{
			myAbj.paintStroke->sx->val_f = i.scale.x;// myAbj.tabletPressure;
			myAbj.paintStroke->sy->val_f = i.scale.y;// myAbj.tabletPressure;
			myAbj.paintStroke->sz->val_f = i.scale.z;// myAbj.tabletPressure;
			
			glm::vec3 tempT = glm::vec3(i.coord, 0.f);
			myAbj.paintStroke->tx->val_f = tempT.x;
			myAbj.paintStroke->ty->val_f = tempT.y;
			myAbj.paintStroke->tz->val_f = tempT.z;

			myAbj.paintStroke->mvpGet();
			myAbj.paintStroke->render();
		}

		//***************************** BLEND BG1 AND STROKE ***************
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushN.fbo0);
		glViewport(0, 0, myAbj.brushN.width, myAbj.brushN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pCopyTex");

		myAbj.copyTgt = 2; //bgN.tex1
		myAbj.myFSQ->render();

		myAbj.copyTgt = 0; //brushTempN1
		myAbj.myFSQ->render();

		//***************************** COPY TO BG1 (held stroke) **********
		glDisable(GL_BLEND);
		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushBGN.fbo0);
		glViewport(0, 0, myAbj.brushBGN.width, myAbj.brushBGN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pCopyTex");
		myAbj.copyTgt = 4; //brushN.tex1
		myAbj.myFSQ->render();

		//***************************** HARDWARE BLEND STROKE AND BG2 *******
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushN.fbo1);
		glViewport(0, 0, myAbj.brushN.width, myAbj.brushN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pCopyTex");

		myAbj.copyTgt = 3; //bgN.tex2
		myAbj.myFSQ->render();

		myAbj.copyTgt = 4; //brushN1
		myAbj.myFSQ->render();
	}

	else if (type == "ERASER")
	{
		myAbj.brushRGBA = glm::vec4(1.f);

		//***************************** STROKE *******************************
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.eraserN.fbo0);
		glViewport(0, 0, myAbj.eraserN.width, myAbj.eraserN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pPaintStroke");

		for (auto &i : myAbj.strokes_eraser)
		{
			myAbj.paintStroke->sx->val_f = i.scale.x;// myAbj.tabletPressure;
			myAbj.paintStroke->sy->val_f = i.scale.y;// myAbj.tabletPressure;
			myAbj.paintStroke->sz->val_f = i.scale.z;// myAbj.tabletPressure;

			glm::vec3 tempT = glm::vec3(i.coord, 0.f);
			myAbj.paintStroke->tx->val_f = tempT.x;
			myAbj.paintStroke->ty->val_f = tempT.y;
			myAbj.paintStroke->tz->val_f = tempT.z;

			myAbj.paintStroke->mvpGet();
			myAbj.paintStroke->render();
		}

		//ERASE
		glDisable(GL_BLEND);

		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.eraserN.fbo1);
		glViewport(0, 0, myAbj.eraserN.width, myAbj.eraserN.height);

		glUseProgram2("pEraseMix");
		myAbj.myFSQ->render();

		//COPY TO BG2
		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushBGN.fbo1);
		glViewport(0, 0, myAbj.brushBGN.width, myAbj.brushBGN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pCopyTex");

		myAbj.copyTgt = 12; //eraserN.tex2
		myAbj.myFSQ->render();

		//COPY TO BRUSHN2
		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushN.fbo1);
		glViewport(0, 0, myAbj.brushN.width, myAbj.brushN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pCopyTex");

		myAbj.copyTgt = 12; //eraserN.tex2
		myAbj.myFSQ->render();
	}
}

void brushOutlineUp()
{
	//edge detect ALL brushes
	//upload sobel silh into brush.FBO1

	//take the alpha of a brush (always solid white) INTO ITS OWN TEXTURE !!!! - brushTemp1
	//gaussian blur THE ALPHA CHANNEL - alphaGauss2
	//sobel the blurred tex

	for (auto &i : myAbj.allTexMaps)
	{
		if (i.type == "BRUSH")
		{
			myAbj.sobelMap = i;

			//ALPHA INTO ITS OWN CHANNEL
			glBindFramebuffer(GL_FRAMEBUFFER, myAbj.brushTempN.fbo0);
			glViewport(0, 0, myAbj.brushTempN.width, myAbj.brushTempN.height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram2("pAlphaAsRGBA");
			myAbj.myFSQ->render();

			//GAUSSIAN BLUR
			glMakeTextureHandleNonResidentARB(myAbj.alphaGaussN.tex1_64);
			glUseProgram2("pGauss");
			//myAbj.alphaGaussN.tex1_64 = glGetTextureHandleARB(gaussianBlur2(myAbj.brushTempN.tex0_32, myAbj.alphaGaussN, 0));
			//myAbj.alphaGaussN.tex1_64 = glGetTextureHandleARB(gaussianBlur2(myAbj.brushTempN.tex0_32, myAbj.alphaGaussN, 1)); //
			myAbj.alphaGaussN.tex1_64 = glGetTextureHandleARB(gaussianBlur2(myAbj.brushTempN.tex0_32, myAbj.alphaGaussN, 4));
			glMakeTextureHandleResidentARB(myAbj.alphaGaussN.tex1_64);

			//EDGE DETECT
			glBindFramebuffer(GL_FRAMEBUFFER, i.layer[0].fbo1);
			glViewport(0, 0, i.layer[0].width, i.layer[0].height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//cout << "brush name = " << i.name << endl;
			//cout << "myAbj.brushTempN.width = " << myAbj.brushTempN.width << endl;
			//cout << "i.layer[0].width = " << i.layer[0].width << endl;
			//cout << "i.layer[0].height = " << i.layer[0].height << endl;
			//cout << endl;

			glUseProgram2("pEdgeDetect");
			//myAbj.edgeDetect_mode = 0; // sobel
			myAbj.edgeDetect_mode = 1; // freiChen
			myAbj.myFSQ->render();
		}
	}

	myAbj.brushOutlineUpB = 0;
}

void clearCursor(bool inPaintMode)
{
	if (inPaintMode) // don't clear if not in paint mode
	{
		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.cursorN.fbo0);
		glViewport(0, 0, myAbj.cursorN.width, myAbj.cursorN.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void clearCanvas()
{
	GLint resetCol[] = { 0, 0, 0, 0 };

	glClearNamedFramebufferiv(myAbj.brushN.fbo1, GL_COLOR, 0, resetCol);
	glClearNamedFramebufferiv(myAbj.brushBGN.fbo0, GL_COLOR, 0, resetCol);
	glClearNamedFramebufferiv(myAbj.brushBGN.fbo1, GL_COLOR, 0, resetCol);
}

TexMap getCurrPaintLayer()
{
	for (auto &i : myAbj.allTexMaps)
	{
		//match the type
		if (myAbj.selB->texSel.type == i.type)
		{
			auto myType = myAbj.selB->texSel.type;
			string myTypeVal;

			if (myType == "ALBEDO") myTypeVal = myAbj.selB->albedoM->val_s;
			else if (myType == "ALPHA") myTypeVal = myAbj.selB->alphaM->val_s;
			else if (myType == "ANISO") myTypeVal = myAbj.selB->anisoM->val_s;
			else if (myType == "LENS") myTypeVal = myAbj.selB->lensM->val_s;
			else if (myType == "METALLIC") myTypeVal = myAbj.selB->metallicM->val_s;
			else if (myType == "RUFF") myTypeVal = myAbj.selB->ruffM->val_s;

			if (i.name == myTypeVal)
				return i;
		}
	}

	return { "", "", "", 0 };
}

void bakeSomething()
{
	setRenderParams_GLApi("back");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //

	myAbj.myLayerIdx = getCurrPaintLayer(); //get correct selLayer

	//1 - write current FBO0.selLayer to copyTex
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.myLayerIdx.layer[0].fbo1);
	glViewport(0, 0, myAbj.myLayerIdx.layer[0].width, myAbj.myLayerIdx.layer[0].height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram2("pCopyTex");
	myAbj.copyTgt = 10;
	myAbj.myFSQ->render();

	//2
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.myLayerIdx.layer[0].fbo0);
	glViewport(0, 0, myAbj.myLayerIdx.layer[0].width, myAbj.myLayerIdx.layer[0].height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram2("pPaintProj");

	if (!myAbj.selB->bb->val_b && searchUp(myAbj.selB))
		myAbj.selB->render();

	//3 - REGEN MIPS
	glGenerateTextureMipmap(myAbj.myLayerIdx.layer[0].tex0_32);

	myAbj.bakeNow = 0;
}

vector<glm::vec2> bresenham(glm::ivec2 pt0, glm::ivec2 pt1, int incr)
{
	vector<glm::vec2> myV;
	glm::vec2 widthHeight(myAbj.width, myAbj.height);

	bool steep = (fabs(pt1.y - pt0.y) > fabs(pt1.x - pt0.x));

	if (steep)
	{
		swap(pt0.x, pt0.y);
		swap(pt1.x, pt1.y);
	}

	if (pt0.x > pt1.x)
	{
		swap(pt0.x, pt1.x);
		swap(pt0.y, pt1.y);
	}

	auto dx = pt1.x - pt0.x;
	auto dy = fabs(pt1.y - pt0.y);
	auto error = dx / 2.f;

	auto ystep = ((int)pt0.y < (int)pt1.y) ? incr : -incr;
	int y = (int)pt0.y;
	//    int maxX = (int)pt1.x;
	int maxX = (int)pt1.x + 1;

	for (int x = (int)pt0.x; x < maxX; x += incr)
	{
		if (steep)
			myV.push_back(glm::vec2(y, x) / widthHeight);

		else
			myV.push_back(glm::vec2(x, y) / widthHeight);

		error -= (float)dy;

		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}

	return myV; // CONSIDER DIVIDING BY WIDTH_HEIGHT HERE
}




