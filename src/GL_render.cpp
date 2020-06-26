#include "pch.h"
#include "GL_render.h"

void printGLM4x4(glm::mat4 in4, string name)
{
	string toPrint = "glm::mat4(";

	for (int i = 0; i < in4.length(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			toPrint += to_string(float(in4[i][j]));

			if (i == in4.length() - 1 && j == 3)
				toPrint += "";
			else
				toPrint += " , ";

		}
	}

	toPrint += ");";

	cout << name << toPrint << endl;
}


void bbViz()
{
	for (auto &i : myAbj.allObj)
	{
		if (i->bb->val_b)
		{
			if (i->anim->val_b == 0) // STATIC OBJ
			{
				//glm::vec3 cWireStored; ///
				vector<glm::vec3> aabb8Pts;

				glUseProgram2("pBB");

				/////// 
				//OBB
				///////
				glm::vec3 bbMinOS = i->bbMin;
				glm::vec3 bbMaxOS = i->bbMax;
				glm::vec3 bbSizeOS = bbMaxOS - bbMinOS;
				glm::vec3 bbCenterOS = .5f * (bbMinOS + bbMaxOS);
				i->obbMVP = glm::translate(glm::mat4(1.f), bbCenterOS) * glm::scale(glm::mat4(1.f), bbSizeOS);

				cout << "~~~~~~~~~~" << endl;
				cout << "bbMinOS = " << glm::to_string(bbSizeOS) << endl;
				cout << "bbMaxOS = " << glm::to_string(bbSizeOS) << endl;
				cout << "bbSizeOS = " << glm::to_string(bbSizeOS) << endl;
				cout << "bbCenterOS = " << glm::to_string(bbSizeOS) << endl;
				cout << "~~~~~~~~~~" << endl;



				i->aabbTgl = 0; i->obbTgl = 1;
				i->mvpGet();
				i->render();
				i->aabbTgl = 0; i->obbTgl = 0;

				/////////// 
				//////AABB
				///////////
				//aabb8Pts.push_back(glm::vec3(i->bbMax.x, i->bbMax.y, i->bbMax.z));
				//aabb8Pts.push_back(glm::vec3(i->bbMin.x, i->bbMax.y, i->bbMax.z));
				//aabb8Pts.push_back(glm::vec3(i->bbMin.x, i->bbMin.y, i->bbMax.z));
				//aabb8Pts.push_back(glm::vec3(i->bbMax.x, i->bbMin.y, i->bbMax.z));

				//aabb8Pts.push_back(glm::vec3(i->bbMax.x, i->bbMax.y, i->bbMin.z));
				//aabb8Pts.push_back(glm::vec3(i->bbMin.x, i->bbMax.y, i->bbMin.z));
				//aabb8Pts.push_back(glm::vec3(i->bbMin.x, i->bbMin.y, i->bbMin.z));
				//aabb8Pts.push_back(glm::vec3(i->bbMax.x, i->bbMin.y, i->bbMin.z));

				//glm::vec4 newBBMin = i->MM * glm::vec4(aabb8Pts[0], 1.f);
				//glm::vec4 newBBMax = i->MM * glm::vec4(aabb8Pts[0], 1.f);

				//for (uint j = 0; j < aabb8Pts.size(); ++j)
				//{
				//	glm::vec4 bbPtWS = i->MM * glm::vec4(aabb8Pts[j], 1.f);
				//	newBBMin = glm::min(bbPtWS, newBBMin);
				//	newBBMax = glm::max(bbPtWS, newBBMax);
				//}

				//glm::vec3 bbSizeWS = newBBMax - newBBMin;
				//glm::vec3 bbCenterWS = .5f * (newBBMin + newBBMax);
				//i->aabbMVP = glm::translate(glm::mat4(1.f), bbCenterWS) * glm::scale(glm::mat4(1.f), bbSizeWS);

				//i->aabbTgl = 1; i->obbTgl = 0;
				//i->mvpGet();
				//i->render();
				//i->aabbTgl = 0; i->obbTgl = 0;

				////cout << "bbCenterWS = " << glm::to_string(bbCenterWS) << endl;

				///* BOUNDING SPHERE */
				//glUseProgram2("pGiz_circ");

				//myAbj.translateSphereVol = glm::translate(glm::mat4(1.f), bbCenterWS) * glm::scale(glm::mat4(1.f), bbSizeWS);

				//for (auto &j : myAbj.allGiz)
				//{
				//	if (j->type == "GIZ_CIRC")
				//	{
				//		glDisable(GL_DEPTH_TEST);
				//		j->spherebbTgl = 1;

				//		glm::vec3 CgizStored = j->Cgiz;

				//		if (i->selected)
				//			j->Cgiz = myAbj.Csel;

				//		else
				//			j->Cgiz = glm::vec3(0.f);

				//		j->mvpGet();
				//		j->render();

				//		j->Cgiz = CgizStored;
				//		j->spherebbTgl = 0;
				//		glEnable(GL_DEPTH_TEST);
				//	}
				//}


			}
		}
	}

	/* AABB - STEP 2 - MIN / MAX */
	for (auto &i : myAbj.allObj)
	{
		if (i->bb->val_b)
		{
			//if (i->anim->val_b == 1)
			//{
			//	glm::vec3 cWireStored; ///
			//	vector<glm::vec3> aabb8Pts;

			//	glUseProgram2("pBB");

			//	/* OBB */
			//	glm::vec4 aabbMinOS = (i->aabbV4OS.empty()) ? glm::vec4(0.f) : i->aabbV4OS[0];
			//	glm::vec4 aabbMaxOS = aabbMinOS;

			//	for (uint j = 0; j < i->aabbV4OS.size(); ++j)
			//	{
			//		aabbMinOS = glm::min(i->aabbV4OS[j], aabbMinOS);
			//		aabbMaxOS = glm::max(i->aabbV4OS[j], aabbMaxOS);
			//	}

			//	glm::vec3 aabbSizeOS = aabbMaxOS - aabbMinOS;
			//	glm::vec3 aabbCenterOS = .5f * (aabbMinOS + aabbMaxOS);
			//	i->obbMVP = glm::translate(glm::mat4(1.f), aabbCenterOS) * glm::scale(glm::mat4(1.f), aabbSizeOS);

			//	i->aabbTgl = 0; i->obbTgl = 1;
			//	i->mvpGet();
			//	i->render();
			//	i->aabbTgl = 0; i->obbTgl = 0;

			//	/* FASTER BUT LOOSER AABB FROM OBB PTS */
			//	glm::vec4 aabbMin = aabbMinOS;
			//	glm::vec4 aabbMax = aabbMaxOS;

			//	aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMax.y, aabbMax.z));
			//	aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMax.y, aabbMax.z));
			//	aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMin.y, aabbMax.z));
			//	aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMin.y, aabbMax.z));

			//	aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMax.y, aabbMin.z));
			//	aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMax.y, aabbMin.z));
			//	aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMin.y, aabbMin.z));
			//	aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMin.y, aabbMin.z));

			//	glm::vec4 newBBMin = i->MM * glm::vec4(aabb8Pts[0], 1.f);
			//	glm::vec4 newBBMax = newBBMin;

			//	for (uint j = 0; j < aabb8Pts.size(); ++j)
			//	{
			//		glm::vec4 bbPtWS = i->MM * glm::vec4(aabb8Pts[j], 1.f);
			//		newBBMin = glm::min(bbPtWS, newBBMin);
			//		newBBMax = glm::max(bbPtWS, newBBMax);
			//	}

			//	///* TIGHTER BUT MORE COMPARISONS AABB */
			//	//glm::vec4 aabbMin = (i->aabbV4WS.empty()) ? glm::vec4(0.f) : i->aabbV4WS[0];
			//	//glm::vec4 aabbMax = (i->aabbV4WS.empty()) ? glm::vec4(0.f) : i->aabbV4WS[0];

			//	//for (uint j = 0; j < i->aabbV4WS.size(); ++j)
			//	//{
			//	//	aabbMin = glm::min(i->aabbV4WS[j], aabbMin);
			//	//	aabbMax = glm::max(i->aabbV4WS[j], aabbMax);
			//	//}

			//	//aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMax.y, aabbMax.z));
			//	//aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMax.y, aabbMax.z));
			//	//aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMin.y, aabbMax.z));
			//	//aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMin.y, aabbMax.z));

			//	//aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMax.y, aabbMin.z));
			//	//aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMax.y, aabbMin.z));
			//	//aabb8Pts.push_back(glm::vec3(aabbMin.x, aabbMin.y, aabbMin.z));
			//	//aabb8Pts.push_back(glm::vec3(aabbMax.x, aabbMin.y, aabbMin.z));

			//	//glm::vec4 newBBMin = glm::vec4(aabb8Pts[0], 1.f);
			//	//glm::vec4 newBBMax = glm::vec4(aabb8Pts[0], 1.f);

			//	//for (uint j = 0; j < aabb8Pts.size(); ++j)
			//	//{
			//	//	glm::vec4 bbPtWS = glm::vec4(aabb8Pts[j], 1.f);
			//	//	newBBMin = glm::min(bbPtWS, newBBMin);
			//	//	newBBMax = glm::max(bbPtWS, newBBMax);
			//	//}

			//	/////
			//	glm::vec3 bbSizeWS = newBBMax - newBBMin;
			//	glm::vec3 bbCenterWS = .5f * (newBBMin + newBBMax);
			//	i->aabbMVP = glm::translate(glm::mat4(1.f), bbCenterWS) * glm::scale(glm::mat4(1.f), bbSizeWS);

			//	i->aabbTgl = 1; i->obbTgl = 0;
			//	i->mvpGet();
			//	i->render();
			//	//cout << "rendering AABB " << endl;
			//	i->aabbTgl = 0; i->obbTgl = 0;

			//	////////
			//	//BOUNDING SPHERE
			//	///////
			//	glUseProgram2("pGiz_circ");

			//	myAbj.translateSphereVol = glm::translate(glm::mat4(1.f), bbCenterWS) * glm::scale(glm::mat4(1.f), bbSizeWS);

			//	for (auto &j : myAbj.allGiz)
			//	{
			//		if (j->type == "GIZ_CIRC")
			//		{
			//			glDisable(GL_DEPTH_TEST);
			//			j->spherebbTgl = 1;

			//			glm::vec3 CgizStored = j->Cgiz;
			//			if (i->selected)
			//				j->Cgiz = myAbj.Csel;
			//			else
			//				j->Cgiz = glm::vec3(0.f);

			//			j->mvpGet();
			//			j->render();

			//			j->Cgiz = CgizStored;

			//			j->spherebbTgl = 0;
			//			glEnable(GL_DEPTH_TEST);
			//		}
			//	}

			//}
		}
	}
}

