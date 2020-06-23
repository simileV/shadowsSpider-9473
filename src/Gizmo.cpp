#include "Gizmo.h"

Gizmo::Gizmo()
{

}

Gizmo::~Gizmo()
{

}

string Gizmo::hover()
{
	auto gizType = myAbj.myGizNull->gizType;
	
	//BUILD INITIAL RAY
	myAbj.giz_rayDir = rayCast(myAbj.pMouseNew);
	myAbj.giz_rayOrigin = glm::vec3(myAbj.selCamLi->t->val_3);

	if (gizType == "R")
	{
		glm::vec3 axX(1.f, 0.f, 0.f);
		glm::vec3 axY(0.f, 1.f, 0.f);
		glm::vec3 axZ(0.f, 0.f, 1.f);

		if (myAbj.gizSpace == "local" && myAbj.selB)
		{
			axX = glm::normalize(glm::vec3(myAbj.selB->MM * glm::vec4(axX, 0.f)));
			axY = glm::normalize(glm::vec3(myAbj.selB->MM * glm::vec4(axY, 0.f)));
			axZ = glm::normalize(glm::vec3(myAbj.selB->MM * glm::vec4(axZ, 0.f)));
		}

		if (rotatePlane(axX, myAbj.gizHoverCheckX)) return "X";
		else if (rotatePlane(axY, myAbj.gizHoverCheckY)) return "Y";
		else if (rotatePlane(axZ, myAbj.gizHoverCheckZ)) return "Z";
	}

	else if (gizType == "T" || gizType == "S")
	{
		auto dualStart = 0.f;
		auto dualEnd = .5f;
		auto xyzEnd = .2f;

		auto df = rayInter(glm::vec3(0.f, 1.f, 0.f), 1, "full"); //XZ

		if (gizType == "S" && df.x > 0 && df.x < xyzEnd && df.z > 0 && df.z < xyzEnd) return "XYZ";
		else if (df.x >= 0 && df.x <= 1 && fabs(df.z) < .1f) return "X";
		else if (df.z >= 0 && df.z <= 1 && fabs(df.x) < .1f) return "Z";
		else if (df.x > dualStart && df.x < dualEnd && df.z > dualStart && df.z < dualEnd) return "XZ";

		else
		{
			df = rayInter(glm::vec3(0.f, 0.f, 1.f), 1, "full"); //XY

			if (gizType == "S" && df.x > 0 && df.x < xyzEnd && df.y > 0 && df.y < xyzEnd) return "XYZ";
			else if (df.x >= 0 && df.x <= 1 && fabs(df.y) < .1f) return "X";
			else if (df.y >= 0 && df.y <= 1 && fabs(df.x) < .1f) return "Y";
			else if (df.x > dualStart && df.x < dualEnd && df.y > dualStart && df.y < dualEnd) return "XY";

			else
			{
				df = rayInter(glm::vec3(1.f, 0.f, 0.f), 1, "full"); //YZ

				if (gizType == "S" && df.y > 0 && df.y < xyzEnd && df.z > 0 && df.z < xyzEnd) return "XYZ";
				else if (df.y >= 0 && df.y <= 1 && fabs(df.z) < .1f) return "Y";
				else if (df.z >= 0 && df.z <= 1 && fabs(df.y) < .1f) return "Z";
				else if (df.y > dualStart && df.y < dualEnd && df.z > dualStart && df.z < dualEnd) return "YZ";
			}
		}
	}

	return "NONE";
}

