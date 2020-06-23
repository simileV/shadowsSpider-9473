#include "pch.h"
#include "Setup_obj.h"

void gridInit()
{
	GridSetup myGridSetup[] =
	{
		{ "grid_front", { 0.f, 0.f, 0.f } },
		{ "grid_frontB", { 0.f, 0.f, 90.f } }, //

		{ "grid_left", { 0.f, 90.f, 0.f } },
		{ "grid_leftB", { 90.f, 90.f, 0.f } },

		{ "grid_top", { 90.f, 0.f, 0.f } },
		{ "grid_topB", { 0.f, 90.f, 90.f } }, //ok
	};

	for (auto &i : myGridSetup)
	{
		myAbj.createNonFBX = nonFBX_VBOup("GRID", i.name, 0); //
		myAbj.createNonFBX->deletable = 0;
		myAbj.createNonFBX->selectable = 0;
		myAbj.createNonFBX->ignoreOutliner = 1;
		myAbj.createNonFBX->r->val_3 = i.r;
		myAbj.createNonFBX->sx->val_f = 100;
		myAbj.createNonFBX->sy->val_f = 100;
		myAbj.createNonFBX->sz->val_f = 100;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allGrid.push_back(myAbj.createNonFBX);
	}
}

void camInit()
{
	gridInit();

	CamSetup myCamSetup[] =
	{
		//{ "ORTHO", "back", { 0.f, 0.f, -5.f } },
		//{ "ORTHO", "bottom", { 0.f, -5.f, .002f } }, //
		
		//{ "ORTHO", "front", { 0.f, 0.f, 5.f } },
		{ "ORTHO", "front",{ -1.f, 0.f, 5.f } }, //////////////

		//{ "ORTHO", "left", { 5.f, 0.f, 0.f } },
		//{ "ORTHO", "right", { -5.f, 0.f, 0.f } },
		//{ "ORTHO", "top", { 0.f, 5.f, .002f } }, //

		//{ "PERSP", "persp", { 0.f, 10.f, 10.f } }, //// !!!
		//{ "PERSP", "persp", { 10.f, 10.f, 10.f } }, //// !!!
		{ "PERSP", "persp", { 20.f, 20.f, 20.f } }, //// !!!


		//{ "THIRD", "third", { 20.f, 20.f, 20.f } }, /// !!!!! 
	};

	for (auto &i : myCamSetup)
	{
		myAbj.createNonFBX = nonFBX_VBOup(i.type, i.name, 0);
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		myAbj.createNonFBX->tx->val_f = i.t.x;
		myAbj.createNonFBX->ty->val_f = i.t.y;
		myAbj.createNonFBX->tz->val_f = i.t.z;

		//myAbj.createNonFBX->r->val_3 = glm::vec3(0.f, -15.f, 0.f);
		myAbj.createNonFBX->piv->val_3 = glm::vec3(myAbj.createNonFBX->tx->val_f, myAbj.createNonFBX->ty->val_f, myAbj.createNonFBX->tz->val_f);


		if (i.type == "ORTHO") //sets in nonFBX_VBOup()
		{
			//myAbj.createNonFBX->targO = glm::vec3(3.f, 0.f, 0.f);
			//myAbj.createNonFBX->targO = glm::vec3(-7.f, 0.f, 0.f);

			//myAbj.createNonFBX->nearClip->val_f = 0.f;
			myAbj.createNonFBX->nearClip->val_f = -10000.f;
			myAbj.createNonFBX->farClip->val_f = 10000.f;
			
			//myAbj.createNonFBX->orthoZoom->val_f = 2.f;
			myAbj.createNonFBX->orthoZoom->val_f = 20.f;

			myAbj.createNonFBX->orthoType->val_s = stringToUpper(i.name);
			myAbj.createNonFBX->ignoreOutliner = 1;
			myAbj.createNonFBX->deletable = 0;
			myAbj.createNonFBX->ref = 1;
		}

		//cout << "name / myAbj.createNonFBX->targO = " << i.name << " myAbj.createNonFBX->targO " << endl;

		//myAbj.createNonFBX->setTarg(myAbj.createNonFBX->targO, 0.f); //
		
		myAbj.createNonFBX->targO = glm::vec3(0.f);

		myAbj.createNonFBX->distO = glm::distance(glm::vec3(myAbj.createNonFBX->tx->val_f, myAbj.createNonFBX->ty->val_f, myAbj.createNonFBX->tz->val_f), myAbj.createNonFBX->targO);
		//myAbj.createNonFBX->setDirty();

		PMupOrtho(myAbj.createNonFBX);

		myAbj.createNonFBX->v->val_b = (myAbj.createNonFBX->camLiType->val_s != "ORTHO") ? 1 : 0;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);
	}
}