void moveByHand_strafe()
{
	float gravity = -150.f * 6;
	float jumpPower = 250.f;
	float terrainHeight = 0.f;

	float runSpeed = 20.f / 2.f;
	float currentSpeed = 0.f;
	float currrentUpwardsSpeed = 0.f;
	float leftStickAngle = 0.f;

	int axesCount;
	const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

	float inputX = axes[0];
	float inputY = axes[1];

	if (myAbj.wTgl)
		inputY = 1.f;

	if (myAbj.aTgl)
		inputX = -1.f;

	if (myAbj.sTgl)
		inputY = -1.f;

	if (myAbj.dTgl)
		inputX = 1.f;

	leftStickAngle = atan2(-inputX, inputY);

	if (leftStickAngle < 0.f)
		leftStickAngle += 3.14f * 2.f;

	leftStickAngle = glm::degrees(leftStickAngle);
	//cout << "leftStickAngle = " << leftStickAngle << endl;

	currentSpeed = 0.f;

	if (myAbj.wTgl || myAbj.aTgl || myAbj.sTgl || myAbj.dTgl)
	{
		currentSpeed = runSpeed;
	}

	if (leftStickAngle != 0.f)
	{
		currentSpeed = runSpeed;
	}

	/* RIGHT STICK */
	float stickSpeed = 1.f;
	myAbj.selCamLi->r->val_3.x -= stickSpeed * axes[2];
	myAbj.selCamLi->r->val_3.y = glm::clamp(myAbj.selCamLi->r->val_3.y - stickSpeed * -axes[3], -80.f, -2.f);

	for (auto &i : myAbj.heroObjects)
	{
		for (auto &j : myAbj.frustumObjs)
		{
			if (i == j->name->val_s)
			{
				j->r->val_3.y -= stickSpeed * axes[2];
			}
		}
	}

	int buttonCt; //14
	const unsigned char *controllerButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCt);

	//float autoBunnyHopPrevent = (float)((double)GetTickCount() - (double)myAbj.jumpTimer) / 1000.f; //

	if (controllerButtons[0] == GLFW_PRESS)
	{
		if (myAbj.isInAir == 0)
		//if (myAbj.isInAir == 0 && autoBunnyHopPrevent >= .5f) // prevents auto bunny hop
		{
			currrentUpwardsSpeed = jumpPower;
			myAbj.isInAir = 1;

			myAbj.jumpTimer = GetTickCount();
		}
	}

	for (auto &i : myAbj.heroObjects)
	{
		for (auto &j : myAbj.frustumObjs)
		{
			if (i == j->name->val_s)
			{
				float distance = -currentSpeed * myAbj.deltaFrameTime;
				float dx = distance * glm::sin(glm::radians(j->r->val_3.y + leftStickAngle));
				float dz = distance * glm::cos(glm::radians(j->r->val_3.y + leftStickAngle));

				j->tx->val_f += dx;
				j->tz->val_f += dz;

				myAbj.selCamLi->setDirty();

				/* FALLING AKA GRAVITY RELATED */
				currrentUpwardsSpeed += gravity * myAbj.deltaFrameTime;
				j->ty->val_f += currrentUpwardsSpeed * myAbj.deltaFrameTime;

				if (j->ty->val_f < 0.f)
				{
					currrentUpwardsSpeed = 0.f;
					myAbj.isInAir = 0;
					j->ty->val_f = terrainHeight;

					//myAbj.jumpTimer = GetTickCount();
				}
			}
		}
	}
}

