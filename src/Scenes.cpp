#include "pch.h"
#include "Setup_obj.h"

FBXtoAbj *myFBXtoAbj;

int randomBetw(int min, int max) {
	/* EVEN RANDOM DISTRIBUTION*/
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);
	int out = dist(engine);

	/* FAST BUT BIASED TOWARDS BOTTOM END*/
	//srand((uint)time(NULL)); // Seed the time
	//int out = rand() % (max-min + 1) + min; // Generate the number, assign to variable.

	return out;
}

void dieChoicesDebug() {
	myAbj.allDFC.clear();

	string choiceA = "play tekken";
	string choiceB = "model starcraft unit";
	string choiceC = "look for ebooks";
	string choiceD = "read TWD";

	myAbj.allChoices.push_back(choiceA);
	myAbj.allChoices.push_back(choiceB);
	myAbj.allChoices.push_back(choiceC);
	myAbj.allChoices.push_back(choiceD);


	//assign each side of the die a choice
	//100 sides
	//50 for each
	//sequential - alternating by counting up the choices
	//dont want the indices to map to the same indices each time
	//use rand() function to scramble initial choiceIdx value

	//type in max 3 numbers and print letters to screen with openGL
	//use input.cpp keyrelease
	//keep last 3 released ints
	//confirm with ENTER

	//store number / choice into DB

	//if result is over max of 100, fade away over time
	//enlarge text, fade it away over time

	int choiceIdx = randomBetw(0, (int)myAbj.allChoices.size() - 1);

	for (int i = 0; i < 100; i++)
	{
		DieFaceChoice newDFC;
		newDFC.die = 0;
		newDFC.face = i + 1;
		newDFC.choice = choiceIdx;

		myAbj.allDFC.push_back(newDFC);

		//cout << i << " - " << newDFC.face << " " << myAbj.allChoices[newDFC.choice] << endl;
		//cout << i << " - " << choiceIdx << endl;
		
		if (choiceIdx + 1 <= myAbj.allChoices.size())
			choiceIdx++;

		if (choiceIdx == myAbj.allChoices.size())
			choiceIdx = 0;
	}

	//for (int i = 0; i < myAbj.allDFC.size(); i++)
	//{
	//	cout << i << " - " << myAbj.allDFC[i].die << " " << myAbj.allDFC[i].face << " " << myAbj.allChoices[myAbj.allDFC[i].choice] << endl;
	//}
}