void gizInit()
{
	myAbj.createNonFBX = nonFBX_VBOup("GIZ", "giz", 0);
	myAbj.createNonFBX->v->val_b = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->selectable = 0;
	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.myGizNull = myAbj.createNonFBX; // parent to this

	float dualP = .5f; // dual axis handle P

	GizSetup myGizSetup[] =
	{
		{ "GIZ_CIRC", "gizCirc", { .2f, .2f, .2f } },
		{ "GIZ_CIRC_HALF", "gizCircHalfX", { 1.f, 0.f, 0.f } },
		{ "GIZ_CIRC_HALF", "gizCircHalfY", { 0.f, 1.f, 0.f } },
		{ "GIZ_CIRC_HALF", "gizCircHalfZ", { 0.f, 0.f, 1.f } },

		{ "GIZ_CONE", "gizConeX", { 1.f, 0.f, 0.f } },
		{ "GIZ_CONE", "gizConeY", { 0.f, 1.f, 0.f } },
		{ "GIZ_CONE", "gizConeZ", { 0.f, 0.f, 1.f } },

		{ "GIZ_CUBE", "gizCubeX", { 1.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 1.f, 0.f, 0.f } },
		{ "GIZ_CUBE", "gizCubeY", { 0.f, 1.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f } },
		{ "GIZ_CUBE", "gizCubeZ", { 0.f, 0.f, 1.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 1.f } },
		{ "GIZ_CUBE", "gizCubeXYZ", { 0.f, 0.f, 0.f } },

		{ "GIZ_DUAL_HANDLE", "gizDualXZ", { 0.f, 1.f, 0.f }, { 90.f, 0.f, 0.f }, { dualP, 0.f, dualP } },
		{ "GIZ_DUAL_HANDLE", "gizDualXY", { 0.f, 0.f, 1.f }, { 0.f, 0.f, 0.f }, { dualP, dualP, 0.f } },
		{ "GIZ_DUAL_HANDLE", "gizDualYZ", { 1.f, 0.f, 0.f }, { 0.f, 90.f, 0.f }, { 0.f, dualP, dualP } },

		{ "GIZ_LINE", "gizLineX", { 1.f, 0.f, 0.f } },
		{ "GIZ_LINE", "gizLineY", { 0.f, 1.f, 0.f } },
		{ "GIZ_LINE", "gizLineZ", { 0.f, 0.f, 1.f } },
	};

	for (auto &i : myGizSetup)
	{
		myAbj.createNonFBX = nonFBX_VBOup(i.type, i.name, 0);
		myAbj.createNonFBX->Cgiz = i.Cgiz;
		myAbj.createNonFBX->Cgiz_stored = i.Cgiz;

		if (i.type == "GIZ_CUBE") {
			myAbj.createNonFBX->sx->val_f = .15f;
			myAbj.createNonFBX->sy->val_f = .15f;
			myAbj.createNonFBX->sz->val_f = .15f;

		}

		else if (i.type == "GIZ_DUAL_HANDLE") {
			myAbj.createNonFBX->sx->val_f = .1f;
			myAbj.createNonFBX->sy->val_f = .1f;
			myAbj.createNonFBX->sz->val_f = .1f;
		}

		myAbj.createNonFBX->r->val_3 = i.r;
		myAbj.createNonFBX->piv->val_3 = i.t;
		myAbj.createNonFBX->deletable = 0;
		myAbj.createNonFBX->tx->val_f = i.t.x;
		myAbj.createNonFBX->ty->val_f = i.t.y;
		myAbj.createNonFBX->tz->val_f = i.t.z;

		myAbj.createNonFBX->selectable = 0;
		myAbj.createNonFBX->ignoreOutliner = 1;
		myAbj.createNonFBX->parentObj("giz"); 
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allGiz.push_back(myAbj.createNonFBX);
	}

	GizSetup myGizSetupSide[] =
	{
		{ "GIZ_LINE", "gizLineXSide", { 1.f, 0.f, 0.f } },
		{ "GIZ_LINE", "gizLineYSide", { 0.f, 1.f, 0.f } },
		{ "GIZ_LINE", "gizLineZSide", { 0.f, 0.f, 1.f } },
	};

	for (auto &i : myGizSetupSide)
	{
		myAbj.createNonFBX = nonFBX_VBOup(i.type, i.name, 0);
		myAbj.createNonFBX->Cgiz = i.Cgiz;
		myAbj.createNonFBX->Cgiz_stored = i.Cgiz;
		myAbj.createNonFBX->deletable = 0;
		myAbj.createNonFBX->selectable = 0;
		myAbj.createNonFBX->ignoreOutliner = 1;
		myAbj.createNonFBX->gizSideObj = 1;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allGizSide.push_back(myAbj.createNonFBX);
	}
}