void moveByHand_free()
{
	cout << "moveByHand_free 0" << endl;

	float gravity = -150.f * 6;
	float jumpPower = 300.f;
	float terrainHeight = 0.f;

	float runSpeed = 20.f / 2.f;
	float currentSpeed = 0.f;
	float currrentUpwardsSpeed = 0.f;

	int axesCount;
	const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

	cout << "axesCount = " << axesCount << endl;

	float inputX = axes[0];
	float inputY = axes[1];

	cout << "moveByHand_free 1" << endl;


	//multiply by selCam view and right vec
	glm::vec3 lookONoY = myAbj.selCamLi->lookO;
	lookONoY.y = 0.f;

	if (myAbj.wTgl)
		inputY = 1.f;

	if (myAbj.aTgl)
		inputX = -1.f;

	if (myAbj.sTgl)
		inputY = -1.f;

	if (myAbj.dTgl)
		inputX = 1.f;

	glm::vec3 targetDirection = (inputX * myAbj.selCamLi->rightO) + (inputY * lookONoY);
	//cout << "lookDirection = " << glm::to_string(lookDirection) << endl;

	float leftStickAngle = 0.f;

	if (targetDirection != glm::vec3(0.f))
	{
		leftStickAngle = atan2(-targetDirection.x, -targetDirection.z);

		if (leftStickAngle < 0.f)
			leftStickAngle += 3.14f * 2.f;

		leftStickAngle = glm::degrees(leftStickAngle);
	}
	//cout << "leftStickAngle = " << leftStickAngle << endl;

	for (auto &i : myAbj.heroObjects)
	{
		for (auto &j : myAbj.frustumObjs)
		{
			if (i == j->name->val_s)
			{
				currentSpeed = 0.f;
				j->r->val_3.y = myAbj.leftStickAnglePrev;

				if (myAbj.wTgl || myAbj.aTgl || myAbj.sTgl || myAbj.dTgl)
				{
					currentSpeed = runSpeed;
					j->r->val_3.y = leftStickAngle;
					myAbj.leftStickAnglePrev = leftStickAngle;
				}

				if (leftStickAngle != 0.f)
				{
					currentSpeed = runSpeed;
					j->r->val_3.y = leftStickAngle;
					myAbj.leftStickAnglePrev = leftStickAngle;
				}
			}
		}
	}

	/* RIGHT STICK */
	float stickSpeed = 1.f;
	myAbj.selCamLi->r->val_3.x -= stickSpeed * axes[2];
	myAbj.selCamLi->r->val_3.y = glm::clamp(myAbj.selCamLi->r->val_3.y - stickSpeed * -axes[3], -80.f, -2.f);

	int buttonCt; //14
	const unsigned char *controllerButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCt);

	//float autoBunnyHopPrevent = (float)((double)GetTickCount() - (double)myAbj.jumpTimer) / 1000.f; //

	if (controllerButtons[0] == GLFW_PRESS)
	{
		if (myAbj.isInAir == 0)
			//if (myAbj.isInAir == 0 && autoBunnyHopPrevent >= .5f) // prevents auto bunny hop
		{
			currrentUpwardsSpeed = jumpPower;
			myAbj.isInAir = 1;

			myAbj.jumpTimer = GetTickCount();
		}
	}

	for (auto &i : myAbj.heroObjects)
	{
		for (auto &j : myAbj.frustumObjs)
		{
			if (i == j->name->val_s)
			{
				float distance = -currentSpeed * myAbj.deltaFrameTime;
				float dx = distance * glm::sin(glm::radians(j->r->val_3.y));
				float dz = distance * glm::cos(glm::radians(j->r->val_3.y));

				j->tx->val_f += dx;
				j->tz->val_f += dz;

				myAbj.selCamLi->setDirty();

				/* FALLING AKA GRAVITY RELATED */
				currrentUpwardsSpeed += gravity * myAbj.deltaFrameTime;
				j->ty->val_f += currrentUpwardsSpeed * myAbj.deltaFrameTime;

				if (j->ty->val_f < 0.f)
				{
					currrentUpwardsSpeed = 0.f;
					myAbj.isInAir = 0;
					j->ty->val_f = terrainHeight;

					//myAbj.jumpTimer = GetTickCount();
				}
			}
		}
	}
}

int findAnimPosition(float animTime, MultiAttr multi)
{
	for (int i = 0; i < multi.keys.size() - 1; i++)
	{
		if (animTime < (float)multi.keys[i + 1].frame)
		{
			return i;
		}
	}

	return 0;
}

void timeBasedStuff()
{
	long currentFrameTime = GetTickCount();
	myAbj.deltaFrameTime = (currentFrameTime - myAbj.lastFrameTime) / 1000.f;
	myAbj.lastFrameTime = currentFrameTime;

	//start timer at frame 0
	//start timer at frame 60
	float TicksPerSecond = 30.f;
	//float TicksPerSecond = 60.f;
	//float TicksPerSecond = 120.f;
	float animStart = 0;
	float animEnd = 120;

	//float animationTimeFrames = fmod((myAbj.myFSQ->animationTime0 * TicksPerSecond) + animStart, animEnd);
	float animationTimeFrames = (myAbj.myFSQ->animationTime0 * TicksPerSecond) + animStart;
	//float animationTime01 = animationTimeFrames / animEnd;

	//cout << fixed << animationTimeFrames << endl;
	//cout << fixed << animationTimeFrames << endl;

	if (animationTimeFrames >= animEnd - .5f) {
		myAbj.myFSQ->animationTime0 = 0.f;

		if (myAbj.dieTgl) {
			myAbj.dieTgl = 0;
		}
	}

	for (int i = 0; i < myAbj.allObj.size(); i++)
	{
		for (int j = 0; j < myAbj.allObj[i]->multiObj.size(); j++)
		{
			if (myAbj.allObj[i]->multiObj[j]->keys.size() >= 2)
			{
				int posIdx = findAnimPosition(animationTimeFrames, *myAbj.allObj[i]->multiObj[j]);
				int nextPosIdx = posIdx + 1;

				float start = myAbj.allObj[i]->multiObj[j]->keys[posIdx].val;
				float end = myAbj.allObj[i]->multiObj[j]->keys[nextPosIdx].val;
				float delta = end - start;

				float deltaTime = (float)(myAbj.allObj[i]->multiObj[j]->keys[nextPosIdx].frame - myAbj.allObj[i]->multiObj[j]->keys[posIdx].frame);
				float factor = (animationTimeFrames - (float)myAbj.allObj[i]->multiObj[j]->keys[posIdx].frame) / deltaTime;
				factor = glm::clamp(factor, 0.f, 1.f);

				float out2 = start + factor * delta;
				//float out2 = glm::lerp(myLerper.lerpRangeStart, myLerper.lerpRangeEnd, delta);


				//cout << "delta / deltaTime = " << delta << " " << deltaTime << endl;
				//cout << fixed << myAbj.allObj[i]->name->val_s << " " << myAbj.allObj[i]->multiObj[j]->name << " " << animationTimeFrames << " " << animationTime01 << " " << posIdx << " " << nextPosIdx << " " << out2 << endl;

				if (myAbj.allObj[i]->multiObj[j]->name == "dieMsgAlpha") {
					if (myAbj.dieTgl) {
						cout << "setting dieMsgAlpha" << endl;
						myAbj.allObj[i]->multiObj[j]->val_f = out2;

						if (animationTimeFrames > 120.f - .1f) {
							myAbj.dieTgl = 0;
						}

					}
				}

				else {
					myAbj.allObj[i]->multiObj[j]->val_f = out2;
				}

			}
		}
	}

	//increase both animTime0 and 1 at same rate

	for (auto &i : myAbj.allObj)
	{
		if (i->name->val_s == "tube")
		{
			i->animationTime0 += myAbj.deltaFrameTime;
			i->animationTime1 += myAbj.deltaFrameTime;

			i->blendingTime -= myAbj.deltaFrameTime / myAbj._blendTimeMult;

			if (i->blendingTime <= 0.f)
				i->animationTime0 = i->animationTime1;
		}

		else if (i->name->val_s == "animatedCylinder")
		{
			i->animationTime0 += myAbj.deltaFrameTime;
		}

		//else if (i->name->val_s == "simpleSkinnedRect")
		//{
		//	i->animationTime0 += myAbj.deltaFrameTime;
		//	//cout << "deltaFrameTime = " << myAbj.deltaFrameTime << endl;
		//	//cout << "i->animationTime0 = " << i->animationTime0 << endl;
		//}

		//else if (i->name->val_s == "pCube1")
		//{
		//	i->animationTime0 += myAbj.deltaFrameTime;
		//	//cout << "deltaFrameTime = " << myAbj.deltaFrameTime << endl;
		//	//cout << "i->animationTime0 = " << i->animationTime0 << endl;
		//}

		//else if (i->debugSkel->val_b)
		//{
		//	i->animationTime0 += myAbj.deltaFrameTime;
		//}

		i->animationTime0 += myAbj.deltaFrameTime;
	}

	myAbj.dudvTime = (currentFrameTime - myAbj.dudvStartTime) / 1000.f;
	float waveSpeed = .005f;
	myAbj.dudvTime *= waveSpeed;

	if (myAbj.dudvTime >= 1.f || myAbj.dudvTime < 0.f)
		myAbj.dudvStartTime = currentFrameTime;

	if (myAbj.mpfTgl)
		mpfTimerStart();

	//cout << "dudvTime = " << myAbj.dudvTime << endl;
	//cout << "teapotTurnTime = " << myAbj.teapotTurnTime << endl;
}