void Gizmo::transform()
{
	if (myAbj.lmbTgl)
		return;

	//BUILD NEW RAY FOR DRAG
	myAbj.giz_rayDir = rayCast(myAbj.pMouseNew);
	myAbj.giz_rayOrigin = glm::vec3(myAbj.selCamLi->t->val_3);

	//RAY INTERSECT
	glm::vec3 axX(1.f, 0.f, 0.f);
	glm::vec3 axY(0.f, 1.f, 0.f);
	glm::vec3 axZ(0.f, 0.f, 1.f);

	auto df = rayInter(myAbj.gizN, 0, "inter") - myAbj.gizMouseDown;
	glm::vec3 adf;

	if (myAbj.myGizNull->gizType == "T")
	{
		if (myAbj.gizSpace == "local")
		{
			axX = glm::normalize(glm::vec3(myAbj.selB->MM * glm::vec4(axX, 0.f)));
			axY = glm::normalize(glm::vec3(myAbj.selB->MM * glm::vec4(axY, 0.f)));
			axZ = glm::normalize(glm::vec3(myAbj.selB->MM * glm::vec4(axZ, 0.f)));
		}

		df = dotInterAx(df, axX, axY, axZ);
		adf = df.x * axX + df.y * axY + df.z * axZ;

		for (auto &i : myAbj.allObj)
		{
			if (i->selected)
			{
				i->t->val_3 += adf;
				i->piv->val_3 += adf;
			}
		}
	}

	else if (myAbj.myGizNull->gizType == "R")
	{
		auto clipP = myAbj.selCamLi->PM * (myAbj.selCamLi->VM * glm::vec4(myAbj.selB->t->val_3, 1.f));

		auto ndcP = glm::vec3(clipP.x, clipP.y, clipP.z) / clipP.w;
		auto viewOffset = 0.f;
		auto ssP = ((glm::vec2(ndcP.x, ndcP.y) + 1.f) / 2.f) * glm::vec2(myAbj.width, myAbj.height) + viewOffset;

		auto camFor = glm::vec3(myAbj.selCamLi->MM * glm::vec4(0.f, 0.f, 1.f, 0.f));

		//get screen space direction of mouse move vs mouse xy delta
		auto sign = glm::sign(glm::dot(camFor, myAbj.gizN));
		if (sign == 0.f) sign = 1.f; // looking for 1 or -1

		auto mouseDelta = glm::normalize(myAbj.pMouseNew - ssP);
		auto screenDir = glm::normalize(sign * glm::vec3(-glm::sign(mouseDelta.y), glm::sign(mouseDelta.x), 0.f));

		glm::vec3 pDiff(myAbj.pMouseDiff.x, myAbj.pMouseDiff.y, 0.f);
		auto mouseDeltaInAxisDir = glm::dot(screenDir, pDiff); //

		glm::vec2 pOld2(myAbj.pMouseOld.x, myAbj.pMouseOld.y);
		auto rayDirAfter = rayCast(pOld2 + mouseDeltaInAxisDir * glm::vec2(screenDir));
		auto rayDirBefore = rayCast(pOld2);

		auto gotEditDelta = glm::length(rayDirAfter - rayDirBefore) * glm::sign(mouseDeltaInAxisDir) * 360.f;

		for (auto &i : myAbj.allObj)
		{
			if (i->selected)
			{
				if (myAbj.gizTransType == "X")
				{
				 	i->r->val_3.x -= gotEditDelta;
				}

				if (myAbj.gizTransType == "Y")
				{
					i->r->val_3.y -= gotEditDelta;
				}

				if (myAbj.gizTransType == "Z")
				{
					i->r->val_3.z -= gotEditDelta;
				}
			}
		}
	}

	else if (myAbj.myGizNull->gizType == "S")
	{
		adf = dotInterAx(df, axX, axY, axZ);

		auto dualSpeed = 25.f;
		float dualAdd;

		if (myAbj.gizTransType == "XZ")
		{
			dualAdd = int(df.x + df.z * dualSpeed) / dualSpeed;
			adf = glm::vec3(dualAdd, 0.f, dualAdd);
		}

		else if (myAbj.gizTransType == "XY")
		{
			dualAdd = int(df.x + df.y * dualSpeed) / dualSpeed;
			adf = glm::vec3(dualAdd, dualAdd, 0.f);
		}

		else if (myAbj.gizTransType == "YZ")
		{
			dualAdd = int(df.y + df.z * dualSpeed) / dualSpeed;
			adf = glm::vec3(0.f, dualAdd, dualAdd);
		}

		for (auto &i : myAbj.allObj)
		{
			if (i->selected)
			{
				i->sx->val_f += adf.x;
				i->sy->val_f += adf.y;
				i->sz->val_f += adf.z;

			}
		}
	}

	myAbj.gizMouseDown += adf;

	setLightsDirty();
}

glm::vec3 Gizmo::dotInterAx(glm::vec3 df, glm::vec3 axX, glm::vec3 axY, glm::vec3 axZ)
{
	string type = myAbj.gizTransType;

	if (type == "XYZ") return glm::vec3(myAbj.pMouseDiff.x * .01f);
	else if (type == "X") return glm::vec3(glm::dot(df, axX), 0.f, 0.f);
	else if (type == "Y") return glm::vec3(0.f, glm::dot(df, axY), 0.f);
	else if (type == "Z") return glm::vec3(0.f, 0.f, glm::dot(df, axZ));
	else if (type == "XZ") return glm::vec3(glm::dot(df, axX), 0.f, glm::dot(df, axZ));
	else if (type == "XY") return glm::vec3(glm::dot(df, axX), glm::dot(df, axY), 0.f);
	else if (type == "YZ") return glm::vec3(0.f, glm::dot(df, axY), glm::dot(df, axZ));

	return glm::vec3(0.f);
}

