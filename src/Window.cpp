#include "pch.h"
#include "Window.h"

void quitSeq()
{
	//DELETE ALL OBJECTS AND THEIR VBOS
	for (auto &i : myAbj.allObj)
		i->selected = 1;

	delete_();

	//DELETE ALL FBOS AND THEIR ATTACHED TEXTURES
	resizeTexClearMem();

	//DELETE ALL SHADOWMAPS
	addDeleteShadows("delete");

	//DELETE ALL  "REG" TEXTURES
	for (auto &i : myAbj.allTexMaps)
	{
		for (auto &j : i.layer)
		{
			glMakeTextureHandleNonResidentARB(j.tex0_64);
			glMakeTextureHandleNonResidentARB(j.tex1_64);
			glDeleteTextures(1, &j.tex0_32);
			glDeleteTextures(1, &j.tex1_32);
		}
	}

	//DELETE ALL PROGRAMS
	for (auto &i : myAbj.allPro)
		glDeleteProgram(i.pro);

	//DELETE REMAINING ABJ NODES THAT HAVE FBOS INCLUDING ONES IN GLWIDGETSH
	//delete ubos
	glDeleteBuffers(1, &myAbj.pro);
	glDeleteBuffers(1, &myAbj.uboScene);
	glDeleteBuffers(1, &myAbj.uboLight);

	glfwTerminate();
}

void delete_()
{
	myAbj.myGizNull->v->val_b = 0;
	myAbj.myGizNull->parentTo = 0;
	myAbj.myPivot->parentTo = 0;
	bool needsShadowRefresh = 0;
	myAbj.myPivot->v->val_b = 0;

	for (auto &i : myAbj.allObj) //select downstream, too
	{
		if (i->selected)
		{
			for (auto &j : myAbj.allObj)
			{
				if (j->parentTo == i)
					j->selected = 1;
			}
		}
	}

	for (auto it = myAbj.allObj.begin(); it != myAbj.allObj.end();)
	{
		if ((*it)->deletable && (*it)->selected)
		{
			for (auto &i : myAbj.allObj)
			{
				if ((*it)->dupeStenFix == i->name->val_s)
				{
					//reset
					i->dupeStenFix = "999";
					i->v->val_b = 1;
				}
			}

			if ((*it)->camLiTypeGet("light"))
				needsShadowRefresh = 1;

			(*it)->deleteVAO_VBO();
			it = myAbj.allObj.erase(it);
		}

		else
			++it;
	}

	for (auto it = myAbj.allCamLi.begin(); it != myAbj.allCamLi.end();)
	{
		if ((*it)->deletable && (*it)->selected)
			it = myAbj.allCamLi.erase(it);

		else
			++it;
	}

	if (needsShadowRefresh)
		addDeleteShadows("refresh");


	myAbj.lightCt = countLights();
	setLightsDirty();
}

void deleteObj()
{
	cout << "in faux delete obj" << endl;

	myAbj.myGizNull->v->val_b = 0;
	myAbj.myGizNull->parentTo = 0;
	myAbj.myPivot->parentTo = 0;
	bool needsShadowRefresh = 0;
	myAbj.myPivot->v->val_b = 0;

	for (auto &i : myAbj.allObj) //select downstream, too
	{
		if (i->selected)
		{
			for (auto &j : myAbj.allObj)
			{
				if (j->parentTo == i)
					j->selected = 1;
			}
		}
	}

	for (auto it = myAbj.allObj.begin(); it != myAbj.allObj.end();)
	{
		if ((*it)->deletable && (*it)->selected)
		{
			for (auto &i : myAbj.allObj)
			{
				if ((*it)->dupeStenFix == i->name->val_s)
				{
					//reset
					i->dupeStenFix = "999";
					i->v->val_b = 1;
				}
			}

			if ((*it)->camLiTypeGet("light"))
				needsShadowRefresh = 1;

			(*it)->deleteVAO_VBO();
			it = myAbj.allObj.erase(it);
		}

		else
			++it;
	}

	for (auto it = myAbj.allCamLi.begin(); it != myAbj.allCamLi.end();)
	{
		if ((*it)->deletable && (*it)->selected)
			it = myAbj.allCamLi.erase(it);

		else
			++it;
	}

	if (needsShadowRefresh)
		addDeleteShadows("refresh");


	myAbj.lightCt = countLights();
	setLightsDirty();
	myAbj.selB = 0;
}

void dupeObj()
{
	if (myAbj.selB && myAbj.selB->type != "CAMLI") //simple
	{
		bool gizWasOn = 0;

		if (myAbj.myGizNull->v->val_b)
		{
			myAbj.myGizNull->v->val_b = 0;
			myAbj.myGizNull->parentTo = 0;

			gizWasOn = 1; //store gizmo viz
		}

		vector<shared_ptr<Object>> dupeTemp;

		for (auto &i : myAbj.allObj)
		{
			if (i->selected)
				dupeTemp.push_back(i);
		}

		for (auto &i : dupeTemp)
		{
			auto obj = make_shared<Object>();
			obj = nonFBX_VBOup(i->type, i->name->val_s, make_shared<Object>(*i));

			//bool changedLight = 0;

			//if (newObj[0]->camLiTypeGet("light"))
			//{
			//	if (!tryAddSwitchLight(newObj[0]->camLiType->val_s))
			//		newObj[0]->camLiType->val_s = "PERSP";

			//	changedLight = 1;
			//}

			obj->dupeStenFix = i->name->val_s;
			myAbj.allObj.push_back(obj);

			if (i->type == "CAMLI")
				myAbj.allCamLi.push_back(i);

			obj->VAO_load();
			myAbj.selB = obj;
			i->selected = 0;

			//if (changedLight)
			//lightCt = countLights();
		}

		if (gizWasOn)
		{
			myAbj.myGizNull->v->val_b = 1;
			myAbj.myGizNull->parentTo = myAbj.selB;
		}

		setLightsDirty();
	}


}