void setRenderParams_GLApi(string cullFaceDir)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CCW); //openGL default
	//glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_CULL_FACE);

	if (cullFaceDir == "back")
		glCullFace(GL_BACK);

	else if (cullFaceDir == "front")
		glCullFace(GL_FRONT);
}

void renderFrame()
{
	timeBasedStuff();

	if (!myAbj.fboReady)
		myAbj.fboReady = fboPrep();

	if (myAbj.selCamLi->camLiType->val_s == "THIRD")
	{
		moveByHand_free(); //
		//moveByHand_strafe();
	}

	/* MVPGET / VAO LOAD */
	if (myAbj.stereoTgl)
	{
		for (auto &i : myAbj.allCamLi)
		{
			if (i->camLiTypeGet("cam") && i == myAbj.selCamLi)
			{
				glm::vec3 targ0_stored = i->targO;

				if (myAbj.stereoLR == 0)
				{
					i->targO += myAbj.selCamLi->rightO * myAbj.stereoSep * (float)myAbj.stereoSwitchLR;
					VMup(i);
					//i->targO += myAbj.selCamLi->rightO * -.3f;
					i->targO = targ0_stored;
				}

				if (myAbj.stereoLR == 1)
				{
					i->targO += myAbj.selCamLi->rightO * -myAbj.stereoSep * (float)myAbj.stereoSwitchLR;
					VMup(i);
					//i->targO += myAbj.selCamLi->rightO * .3f;
					i->targO = targ0_stored;
				}
			}
		}
	}

	else
	{
		for (auto &i : myAbj.allCamLi)
		{
			if (i->camLiTypeGet("cam") && i == myAbj.selCamLi)
			{
				if (i->dirtyVM)
					VMup(i);
			}
		}
	}

	for (auto &i : myAbj.allObj)
	{
		//if (i->type != "SELRECT" && i->type != "TXT")
		{
			//if (!i->gizSideObj && i->name->val_s != "pivot")
			{
				if (searchUp(i))
					i->mvpGet();
			}
		}

		if (i->dupeStenFix != "999")
			dupeStenFix_check(i);

		i->VAO_load();
	}

	if (myAbj.matchCamera)
	{
		//myAbj.selCam->MM = glm::mat4(0.036636, 0.000000, 0.999329, 0.000000, 0.367410, 0.929961, -0.013470, 0.000000, -0.929337, 0.367657, 0.034070, 0.000000, -24.934433, 7.472488, 0.453848, 1.000000);
		//myAbj.selCam->VM = glm::mat4(0.036636, 0.367410, -0.929337, 0.000000, 0.000000, 0.929961, 0.367657, 0.000000, 0.999329, -0.013470, 0.034070, 0.000000, 0.459960, 2.218156, -25.935266, 1.000000);

		//myAbj.selCamLi->MM = glm::mat4(0.707107, 0.000000, -0.707107, 0.000000, -0.235702, 0.942809, -0.235702, 0.000000, 0.666667, 0.333333, 0.666667, 0.000000, 20.000000, 10.000000, 20.000000, 1.000000);
		//myAbj.selCamLi->VM = glm::mat4(0.707107, -0.235702, 0.666667, 0.000000, 0.000000, 0.942809, 0.333333, 0.000000, -0.707107, -0.235702, 0.666667, 0.000000, 0.000000, 0.000000, -30.000002, 1.000000);
		//myAbj.selCamLi->PM = glm::mat4(2.144507, 0.000000, 0.000000, 0.000000, 0.000000, 2.144507, 0.000000, 0.000000, 0.000000, 0.000000, -1.000020, -1.000000, 0.000000, 0.000000, -0.020000, 0.000000);

	}

	/* FRUSTUM CULL */
	myAbj.frustumObjs.clear();

	for (auto &i : myAbj.allObj)
		myAbj.frustumObjs.push_back(i); //TEMP OVERRIDE CULLING

	//frustumCullCPU("spherical");
	//frustumCullCPU("AABB"); //

	//for (auto &i : myAbj.allObj)
	//{
	//	if (i->type != "SELRECT" && i->type != "TXT" && searchUp(i))
	//	{
	//		//cout << "i->type / name frustumObjs 0 = " << i->type << " " << i->name->val_s << endl;
	//		myAbj.frustumObjs.push_back(i);
	//	}
	//}

	/////////////////////
	//calc bone movement
	////////////////////
	for (auto &i : myAbj.frustumObjs)
	{
		//if (i->type == "OBJ" && (i->anim->val_b || (i->debugSkel->val_b)))
		//{
		//	i->boneTransformGrpABJ(); ///////
		//}

		//if (i->type == "OBJ" && (i->anim->val_b || (i->debugSkel->val_b)))
		//{
		//	i->boneTransformGrpABJ(); ///////
		//}

		if (i->type == "OBJ" && i->anim->val_b && myAbj.startupSceneName == "fbxAnimTest")
		{
			i->boneTransformGrpABJ_solo(); ///////
		}

		if (i->type == "OBJ" && i->animAI->val_b && myAbj.startupSceneName == "AItest")
		{
			i->boneTransformGrp_AI(i->linkedGrp, i->m_NumBones);
		}
	}

	/* SHADOWMAP */
	for (auto &i : myAbj.allCamLi)
	{
		if (i->camLiTypeGet("light"))
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT);
			glCullFace(GL_BACK); //

			//if (i->dirtyShadow) //
			{
				writeShadow(i);
			}
		}
	}

	//if (myAbj.UBO_light_needsUp) //
	uboUp();

	//removed from GL core profile but necc for UBO?
	//glEnableClientState(GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV);
	//glEnableClientState(GL_ELEMENT_ARRAY_UNIFIED_NV);
	glEnableClientState(GL_UNIFORM_BUFFER_UNIFIED_NV);

	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.bgN.fbo0);
	glViewport(0, 0, myAbj.width, myAbj.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setRenderParams_GLApi("back");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum DrawBuffersBG_0[] = { GL_COLOR_ATTACHMENT0 };
	GLenum DrawBuffersBG_1[] = { GL_COLOR_ATTACHMENT1 };

	glNamedFramebufferDrawBuffers(myAbj.bgN.fbo0, 1, DrawBuffersBG_0);

	glDisable(GL_DEPTH_TEST);
	glUseProgram2("pSky");
	myAbj.myFSQ->render(); //sky
	glEnable(GL_DEPTH_TEST);

	if (myAbj.selCamLi->gridV)
	{
		glUseProgram2("pGrid");

		for (auto &i : myAbj.allGrid)
		{
			if (i->type == "GRID" && gridMatch(i))
				i->render();
		}
	}

	glNamedFramebufferDrawBuffers(myAbj.bgN.fbo0, 1, DrawBuffersBG_1);

	//

	bbViz();

	if (myAbj.wireOverTgl)
	{
		for (auto &i : myAbj.frustumObjs)
		{
			if (i->type == "OBJ" && !i->bb->val_b)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

				glUseProgram2("pWireframe");
				i->render();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	}

	for (auto &i : myAbj.frustumObjs) //RENDER OBJS ONLY
	{
		if (i->selected && i->type == "OBJ" && !i->bb->val_b)
		{
			if (myAbj.selMode == "OBJ")
			{
				glClearStencil(0);
				glClear(GL_STENCIL_BUFFER_BIT);
				glEnable(GL_STENCIL_TEST);

				/* RENDER MESH */
				glStencilFunc(GL_ALWAYS, 1, 0xFF); // -1
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

				if (i->anim->val_b)
					glUseProgram2("pStencilGeoAnim");

				else
					glUseProgram2("pStencilGeo");

				i->render();

				/* THICK WIRE VERSION */
				glStencilFunc(GL_NOTEQUAL, 1, -1);
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
				glLineWidth(7.f);

				glCullFace(GL_BACK);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

				if (i->anim->val_b)
					glUseProgram2("pStencilHiAnim");

				else
					glUseProgram2("pStencilHi");

				i->render();

				glDisable(GL_STENCIL_TEST);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glLineWidth(1.f);
			}
		}
	}

	//REVERSE DEPTH FOR SSR
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.depthRevN.fbo0);
	glViewport(0, 0, myAbj.depthRevN.width, myAbj.depthRevN.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setRenderParams_GLApi("front");
	glDisable(GL_BLEND);

	glUseProgram2("pDepthRev");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b && !i->anim->val_b)
			i->render();
	}

	glUseProgram2("pDepthRevAnim");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b && i->anim->val_b)
			i->render();
	}

	GBuffer_BOIT(); // 

	if (myAbj.brushOutlineUpB)
		brushOutlineUp();

	//if (myAbj.paintMode)
	//{
	//	paintSomething0();
	//	myAbj.cursorName = "ROUND_BRUSH";
	//}

	//else
	//	myAbj.cursorName = "cursorReg";

	myAbj.cursorName = "cursorReg";

	/* COMP */
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	postFX();
	overlay2D();
}