void objInit()
{
	myAbj.createNonFBX = nonFBX_VBOup("BB", "bb", 0);
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->selectable = 0;
	myAbj.createNonFBX->v->val_b = 0;
	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.myBB = myAbj.createNonFBX;

	myAbj.createNonFBX = nonFBX_VBOup("FBO", "fsq", 0);
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->selectable = 0;

	for (auto &j : myAbj.allTexMaps)
	{
		if (j.name == "ENNIS_CUBEIRRAD")
			myAbj.cubeM_irradiance_32 = j.layer[0].tex0_32;

		else if (j.name == "ENNIS_CUBESPEC")
			myAbj.cubeM_specular_32 = j.layer[0].tex0_32;

		myAbj.createNonFBX->cubeM->val_s = j.name;
	}

	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.myFSQ = myAbj.createNonFBX;
	myAbj.myFSQ->vign->val_b = 0;

	myAbj.createNonFBX = nonFBX_VBOup("FBO", "paintStroke", 0);
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->selectable = 0;
	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.paintStroke = myAbj.createNonFBX;

	myAbj.createNonFBX = nonFBX_VBOup("SELRECT", "selRect", 0);
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->selectable = 0;
	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.mySelRect = myAbj.createNonFBX;

	myAbj.createNonFBX = nonFBX_VBOup("TXT", "txt", 0);
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->selectable = 0;
	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.myTxt = myAbj.createNonFBX;

	myAbj.createNonFBX = nonFBX_VBOup("GIZ_CUBE", "pivot", 0);
	myAbj.createNonFBX->v->val_b = 0;
	myAbj.createNonFBX->sx->val_f = .3f;
	myAbj.createNonFBX->sy->val_f = .3f;
	myAbj.createNonFBX->sz->val_f = .3f;
	myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 1.f, 0.f);
	myAbj.createNonFBX->deletable = 0;
	myAbj.createNonFBX->ignoreOutliner = 1;
	myAbj.createNonFBX->selectable = 0;
	myAbj.allObj.push_back(myAbj.createNonFBX);
	myAbj.myPivot = myAbj.createNonFBX;
}