void startupScene(string name)
{
	dieChoicesDebug();

	if (name == "AItest")
	{
		myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
		myAbj.createNonFBX->t->val_3 = glm::vec3(8.f);
		//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
		myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

		myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		//myAbj.createNonFBX->setTarg(i->targO, 0.f);
		//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
		//myAbj.createNonFBX->lSpotO->val_f = 40.f;
		myAbj.createNonFBX->lInten->val_f = 5.f;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);

		AI *myAI = new AI();

		myAI->LoadAssimp("fbx/simpleSkinnedRect.fbx", "curl");
		//myAI->LoadAssimp("fbx/simpleSkinnedRectB.fbx", "curl");
		//myAI->LoadAssimp("fbx/simpleSkinnedRect2.fbx", "curl");
		//myAI->LoadAssimp("fbx/sphere.fbx", "curl");
		//myAI->LoadAssimp("fbx/cubeBig.fbx", "curl");

		//myAI->LoadAssimp("fbx/legIK.fbx", "curl");
		//myAI->LoadAssimp("fbx/pig.fbx", "curl");

		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//cout << "found a match for " << i->name->val_s << endl;

					i->setAnim("curl");
				}

			}

			//cout << "name = " << i->name->val_s << endl;
		}

		//++myAbj.aiLoadCt;
		//myAI->LoadAssimp("fbx/teapotBig.fbx", "curl");

		//delete myAI;

		//for (uint i = 0; i < myAbj.allObj.size(); ++i)
		//{
			//cout 
		//}

		//for (auto &i : myAbj.allObj)
		//{
		//	cout << "name = " << i->name->val_s << endl;

		//	if (i->name->val_s == "pCube1")
		//	{
		//		i->setAnim("1_1");
		//	}
		//}
	}

	if (name == "BBabj")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			myAbj.createNonFBX->t->val_3 = glm::vec3(32.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
			myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/cubeBig.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/shoulder.fbx");


			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			myObj = make_shared<Object>();
			myObj->rename("cube");
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "GREEN_ALBEDO";
			myObj->albedoM->val_s = "SKIN1_ALBEDO";

			myObj->ruffM->val_s = "GRAY_RUFF";
			myObj->normalM->val_s = "TIGHTBRICK_NORMAL";
			myObj->normalTile->val_2 = glm::vec2(2.f);
			myObj->sx->val_f = .25f;
			myObj->sy->val_f = .25f;
			myObj->sz->val_f = .25f;
			//myObj->t->val_3 = glm::vec3(0.f, 0.f, -20.f);
			myFBXtoAbj->readAbjStaticXML("fbx/cubeBig.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/shoulder.abjmesh", myObj);

		}
	}

	if (name == "BBabjAI")
	{
		myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
		myAbj.createNonFBX->t->val_3 = glm::vec3(8.f);
		myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

		myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		myAbj.createNonFBX->lInten->val_f = 5.f;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);

		AI *myAI = new AI();

		//myAI->LoadAssimp("fbx/cubeBig.fbx", "curl");
		myAI->LoadAssimp("fbx/shoulder2.fbx", "curl");


		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//cout << "found a match for " << i->name->val_s << endl;

					i->sx->val_f = .25f;
					i->sy->val_f = .25f;
					i->sz->val_f = .25f;

					i->setAnim("curl");
				}
			}
		}
	}

	if (name == "fbxAnimTest")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			myAbj.createNonFBX->t->val_3 = glm::vec3(32.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
			myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/animatedCylinder.fbx"); //
			//myFBXtoAbj->WriteAbjXML("fbx/teapotBig.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/planeHuge.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/sphere.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/shoulder.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/oblong.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/oblongNoFreeze.fbx");
			myFBXtoAbj->WriteAbjXML("fbx/simpleSkinnedRect.fbx");

			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("planeHuge");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	myObj->ruffM->val_s = "BLANK_RUFF";
		//	myObj->albedoTile->val_2 = glm::vec2(4.f);

		//	//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//	myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
		//	myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		//}

		{
			myObj = make_shared<Object>();
			myObj->rename("simpleSkinnedRect");
			myObj->type = "OBJ";
			//myObj->anim->val_b = 1;
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			//myObj->albedoM->val_s = "CHECKER_ALBEDO";
			//myObj->ruffM->val_s = "WHITE_RUFF";
			//myObj->ruffM->val_s = "GRAY_RUFF";
			myObj->ruffM->val_s = "BLANK_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);

			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			//myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
			//myFBXtoAbj->readAbjStaticXML("fbx/shoulder.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/oblong.abjmesh", myObj);
			myFBXtoAbj->readAbjStaticXML("fbx/simpleSkinnedRect.abjmesh", myObj);
		}
	}

	if (name == "fbxSkellyTest")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			myAbj.createNonFBX->t->val_3 = glm::vec3(32.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

			myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/sphere.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/shoulder.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/simpleSkinnedRectR.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/simpleSkinnedRect.fbx");

			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			//myAbj.skeletalViz = 0;
			myObj = make_shared<Object>();
			myObj->rename("simpleSkinnedRect");
			myObj->type = "OBJ";
			myObj->anim->val_b = 1;
			//myObj->v->val_b = 0;

			myObj->debugSkelGen->val_b = 1;
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			//myObj->ruffM->val_s = "WHITE_RUFF";
			//myObj->ruffM->val_s = "GRAY_RUFF";
			myObj->ruffM->val_s = "BLANK_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);

			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			//myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
			//myFBXtoAbj->readAbjStaticXML("fbx/shoulder.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/oblong.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/simpleSkinnedRectR.abjmesh", myObj);
			myFBXtoAbj->readAbjStaticXML("fbx/simpleSkinnedRect.abjmesh", myObj);

			//myFBXtoAbj->LoadAssimp("C:/Users/aleks/source/repos/Shadows_Spider/Shadows_Spider/fbx/simpleSkinnedRect.fbx");
		}

		//for (int i = 0; i < myBindSkeleton.skeletonCt; ++i)
		//{
		//	{
		//		myObj = make_shared<Object>();
		//		myObj->rename("sphere");
		//		myObj->type = "OBJ";
		//		myObj->anim->val_b = 0;
		//		myObj->debugSkel->val_b = 1;
		//		//myObj->debugSkelName->val_s = myObj->name->val_s;
		//		myObj->debugSkelName->val_s = myObj->myBindSkeleton.skeletonData[i].name;

		//		//myObj->albedoM->val_s = "BLANK_ALBEDO";
		//		//myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//		myObj->albedoM->val_s = "ABJ_ALBEDO";

		//		//myObj->albedoTile->val_2 = glm::vec2(4.f);
		//		myObj->t->val_3 = glm::vec3(myObj->myBindSkeleton.skeletonData[i].decompT);

		//		//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//		//myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
		//		myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		//	}
		//}
	}

	if (name == "fbxTest")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			myAbj.createNonFBX->t->val_3 = glm::vec3(32.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
			myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/animatedCylinder.fbx"); //
			//myFBXtoAbj->WriteAbjXML("fbx/teapotBig.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/planeHuge.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/sphere.fbx");
			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			myObj = make_shared<Object>();
			myObj->rename("planeHuge");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			//myObj->ruffM->val_s = "WHITE_RUFF";
			//myObj->ruffM->val_s = "GRAY_RUFF";
			myObj->ruffM->val_s = "BLANK_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 25.f;
			myObj->sy->val_f = 25.f;
			myObj->sz->val_f = 25.f;

			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		//{
		//	myObj->rename("planeHuge");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	//myObj->ruffM->val_s = "WHITE_RUFF";
		//	//myObj->ruffM->val_s = "GRAY_RUFF";
		//	myObj->ruffM->val_s = "BLANK_RUFF";
		//	myObj->albedoTile->val_2 = glm::vec2(4.f);
		//	myObj->sx->val_f = 10.f;
		//	myObj->sy->val_f = 10.f;
		//	myObj->sz->val_f = 10.f;

		//	//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//	myObj->t->val_3 = glm::vec3(0.f, 0.f, -50.f);
		//	myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		//}

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("sphere");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	//myObj->ruffM->val_s = "WHITE_RUFF";
		//	//myObj->ruffM->val_s = "GRAY_RUFF";
		//	myObj->ruffM->val_s = "BLANK_RUFF";
		//	myObj->albedoTile->val_2 = glm::vec2(4.f);
		//	myObj->sx->val_f = 8.f;
		//	myObj->sy->val_f = 8.f;
		//	myObj->sz->val_f = 8.f;
		//	//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//	//myObj->t->val_3 = glm::vec3(0.f, -20.f, -50.f);
		//	myObj->t->val_3 = glm::vec3(0.f, 0.f, -20.f);
		//	myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		//}

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("cubeBig");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	myObj->albedoTile->val_2 = glm::vec2(4.f);
		//	myObj->sx->val_f = .25f;
		//	myObj->sy->val_f = .25f;
		//	myObj->sz->val_f = .25f;
		//	myFBXtoAbj->readAbjStaticXML("fbx/cubeBig.abjmesh", myObj);
		//}

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("sphere");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	myObj->albedoTile->val_2 = glm::vec2(2.f);
		//	myObj->sx->val_f = 6.f;
		//	myObj->sy->val_f = 6.f;
		//	myObj->sz->val_f = 6.f;
		//	//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//	myObj->t->val_3 = glm::vec3(0.f, 0.f, 0.f);
		//	myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		//}

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("torusExtruded");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	myObj->albedoTile->val_2 = glm::vec2(4.f);
		//	myObj->sx->val_f = 2.f;
		//	myObj->sy->val_f = 2.f;
		//	myObj->sz->val_f = 2.f;
		//	//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//	myObj->t->val_3 = glm::vec3(0.f, 0.f, -20.f);
		//	myFBXtoAbj->readAbjStaticXML("fbx/torusExtruded.abjmesh", myObj);
		//}

		/* TEAPOT ANIM */
		{
			myObj = make_shared<Object>();
			myObj->rename("teapot3"); // NAME matters for anim
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoTile->val_2 = glm::vec2(2.f);
			myObj->sx->val_f = .1f;
			myObj->sy->val_f = .1f;
			myObj->sz->val_f = .1f;
			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myObj->t->val_3 = glm::vec3(0.f, 0.f, 0.f);
			myFBXtoAbj->readAbjStaticXML("fbx/teapotBig.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/cubeBig.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/cubeBig2.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/cubeBig3.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/torusSmall.abjmesh", myObj);
			//myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}
	}

	if (name == "fixPointAndSpot")
	{
		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/planeHuge.fbx");
			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			myObj = make_shared<Object>();
			myObj->rename("planeHuge0");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = .25f;
			myObj->sy->val_f = .25f;
			myObj->sz->val_f = .25f;
			myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("planeHuge1");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = .25f;
			myObj->sy->val_f = .25f;
			myObj->sz->val_f = .25f;
			myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("sphere0");
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoTile->val_2 = glm::vec2(2.f);
			myObj->sx->val_f = 3.f;
			myObj->sy->val_f = 3.f;
			myObj->sz->val_f = 3.f;
			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myObj->t->val_3 = glm::vec3(0.f, 10.f, -10.f);
			//myObj->t->val_3 = glm::vec3(0.f, 0.f, -10.f);
			//myObj->t->val_3 = glm::vec3(0.f, 0.f, -20.f);

			myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("sphere1");
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoTile->val_2 = glm::vec2(2.f);
			myObj->sx->val_f = 3.f;
			myObj->sy->val_f = 3.f;
			myObj->sz->val_f = 3.f;
			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myObj->t->val_3 = glm::vec3(0.f, 0.f, 0.f);
			myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		}

		{
			//myAbj.createNonFBX = nonFBX_VBOup("SPOT", "spotTest", 0);
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "dirTest", 0);
			//myAbj.createNonFBX = nonFBX_VBOup("POINT", "pointTest", 0);

			myAbj.createNonFBX->t->val_3 = glm::vec3(0.f, 10.f, 0.f);
			//myAbj.createNonFBX->t->val_3 = glm::vec3(0.f, 0.f, 0.f);
			//myAbj.createNonFBX->t->val_3 = glm::vec3(5.f, 5.f, 2.f);
			//myAbj.createNonFBX->t->val_3 = glm::vec3(5.f, 17.f, 27.f);
			myAbj.createNonFBX->spotTarget = glm::vec3(0, 10, -10);

			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);

			myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

			myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 400.f;
			myAbj.createNonFBX->lSpotI->val_f = 20.f;
			myAbj.createNonFBX->lInten->val_f = 120.f;

			//myAbj.createNonFBX->mvpGet();
			//myAbj.createNonFBX->t->val_3 = glm::vec3(0.f, 0.f, 2.f);
			//myAbj.createNonFBX->mvpGet();


			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}
	}

	if (name == "lerpTest0")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			myAbj.createNonFBX->tx->val_f = 32.f;
			myAbj.createNonFBX->ty->val_f = 32.f;
			myAbj.createNonFBX->tz->val_f = 32.f;
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, -80.f, 0.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 45.f, 0.f);			
			
			//myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			//myAbj.createNonFBX->tx->val_f = 32.f;
			//myAbj.createNonFBX->ty->val_f = 32.f;
			//myAbj.createNonFBX->tz->val_f = 32.f;
			////myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, -80.f, 0.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 45.f, 0.f);

			myAbj.createNonFBX->piv->val_3 = glm::vec3(myAbj.createNonFBX->tx->val_f, myAbj.createNonFBX->ty->val_f, myAbj.createNonFBX->tz->val_f);
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/cubeBig.fbx");

			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			myObj = make_shared<Object>();
			myObj->rename("lerpCube");
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "GREEN_ALBEDO";
			myObj->ruffM->val_s = "GRAY_RUFF";
			//myObj->normalM->val_s = "TIGHTBRICK_NORMAL";
			//myObj->normalTile->val_2 = glm::vec2(2.f);
			myObj->sx->val_f = .25f;
			myObj->sy->val_f = .25f;
			myObj->sz->val_f = .25f;

			//shared_ptr<MultiAttr> key0 = make_shared<MultiAttr>(0);
			//key0->name = "key0";
			//key0->type = "float";
			//key0->val_f = 1.f;

			cubeKeys(myObj);

			myFBXtoAbj->readAbjStaticXML("fbx/cubeBig.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("planeHuge0");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 25.f;
			myObj->sy->val_f = 25.f;
			myObj->sz->val_f = 25.f;

			myObj->tx->val_f = 0.f;
			myObj->ty->val_f = -10.f;
			myObj->tz->val_f = -20.f;

			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("planeHuge1");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 25.f;
			myObj->sy->val_f = 25.f;
			myObj->sz->val_f = 25.f;

			myObj->tx->val_f = 0.f;
			myObj->ty->val_f = -10.f;
			myObj->tz->val_f = -20.f;

			myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("sphere0");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	myObj->albedoTile->val_2 = glm::vec2(2.f);
		//	myObj->sx->val_f = 3.f;
		//	myObj->sy->val_f = 3.f;
		//	myObj->sz->val_f = 3.f;

		//	myObj->tx->val_f = 0.f;
		//	myObj->ty->val_f = 10.f;
		//	myObj->tz->val_f = -10.f;

		//	myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		//}

		//{
		//	myObj = make_shared<Object>();
		//	myObj->rename("sphere1");
		//	myObj->type = "OBJ";
		//	myObj->albedoM->val_s = "CHECKER_ALBEDO";
		//	myObj->albedoTile->val_2 = glm::vec2(2.f);
		//	myObj->sx->val_f = 3.f;
		//	myObj->sy->val_f = 3.f;
		//	myObj->sz->val_f = 3.f;

		//	//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
		//	myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		//}
	}

	if (name == "dirLightPosTest")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			//myAbj.createNonFBX->tx->val_f = 32.f;
			myAbj.createNonFBX->ty->val_f = 0.f;
			//myAbj.createNonFBX->tz->val_f = 32.f;
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, -80.f, 0.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 45.f, 0.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(0.f, -90.f, 0.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(0.f, 0.f, -90.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-45, 0.f, 0.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-90.f, 0.f, 0.f);

			//myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			//myAbj.createNonFBX->tx->val_f = 32.f;
			//myAbj.createNonFBX->ty->val_f = 32.f;
			//myAbj.createNonFBX->tz->val_f = 32.f;
			////myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, -80.f, 0.f);
			//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 45.f, 0.f);

			myAbj.createNonFBX->piv->val_3 = glm::vec3(myAbj.createNonFBX->tx->val_f, myAbj.createNonFBX->ty->val_f, myAbj.createNonFBX->tz->val_f);
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/cubeBig.fbx");

			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			myObj = make_shared<Object>();
			myObj->rename("plane0");
			myObj->type = "OBJ";
			myObj->ruffM->val_s = "CHECKER_INVERTED";
			myObj->ruffTile->val_2 = glm::vec2(4.f);
			//myObj->albedoM->val_s = "BLANK_ALBEDO";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 50.f;
			myObj->sy->val_f = 50.f;
			myObj->sz->val_f = 50.f;

			myObj->tx->val_f = 0.f;
			myObj->ty->val_f = -5.f;
			myObj->tz->val_f = 0.f;

			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("plane1");
			myObj->type = "OBJ";
			myObj->ruffM->val_s = "CHECKER_INVERTED";
			myObj->ruffTile->val_2 = glm::vec2(4.f);
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 50.f;
			myObj->sy->val_f = 50.f;
			myObj->sz->val_f = 50.f;

			myObj->tx->val_f = 0.f;
			myObj->ty->val_f = 0.f;
			myObj->tz->val_f = -20.f;

			myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("sphere");
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->ruffM->val_s = "CHECKER_INVERTED";
			myObj->ruffTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 2.f;
			myObj->sy->val_f = 2.f;
			myObj->sz->val_f = 2.f;

			myObj->tx->val_f = 10.f;
			myObj->ty->val_f = 5.f;
			myObj->tz->val_f = 0.f;
			myObj->bb->val_b = 1;

			myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("teapot");
			myObj->type = "OBJ";
			myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->ruffM->val_s = "CHECKER_INVERTED";
			myObj->ruffTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = .15f;
			myObj->sy->val_f = .15f;
			myObj->sz->val_f = .15f;
			//myObj->bb->val_b = 1;

			myObj->tx->val_f = 0.f;
			myObj->ty->val_f = 5.f;
			myObj->tz->val_f = 0.f;

			myFBXtoAbj->readAbjStaticXML("fbx/teapotBigCentered.abjmesh", myObj);
		}
	}

	if (name == "stompBox")
	{
		myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
		myAbj.createNonFBX->t->val_3 = glm::vec3(8.f);
		//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
		myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

		myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		//myAbj.createNonFBX->setTarg(i->targO, 0.f);
		//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
		//myAbj.createNonFBX->lSpotO->val_f = 40.f;
		myAbj.createNonFBX->lInten->val_f = 5.f;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);

		AI *myAI = new AI();

		myAI->LoadAssimp("fbx/stomp0.fbx", "curl");
		//myAI->LoadAssimp("fbx/simpleSkinnedRectB.fbx", "curl");
		//myAI->LoadAssimp("fbx/simpleSkinnedRect2.fbx", "curl");
	
		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//cout << "found a match for " << i->name->val_s << endl;

					i->sx->val_f = 8.f;
					i->sy->val_f = 8.f;
					i->sz->val_f = 8.f;

					i->setAnim("curl");
				}

			}

			//cout << "name = " << i->name->val_s << endl;
		}

		//++myAbj.aiLoadCt;
		//myAI->LoadAssimp("fbx/teapotBig.fbx", "curl");

		//delete myAI;

	}

	if (name == "transpGrass")
	{
		//myAbj.myFSQ->transpW->val_f = 5.f;

		myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
		myAbj.createNonFBX->t->val_3 = glm::vec3(8.f);
		myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

		myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		myAbj.createNonFBX->lInten->val_f = 5.f;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);

		AI *myAI = new AI();

		myAI->LoadAssimp("fbx/planeHuge.fbx", "curl");
		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//cout << "found a match for " << i->name->val_s << endl;
					//i->Ko->val_f = .75f;
					i->albedoM->val_s = "BLUE_ALBEDO";
					i->alphaM->val_s = "GRASS_ALPHA";
					i->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
					//i->t->val_3 = glm::vec3(1.f, 0.f, 2.f);
					//i->t->val_3 = glm::vec3(0.f, 0.f, 2.f);
					i->setAnim("curl");
				}

			}
		}

		myAI->LoadAssimp("fbx/planeHuge.fbx", "curl");
		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//cout << "found a match for " << i->name->val_s << endl;
					//i->Ko->val_f = .75f;
					i->sx->val_f = 5.f;
					i->sy->val_f = 5.f;
					i->sz->val_f = 5.f;
					//i->t->val_3 = glm::vec3(1.f, 0.f, 2.f);
					i->t->val_3 = glm::vec3(0.f, -2.f, 2.f);
					i->setAnim("curl");
				}

			}
		}
	}

	if (name == "volumeCone")
	{
		//myAbj.myFSQ->transpW->val_f = 5.f;

		//myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
		myAbj.createNonFBX = nonFBX_VBOup("SPOT", "sun", 0);
		myAbj.createNonFBX->t->val_3 = glm::vec3(8.f);
		myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

		myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		myAbj.createNonFBX->lInten->val_f = 5.f;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);

		AI *myAI = new AI();

		myAI->LoadAssimp("fbx/planeHuge.fbx", "curl");
		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//i->Ko->val_f = .75f;
					i->sx->val_f = 5.f;
					i->sy->val_f = 5.f;
					i->sz->val_f = 5.f;
					//i->t->val_3 = glm::vec3(1.f, 0.f, 2.f);
					i->t->val_3 = glm::vec3(0.f, -2.f, 2.f);
					i->setAnim("curl");
				}
			}
		}

		myAI->LoadAssimp("fbx/sphere.fbx", "curl");
		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//i->Ko->val_f = .75f;
					//i->t->val_3 = glm::vec3(1.f, 0.f, 2.f);
					//i->t->val_3 = glm::vec3(0.f, -2.f, 2.f);
					i->setAnim("curl");
				}
			}
		}

	}

	if (name == "VST")
	{
		myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
		myAbj.createNonFBX->t->val_3 = glm::vec3(8.f);
		//myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
		myAbj.createNonFBX->r->val_3 = glm::vec3(-45.f, 0.f, 0.f);

		myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
		myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
		//myAbj.createNonFBX->setTarg(i->targO, 0.f);
		//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
		//myAbj.createNonFBX->lSpotO->val_f = 40.f;
		myAbj.createNonFBX->lInten->val_f = 5.f;
		myAbj.allObj.push_back(myAbj.createNonFBX);
		myAbj.allCamLi.push_back(myAbj.createNonFBX);


		AI *myAI = new AI();

		//myAI->LoadAssimp("fbx/simpleSkinnedRect.fbx", "curl");
		//myAI->LoadAssimp("fbx/simpleSkinnedRectB.fbx", "curl");
		//myAI->LoadAssimp("fbx/simpleSkinnedRect2.fbx", "curl");
		//myAI->LoadAssimp("fbx/sphere.fbx", "curl");
		//myAI->LoadAssimp("fbx/MeetMat.obj", "blank");
		myAI->LoadAssimp("fbx/planeHuge.fbx", "blank");



		//myAI->LoadAssimp("fbx/legIK.fbx", "curl");
		//myAI->LoadAssimp("fbx/pig.fbx", "curl");

		myAbj.aiLoadCt++;

		for (auto &i : myAbj.allObj)
		{
			for (auto &j : myAbj.aiNameUnknown)
			{
				if (i->name->val_s == j)
				{
					//cout << "found a match for " << i->name->val_s << endl;

					//i->normalM->val_s = "VORONOI_NORMAL";
					i->normalM->val_s = "TIGHTBRICK_NORMAL";
					i->albedoM->val_s = "CHECKER_ALBEDO";


					//i->albedoM->val_s = "BLUE_ALBEDO";

					//i->ruffM->val_s = "BLANK_RUFF";
					i->ruffM->val_s = "GRAY_RUFF";
					//i->ruffM->val_s = "WHITE_RUFF";

					//i->normalTile->val_2 = glm::vec2(2.f);
					//i->normalTile->val_2 = glm::vec2(4.f);


					//i->albedoM->val_s = "BLACK_ALBEDO";


					i->setAnim("curl");
				}
			}
		}
	}

	if (name == "VSTabj")
	{
		{
			myAbj.createNonFBX = nonFBX_VBOup("DIR", "sun", 0);
			myAbj.createNonFBX->t->val_3 = glm::vec3(32.f);
			myAbj.createNonFBX->r->val_3 = glm::vec3(-25.f, 0.f, 0.f);
			myAbj.createNonFBX->piv->val_3 = myAbj.createNonFBX->t->val_3;
			myAbj.createNonFBX->Cgiz = glm::vec3(1.f, 0.f, 0.f);
			//myAbj.createNonFBX->setTarg(i->targO, 0.f);
			//myAbj.createNonFBX->setTarg(glm::vec3(0.f, 6.f, -10.f), 0.f);
			//myAbj.createNonFBX->lSpotO->val_f = 40.f;
			myAbj.createNonFBX->lInten->val_f = 5.f;
			myAbj.allObj.push_back(myAbj.createNonFBX);
			myAbj.allCamLi.push_back(myAbj.createNonFBX);
		}

		{
			myFBXtoAbj = new FBXtoAbj();
			//myFBXtoAbj->WriteAbjXML("fbx/animatedCylinder.fbx"); //
			//myFBXtoAbj->WriteAbjXML("fbx/teapotBig.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/planeHuge.fbx");
			//myFBXtoAbj->WriteAbjXML("fbx/sphere.fbx");
			delete myFBXtoAbj;
		}

		auto myObj = make_shared<Object>();

		{
			myObj = make_shared<Object>();
			myObj->rename("planeHuge");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "BLACK_ALBEDO";
			//myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoM->val_s = "BLUE_ALBEDO";
			//myObj->albedoM->val_s = "MAGENTA_ALBEDO";


			//myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->ruffM->val_s = "GRAY_RUFF";
			//myObj->ruffM->val_s = "BLANK_RUFF";
			myObj->normalM->val_s = "TIGHTBRICK_NORMAL";
			//myObj->normalM->val_s = "TIGHTBRICK2_NORMAL";
			//myObj->normalM->val_s = "SQUARES_NORMAL";

			myObj->normalTile->val_2 = glm::vec2(2.f);
			//myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 25.f;
			myObj->sy->val_f = 25.f;
			myObj->sz->val_f = 25.f;

			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			myObj->t->val_3 = glm::vec3(0.f, -10.f, -20.f);
			myFBXtoAbj->readAbjStaticXML("fbx/planeHuge.abjmesh", myObj);
		}

		{
			myObj = make_shared<Object>();
			myObj->rename("sphere");
			myObj->type = "OBJ";
			//myObj->albedoM->val_s = "CHECKER_ALBEDO";
			myObj->albedoM->val_s = "GREEN_ALBEDO";
			//myObj->albedoM->val_s = "BLUE_ALBEDO";
			myObj->albedoM->val_s = "SKIN1_ALBEDO";

			//myObj->ruffM->val_s = "WHITE_RUFF";
			myObj->ruffM->val_s = "GRAY_RUFF";
			//myObj->ruffM->val_s = "BLANK_RUFF";
			myObj->normalM->val_s = "TIGHTBRICK_NORMAL";
			myObj->normalTile->val_2 = glm::vec2(2.f);
			//myObj->albedoTile->val_2 = glm::vec2(4.f);
			myObj->sx->val_f = 8.f;
			myObj->sy->val_f = 8.f;
			myObj->sz->val_f = 8.f;
			//myObj->r->val_3 = glm::vec3(90.f, 0.f, 0.f);
			//myObj->t->val_3 = glm::vec3(0.f, -20.f, -50.f);
			myObj->t->val_3 = glm::vec3(0.f, 0.f, -20.f);
			myFBXtoAbj->readAbjStaticXML("fbx/sphere.abjmesh", myObj);
		}
	}
}