void GBuffer_BOIT()
{
	/* N_VS / RUFF FOR ALL OBJECTS FOR SSR */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.normalRuffN.fbo0);
	glViewport(0, 0, myAbj.normalRuffN.width, myAbj.normalRuffN.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setRenderParams_GLApi("back");
	glDisable(GL_BLEND);

	glUseProgram2("pNormalRuffAnim");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b && i->anim->val_b)
			i->render();
	}

	glUseProgram2("pNormalRuff");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b && !i->anim->val_b)
			i->render();
	}

	/* OPAQUE PASS */
	/* ALPHA TESTING in opaque pass shader (for alpha == 1.f) */
	//if (col.a <= threshold)
	//    discard;

		/* G BUFFER */
	GLenum DrawBuffersOpaque[] =
	{
		GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6,
	};

	glNamedFramebufferDrawBuffers(myAbj.gBufN.fbo0, 7, DrawBuffersOpaque);

	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.gBufN.fbo0);
	glViewport(0, 0, myAbj.gBufN.width, myAbj.gBufN.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setRenderParams_GLApi("back");
	glDisable(GL_BLEND);

	/* RENDER ANIMATED / STATIC OPAQUE OBJS */
	glUseProgram2("pGBufferAnim");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b && i->anim->val_b)
		{
			if (i->Ko->val_f == 1.f && i->alphaM->val_s == "BLANK_ALPHA")
				i->render();
		}
	}

	glUseProgram2("pGBuffer");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b && !i->anim->val_b)
		{
			if (i->Ko->val_f == 1.f && i->alphaM->val_s == "BLANK_ALPHA")
				i->render();
		}
	}

	GLenum DrawBuffersTransp[] = { GL_COLOR_ATTACHMENT7 };
	glNamedFramebufferDrawBuffers(myAbj.gBufN.fbo0, 1, DrawBuffersTransp);

	//glDepthMask(GL_FALSE); //read depth from opaque pass but dont write to it

	float clearColor0[4] = { 0.f, 0.f, 0.f, 0.f };
	////float clearColor1[4] = { 1.f, 1.f, 1.f, 1.f };
	glClearNamedFramebufferfv(myAbj.gBufN.fbo0, GL_COLOR, 0, clearColor0);
	////glClearNamedFramebufferfv(myAbj.gBufN.fbo0, GL_COLOR, 1, clearColor1);

	////glEnable(GL_BLEND);
	////glBlendEquation(GL_FUNC_ADD);
	////glBlendFunci(0, GL_ONE, GL_ONE);
	////glBlendFunci(1, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);

	glUseProgram2("pTransp");

	for (auto &i : myAbj.frustumObjs)
	{
		if (i->type == "OBJ" && !i->bb->val_b)
		{
			if (i->Ko->val_f < 1.f || i->alphaM->val_s != "BLANK_ALPHA")
				i->render();
		}
	}

}