shared_ptr<Object> nonFBX_VBOup(string type, string name, shared_ptr<Object> dupe)
{
	if (!myAbj.newObj.empty())
		myAbj.newObj.clear();

	auto obj = (dupe == 0) ? make_shared<Object>() : dupe;
	obj->rename(name);

	if (type == "DIR" || type == "ORTHO" || type == "PERSP" || type == "THIRD" || type == "POINT" || type == "SPOT")
	{
		obj->type = "CAMLI";
		obj->camLiType->val_s = type;    
		obj->rotOrder->val_s = "YZX";
	}

	else
		obj->type = type;

	if (obj->type == "BB")
	{
		glm::vec3 bbV[] =
		{
			// fbl, fbr,  ftr, ftl
			// nbl, nbr, ntr, ntl
			{ -.5f, -.5f, -.5f }, { .5f, -.5f, -.5f },{ .5f,  .5f, -.5f },{ -.5f,  .5f, -.5f },
			{ -.5f, -.5f,  .5f }, { .5f, -.5f,  .5f },{ .5f,  .5f,  .5f },{ -.5f,  .5f,  .5f },
		};

		for (auto &i : bbV)
			obj->pE.push_back(i);

		GLushort bbI[] =
		{
			0, 1, 2, 3,
			4, 5, 6, 7,
			0, 4, 1, 5,
			2, 6, 3, 7
		};

		for (auto &i : bbI)
		{
			obj->idxE.push_back(i);
			obj->idxBBE.push_back(i); //
		}
	}

	else if (obj->type == "CAMLI")
	{
		if (obj->camLiTypeGet("cam"))
		{
			auto sX = 1.f;
			auto sY = .5f;
			auto sZ = 1.f;

			//box
			obj->pE.push_back(glm::vec3(-1.f * sX, 1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(1.f * sX, 1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(1.f * sX, -1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(-1.f * sX, -1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(-1.f * sX, 1.f * sY, 0.f));

			//cone
			obj->pE.push_back(glm::vec3(0.f, 0.f, sZ));
			obj->pE.push_back(glm::vec3(-1.f * sX, 1.f * sY, 0.f));

			obj->pE.push_back(glm::vec3(1.f * sX, 1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(0.f, 0.f, sZ));

			obj->pE.push_back(glm::vec3(1.f * sX, -1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(0.f, 0.f, sZ));

			obj->pE.push_back(glm::vec3(-1.f * sX, -1.f * sY, 0.f));
			obj->pE.push_back(glm::vec3(0.f, 0.f, sZ));
		}

		else if (obj->camLiType->val_s == "DIR")
		{
			//LR
			lightArrowAdd(obj, -.25f, 0.f, 0.f, "vert");
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));

			lightArrowAdd(obj, .25f, 0.f, 0.f, "vert");
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));

			//UD
			lightArrowAdd(obj, 0.f, .25f, 0.f, "horiz");
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));

			lightArrowAdd(obj, 0.f, -.25f, 0.f, "horiz");
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
		}

		else if (obj->camLiType->val_s == "POINT")
		{
			float scale = .5f;
			//XY
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(-scale, scale, 0.f));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(scale, scale, 0.f));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(scale, -scale, 0.f));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(-scale, -scale, 0.f));

			//XZ
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(-scale, 0.f, -scale));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(scale, 0.f, -scale));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(scale, 0.f, scale));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(-scale, 0.f, scale));

			//YZ
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(0.f, scale, scale));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(0.f, scale, -scale));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(0.f, -scale, -scale));

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			obj->pE.push_back(glm::vec3(0.f, -scale, scale));
		}

		else if (obj->camLiType->val_s == "SPOT")
		{
			glm::vec3 storedBegin;
			auto radius = .3f;

			for (int i = 0; i < 32; ++i)
			{
				auto theta = 2.f * PI * i / 32.f;

				auto x = radius * cos(theta);
				auto y = radius * sin(theta);
				obj->pE.push_back(glm::vec3(x, y, -1.f));

				if (i == 0 || i == 8 || i == 16 || i == 24)
				{
					obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
					obj->pE.push_back(glm::vec3(x, y, -1.f));

					if (i == 0)
						storedBegin = glm::vec3(x, y, -1.f);
				}
			}

			obj->pE.push_back(storedBegin);

			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
			lightArrowAdd(obj, 0.f, 0.f, -.375f, "vert");
			obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));
		}
	}

	else if (obj->type == "GRID")
	{
		auto gridLines = myAbj.gridLines + 1;
		auto gridMinus = myAbj.gridLines / 2.f;

		vector<glm::vec3> gridVerts;
		gridVerts.resize(gridLines * gridLines);

		for (int i = 0; i < gridLines; ++i)
		{
			for (int j = 0; j < gridLines; ++j)
			{
				gridVerts[i + j * gridLines].x = (i - gridMinus) / gridMinus;
				gridVerts[i + j * gridLines].y = (j - gridMinus) / gridMinus;
			}
		}

		for (auto &i : gridVerts)
			obj->pE.push_back(i);
	}

	else if (obj->type == "GIZ_CIRC" || obj->type == "GIZ_CIRC_HALF")
	{
		for (int i = 0; i < 31; ++i)
			obj->pE.push_back(glm::vec3(0.f));
	}

	else if (obj->type == "GIZ_CIRC_FILL" || obj->type == "GIZ_DUAL_HANDLE")
	{
		auto r = 1.f;
		auto seg = 30;

		obj->pE.push_back(glm::vec3(0.f, 0.f, 0.f));

		for (int j = 0; j <= seg; ++j)
		{
			auto x = r * cos(j * 2.f * PI / seg);
			auto y = r * sin(j * 2.f * PI / seg);

			obj->pE.push_back(glm::vec3(x, y, 0.f));
		}
	}

	else if (obj->type == "GIZ_CONE")
	{
		glm::vec3 axX(1.f, 0.f, 0.f);
		glm::vec3 axY(0.f, 1.f, 0.f);
		glm::vec3 axZ(0.f, 0.f, 1.f);
		glm::vec3 pt, ax, axMult1, axMult2;

		auto fct = .075f;
		auto fct2 = .83f;

		if (name == "gizConeX" || name == "gizConeXSide")
		{
			ax = axX; axMult1 = axY; axMult2 = axZ;
		}

		else if (name == "gizConeY" || name == "gizConeYSide")
		{
			ax = axY; axMult1 = axX; axMult2 = axZ;
		}

		else if (name == "gizConeZ" || name == "gizConeZSide")
		{
			ax = axZ; axMult1 = axX; axMult2 = axY;
		}

		for (int i = 0; i <= 30; ++i)
		{
			pt = axMult1 * cos(((2.f * PI) / 30.f) * i) * fct;
			pt += axMult2 * sin(((2.f * PI) / 30.f) * i) * fct;
			pt += ax * fct2;
			obj->pE.push_back(pt);

			pt = axMult1 * cos(((2.f * PI) / 30.f) * (i + 1.f)) * fct;
			pt += axMult2 * sin(((2.f * PI) / 30.f) * (i + 1.f)) * fct;
			pt += ax * fct2;
			obj->pE.push_back(pt);

			obj->pE.push_back(ax);
		}
	}

	else if (obj->type == "GIZ_CUBE")
	{
		const glm::vec3 verts[] =
		{
			{ -.5f, -.5f,  .5f }, { -.5f,  .5f,  .5f },
			{  .5f,  .5f,  .5f }, {  .5f, -.5f,  .5f },
			{ -.5f, -.5f, -.5f }, { -.5f,  .5f, -.5f },
			{  .5f,  .5f, -.5f }, {  .5f, -.5f, -.5f },
		};

		const GLuint indices[] =
		{
			0, 2, 1, 0, 3, 2,
			4, 3, 0, 4, 7, 3,
			4, 1, 5, 4, 0, 1,
			3, 6, 2, 3, 7, 6,
			1, 6, 5, 1, 2, 6,
			7, 5, 6, 7, 4, 5
		};

		for (auto &i : verts)
			obj->pE.push_back(i);

		for (auto &i : indices)
			obj->idxE.push_back(i);
	}

	else if (obj->type == "GIZ_LINE")
	{
		obj->pE.push_back(glm::vec3(0.f));

		if (name == "gizLineX" || name == "gizLineXSide")
			obj->pE.push_back(glm::vec3(1.f, 0.f, 0.f));

		else if (name == "gizLineY" || name == "gizLineYSide")
			obj->pE.push_back(glm::vec3(0.f, 1.f, 0.f));

		else if (name == "gizLineZ" || name == "gizLineZSide")
			obj->pE.push_back(glm::vec3(0.f, 0.f, 1.f));
	}

	upGLBuffersNonFBX(obj, 0, 0);

	return obj;
}