void cubeKeys(shared_ptr<Object> myObj) {
	MultiAttrKey newKey0;

	myObj->sx->keys.push_back({ 0, 0.f });
	myObj->sy->keys.push_back({ 0, 0.f });
	myObj->sz->keys.push_back({ 0, 0.f });

	myObj->sx->keys.push_back({ 30, 1.f });
	myObj->sy->keys.push_back({ 30, 1.f });
	myObj->sz->keys.push_back({ 30, 1.f });

	myObj->tx->keys.push_back({ 0, 0.f });

	myObj->tx->keys.push_back({ 30, 50.f });

	/* dieMsgAlpha */
	newKey0.frame = 1;
	newKey0.val = 1.f;
	myAbj.myTxt->dieMsgAlpha->keys.push_back(newKey0);

	newKey0.frame = 60;
	newKey0.val = 0.f;
	myAbj.myTxt->dieMsgAlpha->keys.push_back(newKey0);
}



//void cubeKeys(shared_ptr<Object> myObj) {
//	MultiAttrKey newKey0;
//
//	myObj->sx->keys.push_back({ 0, 0.f });
//	myObj->sy->keys.push_back({ 0, 0.f });
//	myObj->sz->keys.push_back({ 0, 0.f });	
//
//	myObj->sx->keys.push_back({ 30, .9f });
//	myObj->sy->keys.push_back({ 30, 2.9f });
//	myObj->sz->keys.push_back({ 30, .9f });
//
//
//	newKey0.frame = 60;
//	newKey0.val = .1f;
//	myObj->sx->keys.push_back(newKey0);
//	myObj->sy->keys.push_back(newKey0);
//	myObj->sz->keys.push_back(newKey0);
//
//	newKey0.frame = 90;
//	newKey0.val = .75f;
//	myObj->sx->keys.push_back(newKey0);
//	myObj->sy->keys.push_back(newKey0);
//	myObj->sz->keys.push_back(newKey0);
//
//	newKey0.frame = 105;
//	newKey0.val = .5f;
//	myObj->sx->keys.push_back(newKey0);
//	myObj->sy->keys.push_back(newKey0);
//	myObj->sz->keys.push_back(newKey0);
//
//	newKey0.frame = 115;
//	newKey0.val = 1.f;
//	myObj->sx->keys.push_back(newKey0);
//	myObj->sy->keys.push_back(newKey0);
//	myObj->sz->keys.push_back(newKey0);
//
//	newKey0.frame = 120;
//	newKey0.val = 0.f;
//	myObj->sx->keys.push_back(newKey0);
//	myObj->sy->keys.push_back(newKey0);
//	myObj->sz->keys.push_back(newKey0);
//
//	/* dieMsgAlpha */
//	newKey0.frame = 1;
//	newKey0.val = 1.f;
//	myAbj.myTxt->dieMsgAlpha->keys.push_back(newKey0);
//
//	newKey0.frame = 60;
//	newKey0.val = 0.f;
//	myAbj.myTxt->dieMsgAlpha->keys.push_back(newKey0);
//}

//void cubeKeys(shared_ptr<Object> myObj) {
//	MultiAttrKey newKey0;
//	newKey0.frame = 1;
//	newKey0.val = 0.f;
//	myObj->s->keys.push_back(newKey0);
//
//	newKey0.frame = 30;
//	newKey0.val = .4f;
//	myObj->s->keys.push_back(newKey0);
//
//	newKey0.frame = 60;
//	newKey0.val = .1f;
//	myObj->s->keys.push_back(newKey0);
//
//	newKey0.frame = 90;
//	newKey0.val = .75f;
//	myObj->s->keys.push_back(newKey0);
//
//	newKey0.frame = 105;
//	newKey0.val = .5f;
//	myObj->s->keys.push_back(newKey0);
//
//	newKey0.frame = 115;
//	newKey0.val = 1.f;
//	myObj->s->keys.push_back(newKey0);
//
//	newKey0.frame = 120;
//	newKey0.val = 0.f;
//	myObj->s->keys.push_back(newKey0);
//}