void postFX()
{
	// /* BILLBOARD */
	//glBindFramebuffer(GL_FRAMEBUFFER, myAbj.billN.fbo0);
	//glViewport(0, 0, myAbj.billN.width, myAbj.billN.height);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glUseProgram2("pBill");
	//myAbj.myFSQ->render();

	//glBufferAddressRangeNV(GL_UNIFORM_BUFFER_ADDRESS_NV, 0, myAbj.uboDebug_64, sizeof(DebugData)); // !!!!!!!

	/* SSAO */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.ssaoN.fbo0);
	glViewport(0, 0, myAbj.ssaoN.width, myAbj.ssaoN.height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram2("pSSAO_32");
	myAbj.myFSQ->render();

	glMakeTextureHandleNonResidentARB(myAbj.ssaoGaussN.tex1_64);
	glUseProgram2("pGauss");
	myAbj.ssaoGaussN.tex1_64 = glGetTextureHandleARB(gaussianBlur(myAbj.ssaoN, myAbj.ssaoGaussN, 1));
	glMakeTextureHandleResidentARB(myAbj.ssaoGaussN.tex1_64);

	/* DEFERRED LIGHTING */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.defN.fbo0);
	glViewport(0, 0, myAbj.defN.width, myAbj.defN.height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram2("pDef");
	myAbj.myFSQ->render();

	/* TRANSP COMPOSITE */
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram2("pTranspComp");
	myAbj.myFSQ->render();
	glDisable(GL_BLEND);

	/* LUMA INIT */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.lumaInitN.fbo0);
	glViewport(0, 0, myAbj.lumaInitN.width, myAbj.lumaInitN.height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram2("pLumaInit");
	myAbj.myFSQ->render();

	/* LUMA ADAPTIVE */
	//if (myAbj.stereoTgl)
	//{
	//	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.lumaAdaptN[myAbj.currLum].fbo0);
	//	glViewport(0, 0, myAbj.lumaAdaptN[myAbj.currLum].width, myAbj.lumaAdaptN[myAbj.currLum].height);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	glUseProgram2("pLumaAdapt");
	//	myAbj.myFSQ->render();
	//	glGenerateTextureMipmap(myAbj.lumaAdaptN[myAbj.currLum].tex0_32);
	//}

	//else
	//{
	//	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.lumaAdaptN[myAbj.currLum].fbo0);
	//	glViewport(0, 0, myAbj.lumaAdaptN[myAbj.currLum].width, myAbj.lumaAdaptN[myAbj.currLum].height);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	glUseProgram2("pLumaAdapt");
	//	myAbj.myFSQ->render();
	//	glGenerateTextureMipmap(myAbj.lumaAdaptN[myAbj.currLum].tex0_32);
	//}


	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.lumaAdaptN[myAbj.currLum].fbo0);
	glViewport(0, 0, myAbj.lumaAdaptN[myAbj.currLum].width, myAbj.lumaAdaptN[myAbj.currLum].height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram2("pLumaAdapt");
	myAbj.myFSQ->render();
	glGenerateTextureMipmap(myAbj.lumaAdaptN[myAbj.currLum].tex0_32);

	/* BLOOM + COLOR */
	bloomRender();

	/* TONEMAP */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.tonemapN.fbo0);
	glViewport(0, 0, myAbj.tonemapN.width, myAbj.tonemapN.height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram2("pTonemap");
	myAbj.myFSQ->render();

	/* FXAA */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.fxaaN.fbo0);
	glViewport(0, 0, myAbj.fxaaN.width, myAbj.fxaaN.height);
	glClear(GL_COLOR_BUFFER_BIT);
	myAbj.texelSize = glm::vec2(1.f / myAbj.fxaaN.width, 1.f / myAbj.fxaaN.height);
	glUseProgram2("pFxaa");
	myAbj.myFSQ->render();

	/* SSR */
	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.ssrN.fbo0);
	glViewport(0, 0, myAbj.ssrN.width, myAbj.ssrN.height);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //
	glUseProgram2("pSSR");
	myAbj.myFSQ->render();
	glDisable(GL_BLEND);

	if (myAbj.stereoTgl)
	{
		/* OUTPUT STEREO LR */
		glBindFramebuffer(GL_FRAMEBUFFER, myAbj.stereoN[myAbj.stereoLR].fbo0);
		glViewport(0, 0, myAbj.stereoN[0].width, myAbj.stereoN[myAbj.stereoLR].height);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram2("pStereoPost");
		myAbj.myFSQ->render();

		/* FINAL */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, myAbj.width, myAbj.height);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram2("pFinalStereo");
		myAbj.myFSQ->render();
	}

	else
	{
		/* FINAL */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, myAbj.width, myAbj.height);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram2("pFinal");
		myAbj.myFSQ->render();
	}

	myAbj.currLum = !myAbj.currLum;
	myAbj.stereoLR = !myAbj.stereoLR;
}

void overlay2D()
{
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	if (myAbj.selB == myAbj.selCamLi) //REZGATE
	{
		glm::vec2 center(myAbj.width / 2, myAbj.height / 2);
		glm::vec2 xyHalf(725 / 2, 400 / 2); //

		myAbj.rezGate_RU = toNDC(center + xyHalf, "REG");
		myAbj.rezGate_LD = toNDC(center - xyHalf, "REG");
	}
	
	if (!myAbj.disableSelRect && myAbj.lmbTgl && !myAbj.altTgl) //SELRECT
	{
		//cout << "mmbTgl in selrect = " << myAbj.mmbTgl << endl;

		myAbj.selRect_LD = toNDC(myAbj.rayP, "SELRECT");
		myAbj.selRect_RU = toNDC(myAbj.pMouseNew, "SELRECT");

		glUseProgram2("pSelRect");
		myAbj.mySelRect->render();
	}

	//TXT
	if (myAbj.mpfTgl || myAbj.gizSpaceTgl || myAbj.statsTgl)
	{
		if (myAbj.dieTgl)
		{
			glUseProgram2("pTxtDie");

			myAbj.myTxt->txt2D = myAbj.dieRollChoice.c_str();
			//myAbj.myTxt->txt2D = "100";
			//myAbj.myTxt->txt2D = "10";
			//myAbj.myTxt->txt2D = "1";

			for (auto &i : myAbj.GLDataSh)
			{
				if (i.obj == myAbj.myTxt)
					glNamedBufferSubData(i.VBO_P, 0, (GLsizei)strlen(myAbj.myTxt->txt2D), myAbj.myTxt->txt2D);
			}

			//myAbj.myTxt->txtOrigin = glm::vec2(0.f, 0.f);
			myAbj.myTxt->txtOrigin = glm::vec2(-.9f, 0.f);

			myAbj.myTxt->render();
		}

		glUseProgram2("pTxt");

		if (myAbj.mpfTgl)
		{
			myAbj.myTxt->txt2D = myAbj.mpf.c_str();

			for (auto &i : myAbj.GLDataSh)
			{
				if (i.obj == myAbj.myTxt)
					glNamedBufferSubData(i.VBO_P, 0, (GLsizei)strlen(myAbj.myTxt->txt2D), myAbj.myTxt->txt2D);
			}

			myAbj.myTxt->txtOrigin = glm::vec2(.8f, -.9f);
			myAbj.myTxt->render();
		}

		if (myAbj.gizSpaceTgl) //gizSpace
		{
			if (myAbj.gizSpace == "local") myAbj.myTxt->txt2D = "local";
			else if (myAbj.gizSpace == "world") myAbj.myTxt->txt2D = "world";

			for (auto &i : myAbj.GLDataSh)
			{
				if (i.obj == myAbj.myTxt)
					glNamedBufferSubData(i.VBO_P, 0, (GLsizei)strlen(myAbj.myTxt->txt2D), myAbj.myTxt->txt2D);
			}

			myAbj.myTxt->txtOrigin = glm::vec2(.9f, -.9f);
			myAbj.myTxt->render();
		}

		if (myAbj.statsTgl)
		{
			auto vertsOnObj = 0; auto edgesOnObj = 0; auto facesOnObj = 0;

			for (auto &i : myAbj.allObj)
			{
				if (i->selected)
				{
					vertsOnObj += i->vertsOnObj;
					//edgesOnObj += i->edgesOnObj;
					//facesOnObj += i->facesOnObj;
				}
			}

			stringstream ss;
			ss << "v " << vertsOnObj << " e " << edgesOnObj << " f " << facesOnObj;

			auto selStats = ss.str();
			myAbj.myTxt->txt2D = selStats.c_str();

			for (auto &i : myAbj.GLDataSh)
			{
				if (i.obj == myAbj.myTxt)
					glNamedBufferSubData(i.VBO_P, 0, (GLsizei)strlen(myAbj.myTxt->txt2D), myAbj.myTxt->txt2D);
			}

			myAbj.myTxt->txtOrigin = glm::vec2(.5f, .85f);
			myAbj.myTxt->render();
		}
	}

	////CURSOR
	//if (myAbj.cursorUse)
	//{
	//	glUseProgram2("pCursor");
	//	myAbj.myFSQ->render();
	//}
}