void lightArrowAdd(shared_ptr<Object> obj, float arrX, float arrY, float arrZ, string orient)
{
	float orientX_l, orientX_r, orientY_l, orientY_r;

	if (orient == "horiz")
	{
		orientX_r = arrX + .1f; orientY_r = arrY;
		orientX_l = arrX - .1f; orientY_l = arrY;
	}

	else
	{
		orientX_r = arrX; orientY_r = arrY + .1f;
		orientX_l = arrX; orientY_l = arrY - .1f;
	}

	obj->pE.push_back(glm::vec3(arrX, arrY, arrZ));
	obj->pE.push_back(glm::vec3(arrX, arrY, arrZ - 1.f));
	obj->pE.push_back(glm::vec3(orientX_r, orientY_r, arrZ - 1.f)); //
	obj->pE.push_back(glm::vec3(arrX, arrY, arrZ - 1.25f));
	obj->pE.push_back(glm::vec3(orientX_l, orientY_l, arrZ - 1.f)); //
	obj->pE.push_back(glm::vec3(arrX, arrY, arrZ - 1.f));
	obj->pE.push_back(glm::vec3(arrX, arrY, arrZ));
}


void upGLBuffersNonFBX(shared_ptr<Object> myObj, bool isAnimated, bool pushIntoAllObj)
{
	GLuint VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX, VBO_BONEID, VBO_BONEWT;

	//if (myObj->name->val_s == "RootNode")
	//{
	//	cout << "pE.size() = " << myObj->pE.size() << " " << "idxE.size() = " << myObj->idxE.size() << endl;

	//	cout << endl;

	//	for (uint i = 0; i < myObj->pE.size(); ++i)
	//	{
	//		cout << "myObj->pE[i] xyz = " << glm::to_string(myObj->pE[i]) << endl;
	//	}
	//	cout << endl;

	//	for (uint i = 0; i < myObj->idxE.size(); ++i)
	//	{
	//		cout << "myObj->idxE[i] = " << myObj->idxE[i] << endl;
	//	}
	//}

	if (!myObj->pE.empty() || myObj->type == "TXT")
	{
		glCreateBuffers(1, &VBO_P);

		if (myObj->type == "TXT")
		{
			myObj->txt2D = "                                                 ";
			glNamedBufferData(VBO_P, (GLsizei)strlen(myObj->txt2D), myObj->txt2D, GL_STATIC_DRAW);
		}

		else
			glNamedBufferData(VBO_P, myObj->pE.size() * sizeof(glm::vec3), &myObj->pE[0], GL_STATIC_DRAW); //0
	}

	if (!myObj->uvE.empty())
	{
		glCreateBuffers(1, &VBO_UV);
		glNamedBufferData(VBO_UV, myObj->uvE.size() * sizeof(glm::vec2), &myObj->uvE[0], GL_STATIC_DRAW); //1
	}

	if (!myObj->tE.empty())
	{
		glCreateBuffers(1, &VBO_T);
		glNamedBufferData(VBO_T, myObj->tE.size() * sizeof(glm::vec3), &myObj->tE[0], GL_STATIC_DRAW); //2
	}

	if (!myObj->nE.empty())
	{
		glCreateBuffers(1, &VBO_N);
		glNamedBufferData(VBO_N, myObj->nE.size() * sizeof(glm::vec3), &myObj->nE[0], GL_STATIC_DRAW); //3
	}

	if (!myObj->idxE.empty())
	{
		glCreateBuffers(1, &VBO_IDX);

		if (myObj->type == "BB" && !isAnimated)
			glNamedBufferData(VBO_IDX, myObj->idxBBE.size() * sizeof(GLuint), &myObj->idxBBE[0], GL_STATIC_DRAW);

		else
			glNamedBufferData(VBO_IDX, myObj->idxE.size() * sizeof(GLuint), &myObj->idxE[0], GL_STATIC_DRAW); //0
	}

	if (isAnimated)
	{
		if (!myObj->boneIdE.empty())
		{
			glCreateBuffers(1, &VBO_BONEID);
			glNamedBufferData(VBO_BONEID, myObj->boneIdE.size() * sizeof(glm::ivec4), &myObj->boneIdE[0], GL_STATIC_DRAW); //4
		}

		if (!myObj->boneWtE.empty())
		{
			glCreateBuffers(1, &VBO_BONEWT);
			glNamedBufferData(VBO_BONEWT, myObj->boneWtE.size() * sizeof(glm::vec4), &myObj->boneWtE[0], GL_STATIC_DRAW); //5
		}
	}

	/* delete any matching / pre-existing data */
	for (auto it = myAbj.GLDataSh.begin(); it != myAbj.GLDataSh.end();)
	{
		if ((*it).obj == myObj)
			it = myAbj.GLDataSh.erase(it);

		else
			++it;
	}

	if (isAnimated)
		myAbj.GLDataSh.push_back({ myObj, VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX, VBO_BONEID, VBO_BONEWT });
	else
		myAbj.GLDataSh.push_back({ myObj, VBO_P, VBO_UV, VBO_T, VBO_N, VBO_IDX, 0, 0 });



	myObj->BBup();

	if (pushIntoAllObj)
		myAbj.allObj.push_back(myObj);
}