glm::vec3 Gizmo::rayCast(glm::vec2 XYin)
{
	glm::vec4 lRayEnd_NDC((XYin.x / myAbj.width - .5f) * 2.f, (XYin.y / myAbj.height - .5f) * -2.f, 0.f, 1.f);

	glm::vec4 lRayEnd_world = glm::inverse(myAbj.selCamLi->PM * myAbj.selCamLi->VM) * lRayEnd_NDC;
	lRayEnd_world /= lRayEnd_world.w;

	glm::vec3 lRayDir_world(lRayEnd_world - glm::vec4(myAbj.selCamLi->t->val_3, 1.f));

	return glm::normalize(lRayDir_world);

	//    if (myV.myGL->selCamLi->camLiTypeGet("dirOrtho")) // DEBUG ORTHO RAYCAST
	//    {
	//        auto dirN = myV.myGL->giz_rayDir - myV.myGL->giz_rayOrigin;
	//        myV.myGL->giz_rayDir = glm::normalize(dirN);
	//    }
}

glm::vec3 Gizmo::rayInter(glm::vec3 normal, bool getTrueNormal, string mode)
{
	if (getTrueNormal)
	{
		auto normalAdjusted = myAbj.myGizNull->RM * glm::vec4(normal, 1.f);
		normal = glm::vec3(normalAdjusted);
	}

	myAbj.gizN = normal;

	//RAY INTERSECT
	auto gizPlane = glm::vec4(normal, glm::dot(myAbj.myGizNull->parentTo->t->val_3, normal));
	auto tmp = (normal * gizPlane.w) - myAbj.giz_rayOrigin;
	auto den = glm::dot(normal, myAbj.giz_rayDir);
	auto inter = myAbj.giz_rayOrigin + (glm::dot(normal, tmp) / den) * myAbj.giz_rayDir;

	if (mode == "inter")
		return inter;

	myAbj.gizMouseDown = inter; // only set on the full vers

	return glm::vec3(glm::inverse(myAbj.myGizNull->MM) * glm::vec4(inter, 1.f)) / myAbj.gizScale; //TRANSFORM PT
}

bool Gizmo::rotatePlane(glm::vec3 normal, glm::vec3 hoverCheck)
{
	auto inter = rayInter(normal, 0, "inter");
	myAbj.gizMouseDown = inter;

	auto df = (inter - myAbj.myGizNull->parentTo->t->val_3);

	auto dotCheck = glm::dot(df, hoverCheck * myAbj.gizScale);
	auto hoverThick = .2f;

	if (dotCheck >= 0.f)
	{
		if (glm::length(df) > (1.f - hoverThick) * myAbj.gizScale && glm::length(df) < (1.f + hoverThick) * myAbj.gizScale)
			return 1;
	}

	return 0;
}

void Gizmo::resetSetCol(string type)
{
	//reset color
	for (auto &i : myAbj.allObj)
	{
		auto type = i->type;

		if (type == "GIZ_CONE" || type == "GIZ_CUBE" || type == "GIZ_DUAL_HANDLE" || type == "GIZ_LINE" || type == "GIZ_CIRC" || type == "GIZ_CIRC_HALF")
			i->Cgiz = i->Cgiz_stored;
	}

	auto Csel = glm::vec3(1.f, 1.f, 0.f); //yellow

	for (auto &i : myAbj.allGiz)
	{
		auto name = i->name->val_s;

		if (type == "X" && (name == "gizCircHalfX" || name == "gizConeX" || name == "gizCubeX" || name == "gizLineX"))
			i->Cgiz = Csel;

		else if (type == "Y" && (name == "gizCircHalfY" || name == "gizConeY" || name == "gizCubeY" || name == "gizLineY"))
			i->Cgiz = Csel;

		else if (type == "Z" && (name == "gizCircHalfZ" || name == "gizConeZ" || name == "gizCubeZ" || name == "gizLineZ"))
			i->Cgiz = Csel;

		else if (type == "XYZ" && name == "gizCubeXYZ") i->Cgiz = Csel;
		else if (type == "XZ" && name == "gizDualXZ") i->Cgiz = Csel;
		else if (type == "XY" && name == "gizDualXY") i->Cgiz = Csel;
		else if (type == "YZ" && name == "gizDualYZ") i->Cgiz = Csel;
	}
}