bool gridMatch(shared_ptr<Object> obj)
{
	bool found = 0;
	auto gridName = obj->name->val_s;
	auto orthoType = myAbj.selCamLi->orthoType->val_s;

	if (myAbj.selCamLi->camLiType->val_s != "ORTHO" || myAbj.selCamLi->orthoFree->val_b)
	{
		if (gridName == "grid_top")
			found = 1;

		else if (gridName == "grid_topB")
			found = 1;

		else if (gridName == "grid_left")
			found = 1;

		else if (gridName == "grid_leftB")
			found = 1;
	}

	else
	{
		if ((gridName == "grid_front" && (orthoType == "BACK" || orthoType == "FRONT"))
			|| (gridName == "grid_left" && (orthoType == "LEFT" || orthoType == "RIGHT"))
			|| (gridName == "grid_top" && (orthoType == "BOTTOM" || orthoType == "TOP")))

			found = 1;

		else if ((gridName == "grid_frontB" && (orthoType == "BACK" || orthoType == "FRONT"))
			|| (gridName == "grid_leftB" && (orthoType == "LEFT" || orthoType == "RIGHT"))
			|| (gridName == "grid_topB" && (orthoType == "BOTTOM" || orthoType == "TOP")))

			found = 1;
	}

	return found;
}

void dupeStenFix_check(shared_ptr<Object> obj)
{
	for (auto &i : myAbj.allObj)
	{
		if (obj->v->val_b && obj->dupeStenFix == i->name->val_s)
		{
			if (obj->MM == i->MM)
				i->v->val_b = 0;

			else
			{
				obj->dupeStenFix = "999";
				i->v->val_b = 1;
			}
		}
	}
}

void setLightsDirty()
{
	for (auto &i : myAbj.allCamLi)
	{
		if (i->v->val_b && i->type == "CAMLI" && i->camLiTypeGet("light"))
			i->setDirty();
	}
}

void resize()
{
	glViewport(0, 0, myAbj.width, myAbj.height);
	myAbj.aspect = (float)myAbj.width / myAbj.height;
	myAbj.aspectSide = (0.f) ? 1.f : myAbj.gizSideS.x / myAbj.gizSideS.y;

	//cout << "myAbj.width = " << myAbj.width << endl;
	//cout << "myAbj.height = " << myAbj.height << endl;

	if (myAbj.selCamLi->camLiTypeGet("dirOrtho"))
		myAbj.selCamLi->PM = glm::ortho(-myAbj.selCamLi->orthoZoom->val_f * myAbj.aspect, myAbj.selCamLi->orthoZoom->val_f * myAbj.aspect, -myAbj.selCamLi->orthoZoom->val_f, myAbj.selCamLi->orthoZoom->val_f, myAbj.selCamLi->nearClip->val_f, myAbj.selCamLi->farClip->val_f);

	else
		myAbj.selCamLi->PM = glm::perspective(glm::radians(myAbj.selCamLi->fov->val_f), myAbj.aspect, myAbj.selCamLi->nearClip->val_f, myAbj.selCamLi->farClip->val_f);

	myAbj.PMinv_cube = glm::inverse(glm::perspective(glm::radians(myAbj.selCamLi->fov->val_f), myAbj.aspect, myAbj.selCamLi->nearClip->val_f, myAbj.selCamLi->farClip->val_f));
	myAbj.PMgizSide = glm::perspective(glm::radians(50.f), myAbj.aspectSide, .001f, 1000.f);

	myAbj.aspectXYZ.x = (myAbj.aspect > 1.f) ? myAbj.aspect : 1.f;
	myAbj.aspectXYZ.y = (myAbj.aspect > 1.f) ? 1.f : myAbj.aspect;
	myAbj.aspectXYZ.z = 1.f;
		
	if (myAbj.fboReady)
		resizeTexClearMem();

	myAbj.selCamLi->setDirty();
}

void PMupOrtho(shared_ptr<Object> obj)
{
	//refresh PM because of selCamLi orthoZoom change
	myAbj.aspect = (float)myAbj.width / myAbj.height;
	myAbj.aspectSide = myAbj.gizSideS.x / myAbj.gizSideS.y;

	obj->PM = glm::ortho(-obj->orthoZoom->val_f * myAbj.aspect, obj->orthoZoom->val_f * myAbj.aspect, -obj->orthoZoom->val_f, obj->orthoZoom->val_f, obj->nearClip->val_f, obj->farClip->val_f);

	obj->buildFrustumPlanes();
}

void VMup(shared_ptr<Object> obj) // WITH barTempStuff
{
	glm::mat4 R = glm::yawPitchRoll(glm::radians(obj->r->val_3.x), glm::radians(obj->r->val_3.y), 0.f);
	//glm::mat4 R = glm::yawPitchRoll(glm::radians(obj->r->val_3.x), glm::radians(-45.f), 0.f);
	printGLM4x4(R, "R = ");
	cout << "obj rot = " << glm::to_string(obj->r->val_3) << endl;

	//cout << 

	//else if (obj->camLiType->val_s != "DIR")
	if (obj->camLiType->val_s == "PERSP" || obj->camLiType->val_s == "ORTHO")
	{
		glm::vec3 tempT = glm::vec3(R * glm::vec4(0.f, 0.f, obj->distO, 0.f)) + obj->targO;
		obj->tx->val_f = tempT.x;
		obj->ty->val_f = tempT.y;
		obj->tz->val_f = tempT.z;

		//cout << "camName / R " << obj->name->val_s << " " << glm::to_string(R) << endl;
		//cout << "camName / piv " << obj->name->val_s << " " << glm::to_string(glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f)) << endl;
		//cout << "camName / dist0 " << obj->name->val_s << " " << obj->distO << endl;
		//cout << "camName / targO " << obj->name->val_s << " " << glm::to_string(obj->targO) << endl;

		obj->piv->val_3 = glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f);

		//cout << "name / piv " << obj->name->val_s << " " << glm::to_string(obj->piv->val_3) << endl;

		obj->lookO = glm::normalize(obj->targO - glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f));
		obj->rightO = glm::normalize(glm::cross(obj->lookO, myAbj.upWorld));
		obj->upO = glm::cross(obj->rightO, obj->lookO);

		obj->VM = glm::lookAt(glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f), obj->targO, obj->upO);
		obj->VM *= glm::rotate(glm::mat4(1.f), glm::radians(obj->r->val_3.z), glm::vec3(0.f, 0.f, 1.f));
	}

	else if (obj->camLiType->val_s == "THIRD")
	{
		glm::vec3 playerPos, playerRot;

		for (auto &i : myAbj.frustumObjs)
		{
			if (i->name->val_s == myAbj.heroObj)
			{
				cout << "found heroObj !!!!!!!! : " << i->name->val_s << endl;

				playerPos = glm::vec3(i->tx->val_f, i->ty->val_f, i->tz->val_f);
				playerRot = i->r->val_3;
			}
		}

		playerPos.y = 0.f;

		obj->targO = playerPos;

		glm::vec3 tempT = glm::vec3(R * glm::vec4(0.f, 0.f, obj->distO, 0.f)) + obj->targO;
		obj->tx->val_f = tempT.x;
		obj->ty->val_f = tempT.y;
		obj->tz->val_f = tempT.z;

		obj->piv->val_3 = glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f);

		obj->lookO = glm::normalize(obj->targO - glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f));
		obj->rightO = glm::normalize(glm::cross(obj->lookO, myAbj.upWorld));
		obj->upO = glm::cross(obj->rightO, obj->lookO);

		obj->VM = glm::lookAt(glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f), obj->targO, obj->upO);
		obj->VM *= glm::rotate(glm::mat4(1.f), glm::radians(obj->r->val_3.z), glm::vec3(0.f, 0.f, 1.f));

		obj->prevTargO = obj->targO;
	}

	//update VMgizSide if this object is the selcam
	if (obj == myAbj.selCamLi)
	{
		// UPDATE VM for GIZSIDE
		auto R = glm::yawPitchRoll(glm::radians(obj->r->val_3.x), glm::radians(obj->r->val_3.y), 0.f);
		auto posG = glm::vec3(R * glm::vec4(0.f, 0.f, myAbj.gizSideS.z, 0.f));
		auto lookG = glm::normalize(-posG);
		auto rightG = glm::cross(lookG, myAbj.upWorld);
		auto upG = glm::cross(rightG, lookG);

		myAbj.VMgizSide = glm::lookAt(posG, glm::vec3(0.f), upG);
	}

	obj->dirtyVM = 0;

	if (obj->camLiTypeGet("light"))
		myAbj.UBO_light_needsUp = 1;

	if (myAbj.myFSQ->clearBehav->val_s == "OnVMup")
	{
		cout << "baking (and clearing) canvas on VMup" << endl;

		myAbj.bakeNow = 1;
		//clearCanvas();
	}

	myAbj.selCamLi->buildFrustumPlanes();
}

