/*
reference:
https://www.gamedev.net/resources/_/technical/general-programming/frustum-culling-r4613
*/

#include "Core.h"
#include "Object.h"

//////////////
/* SETUP (AFTER VMUP) */
//////////////

void Object::BBup() //OBB
{
	//917-555-1234
	bbMin = (pE.empty()) ? glm::vec3(0.f) : pE[0];
	bbMax = (pE.empty()) ? glm::vec3(0.f) : pE[0];

	for (auto &i : pE)
	{
		bbMin = glm::min(i, bbMin);
		bbMax = glm::max(i, bbMax);
	}

	bbSize = bbMax - bbMin;
	//bbCenter = .5f * (bbMin + bbMax);
	//obbMVP = glm::translate(glm::mat4(1.f), bbCenter) * glm::scale(glm::mat4(1.f), bbSize);
}

//void Object::BBup() //OBB
//{
//	bbMin = (pE.empty()) ? glm::vec3(0.f) : pE[0];
//	bbMax = (pE.empty()) ? glm::vec3(0.f) : pE[0];
//
//	for (auto &i : pE)
//	{
//		bbMin = glm::min(i, bbMin);
//		bbMax = glm::max(i, bbMax);
//	}
//
//	bbSize = bbMax - bbMin;
//	//bbCenter = .5f * (bbMin + bbMax);
//	//obbMVP = glm::translate(glm::mat4(1.f), bbCenter) * glm::scale(glm::mat4(1.f), bbSize);
//}

//////////////
/* PER FRAME (GL_RENDER) */
//////////////
bool Object::isSphereInFrustum(glm::vec3 sphereCenter, glm::vec3 sphereRad)
{
	bool res = 1;

	float glmTestX = sphereRad.x;
	float glmTestY = sphereRad.y;
	float glmTestZ = sphereRad.z;

	float mySphereRad = glmTestX;
	mySphereRad = glm::max(mySphereRad, glmTestY);
	mySphereRad = glm::max(mySphereRad, glmTestZ);

	for (int i = 0; i < 6; ++i)
	{
		if (myAbj.selCamLi->fPlanes[i].x * sphereCenter.x +
			myAbj.selCamLi->fPlanes[i].y * sphereCenter.y +
			myAbj.selCamLi->fPlanes[i].z * sphereCenter.z +
			myAbj.selCamLi->fPlanes[i].w * 1.f <= -mySphereRad)
		{
			res = 0;
		}
	}

	return res;
}