void mpfTimerStart() //DEBUG - move to chrono in its own struct
{
	//240fps = 4.166
	//120fps = 8.333
	//60fps = 16.667
	//30fps = 33.333

	myAbj.tick_frames++;
	myAbj.tick_new = GetTickCount();
	myAbj.tick_diff = myAbj.tick_new - myAbj.tick_old;

	//cout << "tickDiff = " << myAbj.tick_diff << endl;

	if (myAbj.tick_diff >= 1000)
	{
		stringstream ss;
		ss << fixed << setprecision(3) << 1000.f / myAbj.tick_frames;
		myAbj.mpf = ss.str();

		myAbj.mpfTime = 1000.f / myAbj.tick_frames;
		myAbj.dTime = myAbj.mpfTime * myAbj.myFSQ->adaptTime->val_f * .01f;

		//cout << "myAbj.dTime = " << myAbj.dTime << endl;

		myAbj.tick_frames = 0;
		myAbj.tick_old = myAbj.tick_new;
	}
}

bool searchUp(shared_ptr<Object> obj)
{
	searchUpRecursive(obj);

	if (myAbj.searchB)
		return 1;

	return 0;
}

void searchUpRecursive(shared_ptr<Object> obj)
{
	if (obj->v->val_b)
	{
		if (obj->parentTo)
		{
			if (obj->parentTo->v->val_b)
			{
				bool found = 0;
				shared_ptr<Object> tempObj;

				for (auto &i : myAbj.allObj)
				{
					if (obj->parentTo->parentTo == i)
					{
						found = 1;
						tempObj = i;

						continue;
					}
				}

				if (!found)
					myAbj.searchB = 1; //parent to has no parents and the parent is visible

				else
					searchUpRecursive(tempObj); //keep searching
			}

			else
				myAbj.searchB = 0; //the parent is not visible
		}

		else
			myAbj.searchB = 1; //has no parents and is visible
	}

	else
		myAbj.searchB = 0;
}

void gizShow(string gizTypeShow)
{
	if (myAbj.selB)
	{
		for (auto &i : myAbj.allObj)
		{
			if (gizTypeShow == "T")
			{
				if (i->type == "GIZ_CIRC") i->v->val_b = 0;
				else if (i->type == "GIZ_CIRC_HALF") i->v->val_b = 0;
				else if (i->type == "GIZ_CONE") i->v->val_b = 1;
				else if (i->type == "GIZ_CUBE") i->v->val_b = 0;
				else if (i->type == "GIZ_DUAL_HANDLE") i->v->val_b = 1;
				else if (i->type == "GIZ_LINE") i->v->val_b = 1;
			}

			else if (gizTypeShow == "R")
			{
				if (i->type == "GIZ_CIRC") i->v->val_b = 1;
				else if (i->type == "GIZ_CIRC_HALF") i->v->val_b = 1;
				else if (i->type == "GIZ_CONE") i->v->val_b = 0;
				else if (i->type == "GIZ_CUBE") i->v->val_b = 0;
				else if (i->type == "GIZ_DUAL_HANDLE") i->v->val_b = 0;
				else if (i->type == "GIZ_LINE") i->v->val_b = 0;
			}

			else if (gizTypeShow == "S")
			{
				if (i->type == "GIZ_CIRC") i->v->val_b = 0;
				else if (i->type == "GIZ_CIRC_HALF") i->v->val_b = 0;
				else if (i->type == "GIZ_CONE") i->v->val_b = 0;
				else if (i->type == "GIZ_CUBE" && i != myAbj.myPivot) i->v->val_b = 1;
				else if (i->type == "GIZ_DUAL_HANDLE") i->v->val_b = 1;
				else if (i->type == "GIZ_LINE") i->v->val_b = 1;
			}
		}

		myAbj.myGizNull->parentTo = myAbj.selB;
		myAbj.myGizNull->v->val_b = 1;
		myAbj.myGizNull->gizType = gizTypeShow;
	}
}

void pivTgl()
{
	if (myAbj.selB && myAbj.selB != myAbj.myPivot)
	{
		myAbj.myPivot->parentTo = myAbj.selB;
		myAbj.myPivot->v->val_b = !myAbj.myPivot->v->val_b;
	}
}

void clearSel()
{
	myAbj.selB = 0;

	for (auto &i : myAbj.allObj)
		i->selected = 0;
}

// Returns a quaternion such that q*start = dest
glm::quat RotationBetweenVectors(vec3 start, vec3 dest)
{
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + .001f)
	{
		// special case when vectors in opposite directions :
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		// This implementation favors a rotation around the Up axis,
		// since it's often what you want to do.
		rotationAxis = glm::cross(vec3(.0f, .0f, 1.f), start);
		if (glm::length2(rotationAxis) < .01f) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(vec3(1.f, 0.f, 0.f), start);

		rotationAxis = glm::normalize(rotationAxis);
		return glm::angleAxis(180.f, rotationAxis);
	}

	// Implementation from Stan Melax's Game Programming Gems 1 article
	rotationAxis = glm::cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);
}

// Returns a quaternion that will make your object looking towards 'direction'.
// Similar to RotationBetweenVectors, but also controls the vertical orientation.
// This assumes that at rest, the object faces +Z.
// Beware, the first parameter is a direction, not the target point !
glm::quat LookAtQuat(glm::vec3 direction, glm::vec3 desiredUp)
{
	if (length2(direction) < .0001f)
		return glm::quat();

	// Recompute desiredUp so that it's perpendicular to the direction
	// You can skip that part if you really want to force desiredUp
	vec3 right = cross(direction, desiredUp);
	desiredUp = cross(right, direction);

	// Find the rotation between the front of the object (that we assume towards +Z,
	// but this depends on your model) and the desired direction
	glm::quat rot1 = RotationBetweenVectors(vec3(0.f, 0.f, -1.f), direction);
	// Because of the 1rst rotation, the up is probably completely screwed up. 
	// Find the rotation between the "up" of the rotated object, and the desired up
	vec3 newUp = rot1 * vec3(0.f, 1.f, 0.f);
	glm::quat rot2 = RotationBetweenVectors(newUp, desiredUp);

	// Apply them
	return rot2 * rot1; // remember, in reverse order.
}