bool Object::isAABBInFrustum(glm::vec3 Min, glm::vec3 Max)
{
	//bool RightParallelepipedInFrustum2(vec4 &Min, vec4 &Max, vec4 *frustum_planes)

	//this is just example of basic idea - how BOX culling works, both AABB and OBB
	//Min & Max are 2 world space box points. For AABB-frustum culling
	//We may use transformed (by object matrix) to WS 8 box points. Replace Min & Max in equations and we get OBB-frustum.
	//test all 6 frustum planes

	for (int i = 0; i < 6; i++)
	{
		//try to find such plane for which all 8 box points behind it
		//test all 8 box points against frustum plane
		//calculate distance from point to plane
		//if point is in front of the plane (dist > 0) - this is not separating plane
		if (myAbj.selCamLi->fPlanes[i][0] * Min[0] + myAbj.selCamLi->fPlanes[i][1] * Max[1] + myAbj.selCamLi->fPlanes[i][2] * Min[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Min[0] + myAbj.selCamLi->fPlanes[i][1] * Max[1] + myAbj.selCamLi->fPlanes[i][2] * Max[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Max[0] + myAbj.selCamLi->fPlanes[i][1] * Max[1] + myAbj.selCamLi->fPlanes[i][2] * Max[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Max[0] + myAbj.selCamLi->fPlanes[i][1] * Max[1] + myAbj.selCamLi->fPlanes[i][2] * Min[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Max[0] + myAbj.selCamLi->fPlanes[i][1] * Min[1] + myAbj.selCamLi->fPlanes[i][2] * Min[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Max[0] + myAbj.selCamLi->fPlanes[i][1] * Min[1] + myAbj.selCamLi->fPlanes[i][2] * Max[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Min[0] + myAbj.selCamLi->fPlanes[i][1] * Min[1] + myAbj.selCamLi->fPlanes[i][2] * Max[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		if (myAbj.selCamLi->fPlanes[i][0] * Min[0] + myAbj.selCamLi->fPlanes[i][1] * Min[1] + myAbj.selCamLi->fPlanes[i][2] * Min[2] + myAbj.selCamLi->fPlanes[i][3]>0)
			continue;

		return 0;
	}

	return 1;
}

bool Object::isAABBInFrustumAlt(glm::vec3 Min, glm::vec3 Max)
{
	bool inside = 1;
	//test all 6 frustum planes

	for (int i = 0; i < 6; i++)
	{
		//pick closest point to plane and check if it behind the plane
		//if yes - object outside frustum
		float d = max(Min.x * myAbj.selCamLi->fPlanes[i].x, Max.x * myAbj.selCamLi->fPlanes[i].x) +
			max(Min.y * myAbj.selCamLi->fPlanes[i].y, Max.y * myAbj.selCamLi->fPlanes[i].y) +
			max(Min.z * myAbj.selCamLi->fPlanes[i].z, Max.z * myAbj.selCamLi->fPlanes[i].z) +
			myAbj.selCamLi->fPlanes[i].w;
	
		inside &= d > 0;
		//return 0; //with flag works faster
	}

	return inside;
}

void Object::buildFrustumPlanes()
{
	//NEAR
	nc = glm::vec3(tx->val_f, ty->val_f, tz->val_f) + lookO * nearClip->val_f;
	Hnear = 2.f * tan(glm::radians(fov->val_f / 2.f)) * nearClip->val_f;
	Wnear = Hnear * myAbj.aspect;
	ntl = nc + (upO * Hnear / 2.f) - (rightO * Wnear / 2.f);
	ntr = nc + (upO * Hnear / 2.f) + (rightO * Wnear / 2.f);
	nbl = nc - (upO * Hnear / 2.f) - (rightO * Wnear / 2.f);
	nbr = nc - (upO * Hnear / 2.f) + (rightO * Wnear / 2.f);

	//FAR
	fc = glm::vec3(tx->val_f, ty->val_f, tz->val_f) + lookO * farClip->val_f;
	Hfar = 2.f * tan(glm::radians(fov->val_f / 2.f)) * farClip->val_f;
	Wfar = Hfar * myAbj.aspect;
	ftl = fc + (upO * Hfar / 2.f) - (rightO * Wfar / 2.f);
	ftr = fc + (upO * Hfar / 2.f) + (rightO * Wfar / 2.f);
	fbl = fc - (upO * Hfar / 2.f) - (rightO * Wfar / 2.f);
	fbr = fc - (upO * Hfar / 2.f) + (rightO * Wfar / 2.f);

	fPlanes_temp =
	{
		{ ntr, ntl, ftl }, //U
		{ nbl, nbr, fbr }, //D
		{ ntl, nbl, fbl }, //L
		{ nbr, ntr, fbr }, //R
		{ ntl, ntr, nbr }, //N
		{ ftr, ftl, fbl }, //F
	};

	for (int i = 0; i < 6; ++i)
	{
		glm::vec3 e1 = fPlanes_temp[i].v2 - fPlanes_temp[i].v1;
		glm::vec3 e2 = fPlanes_temp[i].v3 - fPlanes_temp[i].v1;

		glm::vec3 N = glm::normalize(glm::cross(e1, e2));
		float d = -glm::dot(N, fPlanes_temp[i].v2);

		fPlanes[i] = glm::vec4(N, d);
	}
}