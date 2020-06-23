/*
reference:
	https://github.com/leonardo98/TexturedAssimp3DAnimationsOpenGL
*/

#include "Object.h"

Object::Object()
{
	name = make_shared<MultiAttr>();
	name->name = "name";
	name->type = "string";
	name->val_s = "renameMe";

	//TRANSFORM
	t = make_shared<MultiAttr>();
	t->name = "t";
	t->type = "vec3";
	t->val_3 = glm::vec3(0.f);
	multiObj.push_back(t);

	tx = make_shared<MultiAttr>();
	tx->name = "tx";
	tx->type = "float";
	tx->val_f = 0.f;
	multiObj.push_back(tx);

	ty = make_shared<MultiAttr>();
	ty->name = "ty";
	ty->type = "float";
	ty->val_f = 0.f;
	multiObj.push_back(ty);

	tz = make_shared<MultiAttr>();
	tz->name = "tz";
	tz->type = "float";
	tz->val_f = 0.f;
	multiObj.push_back(tz);

	r = make_shared<MultiAttr>();
	r->name = "r";
	r->type = "vec3";
	r->val_3 = glm::vec3(0.f);
	multiObj.push_back(r);

	sx = make_shared<MultiAttr>();
	sx->name = "sx";
	sx->type = "float";
	sx->val_f = 1.f;
	multiObj.push_back(sx);

	sy = make_shared<MultiAttr>();
	sy->name = "sy";
	sy->type = "float";
	sy->val_f = 1.f;
	multiObj.push_back(sy);

	sz = make_shared<MultiAttr>();
	sz->name = "sz";
	sz->type = "float";
	sz->val_f = 1.f;
	multiObj.push_back(sz);

	v = make_shared<MultiAttr>();
	v->name = "v";
	v->type = "bool";
	v->val_b = 1;
	multiObj.push_back(v);

	bb = make_shared<MultiAttr>();
	bb->name = "bb";
	bb->type = "bool";
	bb->val_b = 0;
	multiObj.push_back(bb);

	anim = make_shared<MultiAttr>();
	anim->name = "anim";
	anim->type = "bool";
	anim->val_b = 0;
	multiObj.push_back(anim);

	animAI = make_shared<MultiAttr>();
	animAI->name = "anim";
	animAI->type = "bool";
	animAI->val_b = 0;
	multiObj.push_back(animAI);

	debugSkelGen = make_shared<MultiAttr>();
	debugSkelGen->name = "debugSkelGen";
	debugSkelGen->type = "bool";
	debugSkelGen->val_b = 0;
	multiObj.push_back(debugSkelGen);

	debugSkel = make_shared<MultiAttr>();
	debugSkel->name = "debugSkel";
	debugSkel->type = "bool";
	debugSkel->val_b = 0;
	multiObj.push_back(debugSkel);

	debugSkelName = make_shared<MultiAttr>();
	debugSkelName->name = "debugSkelName";
	debugSkelName->type = "string";
	debugSkelName->val_s = "renameMe";
	multiObj.push_back(debugSkelName);

	debugSkellyMM = glm::mat4(1.f);
	
	//SHADER
	albedoM = make_shared<MultiAttr>();
	albedoM->name = "albedoM";
	albedoM->type = "enum";
	albedoM->typeX = "OBJ";
	albedoM->val_s = "BLANK_ALBEDO";
	multiObj.push_back(albedoM);

	alphaM = make_shared<MultiAttr>();
	alphaM->name = "alphaM";
	alphaM->type = "enum";
	alphaM->typeX = "OBJ";
	alphaM->val_s = "BLANK_ALPHA";
	multiObj.push_back(alphaM);

	anisoM = make_shared<MultiAttr>();
	anisoM->name = "anisoM";
	anisoM->type = "enum";
	anisoM->typeX = "OBJ";
	anisoM->val_s = "BLANK_ANISO";
	multiObj.push_back(anisoM);

	metallicM = make_shared<MultiAttr>();
	metallicM->name = "metallicM";
	metallicM->type = "enum";
	metallicM->typeX = "OBJ";
	metallicM->val_s = "BLANK_METALLIC";
	multiObj.push_back(metallicM);

	normalM = make_shared<MultiAttr>();
	normalM->name = "normalM";
	normalM->type = "enum";
	normalM->typeX = "OBJ";
	normalM->val_s = "BLANK_NORMAL";
	multiObj.push_back(normalM);

	ruffM = make_shared<MultiAttr>();
	ruffM->name = "ruffM";
	ruffM->type = "enum";
	ruffM->typeX = "OBJ";
	//ruffM->val_s = "BLANK_RUFF";
	ruffM->val_s = "GRAY_RUFF";
	multiObj.push_back(ruffM);

	dudvM = make_shared<MultiAttr>();
	dudvM->name = "dudvM";
	dudvM->type = "enum";
	dudvM->typeX = "OBJ";
	dudvM->val_s = "BLANK_DUDV";
	multiObj.push_back(dudvM);

		//TILE
		albedoTile = make_shared<MultiAttr>();
		albedoTile->name = "albedoTile";
		albedoTile->type = "vec2";
		albedoTile->typeX = "OBJ";
		albedoTile->val_2 = glm::vec2(1.f, 1.f);
		multiObj.push_back(albedoTile);

		alphaTile = make_shared<MultiAttr>();
		alphaTile->name = "alphaTile";
		alphaTile->type = "vec2";
		alphaTile->typeX = "OBJ";
		alphaTile->val_2 = glm::vec2(1.f, 1.f);
		multiObj.push_back(alphaTile);

		anisoTile = make_shared<MultiAttr>();
		anisoTile->name = "anisoTile";
		anisoTile->type = "vec2";
		anisoTile->typeX = "OBJ";
		anisoTile->val_2 = glm::vec2(1.f, 1.f);
		multiObj.push_back(anisoTile);

		normalTile = make_shared<MultiAttr>();
		normalTile->name = "normalTile";
		normalTile->type = "vec2";
		normalTile->typeX = "OBJ";
		normalTile->val_2 = glm::vec2(1.f, 1.f);
		multiObj.push_back(normalTile);

		ruffTile = make_shared<MultiAttr>();
		ruffTile->name = "ruffTile";
		ruffTile->type = "vec2";
		ruffTile->typeX = "OBJ";
		ruffTile->val_2 = glm::vec2(1.f, 1.f);
		multiObj.push_back(ruffTile);

	//BASE
	Ko = make_shared<MultiAttr>();
	Ko->name = "Ko";
	Ko->type = "float";
	Ko->typeX = "OBJ";
	Ko->val_f = 1.f;
	Ko->min = 0.f;
	Ko->max = 1.f;
	multiObj.push_back(Ko);

	ior = make_shared<MultiAttr>();
	ior->name = "ior";
	ior->type = "float";
	ior->typeX = "OBJ";
	ior->val_f = 1.5f;
	ior->min = 1.f;
	ior->max = 30.f;
	multiObj.push_back(ior);

	ruffA = make_shared<MultiAttr>();
	ruffA->name = "ruffA";
	ruffA->type = "vec2";
	ruffA->typeX = "OBJ";
	ruffA->val_2 = glm::vec2(.3f, .07f);
	ruffA->min = .001f;
	ruffA->max = 1.f;
	multiObj.push_back(ruffA);

	ruffOren = make_shared<MultiAttr>();
	ruffOren->name = "ruffOren";
	ruffOren->type = "float";
	ruffOren->typeX = "OBJ";
	ruffOren->val_f = .5f;
	ruffOren->min = 0.f;
	ruffOren->max = 1.f;
	multiObj.push_back(ruffOren);

		shadowCast = make_shared<MultiAttr>();
		shadowCast->name = "shadowCast";
		shadowCast->type = "bool";
		shadowCast->tab = 1;
		shadowCast->val_b = 1;
		multiObj.push_back(shadowCast);

		twoSided = make_shared<MultiAttr>();
		twoSided->name = "twoSided";
		twoSided->type = "enum";
		twoSided->val_s = "BLACK";
		twoSided->comboList = { "OFF", "BLACK", "FULL" };
		twoSided->repop = 0;
		twoSided->tab = 1;
		multiObj.push_back(twoSided);

		Cwire = make_shared<MultiAttr>();
		Cwire->name = "Cwire";
		Cwire->type = "color";
		Cwire->typeX = "OBJ";
		Cwire->val_3 = glm::vec3(0.f);
		Cwire->tab = 1;
		multiObj.push_back(Cwire);

		normWt = make_shared<MultiAttr>();
		normWt->name = "normWt";
		normWt->type = "float";
		normWt->typeX = "OBJ";
		normWt->val_f = .5f;
		normWt->min = 0.f;
		normWt->max = 1.f;
		normWt->tab = 1;
		multiObj.push_back(normWt);

		piv = make_shared<MultiAttr>();
		piv->name = "piv";
		piv->type = "vec3";
		piv->val_3 = glm::vec3(0.f);
		piv->tab = 1;
		multiObj.push_back(piv);

		rotOrder = make_shared<MultiAttr>();
		rotOrder->name = "rotOrder";
		rotOrder->type = "enum";
		rotOrder->val_s = "XZY";
		rotOrder->comboList = { "XYZ", "YZX", "ZXY", "XZY", "YXZ", "ZYX" };
		rotOrder->repop = 0;
		rotOrder->tab = 1;
		multiObj.push_back(rotOrder);

	//CAMLI
	camLiType = make_shared<MultiAttr>();
	camLiType->name = "camLiType";
	camLiType->type = "enum";
	camLiType->typeX = "CAMLI";
	camLiType->val_s = "PERSP";
	camLiType->comboList = { "DIR", "ORTHO", "PERSP", "THIRD", "POINT", "SPOT" };
	camLiType->repop = 0;
	multiObj.push_back(camLiType);

	fov = make_shared<MultiAttr>();
	fov->name = "fov";
	fov->type = "float";
	fov->typeX = "CAMLI";
	fov->val_f = 50.f; //50
	fov->min = 1.f;
	multiObj.push_back(fov);

	nearClip = make_shared<MultiAttr>();
	nearClip->name = "nearClip";
	nearClip->type = "float";
	nearClip->typeX = "CAMLI";
	nearClip->val_f = .01f;
	nearClip->min = .01f;
	nearClip->tab = 1;
	multiObj.push_back(nearClip);

	farClip = make_shared<MultiAttr>();
	farClip->name = "farClip";
	farClip->type = "float";
	farClip->typeX = "CAMLI";
	farClip->val_f = 1000.f;
	farClip->min = .01f;
	farClip->tab = 1;
	multiObj.push_back(farClip);

	nearShadow = make_shared<MultiAttr>();
	nearShadow->name = "nearShadow";
	nearShadow->type = "float";
	nearShadow->typeX = "CAMLI";
	nearShadow->tab = 1;
	nearShadow->val_f = 1.f;
	nearShadow->min = 0.f;
	multiObj.push_back(nearShadow);

	farShadow = make_shared<MultiAttr>();
	farShadow->name = "farShadow";
	farShadow->type = "float";
	farShadow->typeX = "CAMLI";
	farShadow->tab = 1;
	farShadow->val_f = 100.f;
	multiObj.push_back(farShadow);

	orthoFree = make_shared<MultiAttr>();
	orthoFree->name = "orthoFree";
	orthoFree->type = "bool";
	orthoFree->typeX = "CAMLI";
	orthoFree->val_b = 0;
	multiObj.push_back(orthoFree);

	orthoType = make_shared<MultiAttr>();
	orthoType->name = "orthoType";
	orthoType->type = "enum";
	orthoType->typeX = "CAMLI";
	orthoType->val_s = "TOP";
	orthoType->comboList = { "BACK", "BOTTOM", "FRONT", "LEFT", "RIGHT", "TOP" };
	orthoType->repop = 0;
	multiObj.push_back(orthoType);

	orthoZoom = make_shared<MultiAttr>();
	orthoZoom->name = "orthoZoom";
	orthoZoom->type = "float";
	orthoZoom->typeX = "CAMLI";
	orthoZoom->val_f = 2.f;
	orthoZoom->min = .001f;
	multiObj.push_back(orthoZoom);

	//LIGHT
	Cl = make_shared<MultiAttr>();
	Cl->name = "Cl";
	Cl->grp = "light";
	Cl->type = "color";
	Cl->typeX = "CAMLI";
	Cl->val_3 = glm::vec3(1.f);
	multiObj.push_back(Cl);

	lInten = make_shared<MultiAttr>();
	lInten->name = "lInten";
	lInten->grp = "light";
	lInten->type = "float";
	lInten->typeX = "CAMLI";
	lInten->val_f = 3.f; //
	lInten->min = 0.f;
	multiObj.push_back(lInten);

	lSpotI = make_shared<MultiAttr>();
	lSpotI->name = "lSpotI";
	lSpotI->grp = "light";
	lSpotI->type = "float";
	lSpotI->typeX = "CAMLI";
	lSpotI->val_f = 10.f;
	lSpotI->min = 0.f;
	multiObj.push_back(lSpotI);

	lSpotO = make_shared<MultiAttr>();
	lSpotO->name = "lSpotO";
	lSpotO->grp = "light";
	lSpotO->type = "float";
	lSpotO->typeX = "CAMLI";
	lSpotO->val_f = 30.f;
	multiObj.push_back(lSpotO);

	//VOLUME LIGHT
	volCone = make_shared<MultiAttr>();
	volCone->name = "volCone";
	volCone->grp = "vol";
	volCone->type = "bool";
	volCone->typeX = "CAMLI";
	volCone->val_b = 0;
	multiObj.push_back(volCone);

	volDist = make_shared<MultiAttr>();
	volDist->name = "volDist";
	volDist->grp = "vol";
	volDist->type = "float";
	volDist->typeX = "CAMLI";
	volDist->val_f = 5.5f;
	volDist->min = 0.f;
	multiObj.push_back(volDist);

	volS = make_shared<MultiAttr>();
	volS->name = "volS";
	volS->grp = "vol";
	volS->type = "vec3";
	volS->typeX = "CAMLI";
	volS->val_3 = glm::vec3(1.f);
	multiObj.push_back(volS);

	/* FSQ */
	cubeM = make_shared<MultiAttr>();
	cubeM->name = "cube_specM";
	cubeM->type = "enum";
	cubeM->typeX = "FBO";
	cubeM->val_s = "ENNIS";
	multiObj.push_back(cubeM);

	//BLOOM
	bloomInten = make_shared<MultiAttr>();
	bloomInten->name = "bloomInten";
	bloomInten->grp = "bloom";
	bloomInten->type = "float";
	bloomInten->typeX = "FBO";
	//bloomInten->val_f = .1f;
	//bloomInten->val_f = .05f;
	bloomInten->val_f = .01f;
	//bloomInten->val_f = .005f;
	//bloomInten->val_f = .002f;
	bloomInten->min = 0.f;
	bloomInten->max = 1.f;
	multiObj.push_back(bloomInten);

	bloomLensInten = make_shared<MultiAttr>();
	bloomLensInten->name = "bloomLensInten";
	bloomLensInten->grp = "bloom";
	bloomLensInten->type = "float";
	bloomLensInten->typeX = "FBO";
	//bloomLensInten->val_f = .2f;
	//bloomLensInten->val_f = .02f;
	bloomLensInten->val_f = 0.005f;
	bloomLensInten->min = 0.f;
	bloomLensInten->max = 1.f;
	multiObj.push_back(bloomLensInten);

	lensM = make_shared<MultiAttr>();
	lensM->name = "lensM";
	lensM->type = "enum";
	lensM->typeX = "FBO";
	lensM->val_s = "DIRTY_LENS";
	multiObj.push_back(lensM);

	//HDR
	adaptTime = make_shared<MultiAttr>();
	adaptTime->name = "adaptTime";
	adaptTime->grp = "hdr";
	adaptTime->type = "float";
	adaptTime->typeX = "FBO";
	adaptTime->val_f = .5f;
	adaptTime->min = 0.f;
	multiObj.push_back(adaptTime);

	adaptAuto = make_shared<MultiAttr>();
	adaptAuto->name = "adaptAuto";
	adaptAuto->grp = "hdr";
	adaptAuto->type = "bool";
	adaptAuto->typeX = "FBO";
	adaptAuto->val_b = 1;
	multiObj.push_back(adaptAuto);

	expo = make_shared<MultiAttr>();
	expo->name = "expo";
	expo->grp = "hdr";
	expo->type = "float";
	expo->typeX = "FBO";
	expo->val_f = 1.1f;
	expo->min = 1.001f;
	multiObj.push_back(expo);

	Kgi = make_shared<MultiAttr>();
	Kgi->name = "Kgi";
	Kgi->grp = "hdr";
	Kgi->type = "float";
	Kgi->typeX = "FBO";
	//Kgi->val_f = .25f;
	Kgi->val_f = .5f;
	//Kgi->val_f = .01f;

	Kgi->min = 0.f;
	Kgi->max = 1.f;
	multiObj.push_back(Kgi);

	vign = make_shared<MultiAttr>();
	vign->name = "vign";
	vign->grp = "hdr";
	vign->type = "bool";
	vign->typeX = "FBO";
	vign->val_b = 1;
	multiObj.push_back(vign);

	vignDist = make_shared<MultiAttr>();
	vignDist->name = "vignDist";
	vignDist->grp = "hdr";
	vignDist->type = "float";
	vignDist->typeX = "FBO";
	vignDist->val_f = 1.5f;
	vignDist->min = 1.3f;
	multiObj.push_back(vignDist);

		//FXAA
		fxaaBlur = make_shared<MultiAttr>();
		fxaaBlur->name = "fxaaBlur";
		fxaaBlur->grp = "fxaa";
		fxaaBlur->type = "bool";
		fxaaBlur->typeX = "FBO";
		fxaaBlur->val_b = 1;
		fxaaBlur->tab = 1;
		multiObj.push_back(fxaaBlur);

		fxaaSubPix = make_shared<MultiAttr>();
		fxaaSubPix->name = "subPix";
		fxaaSubPix->grp = "fxaa";
		fxaaSubPix->type = "float";
		fxaaSubPix->typeX = "FBO";
		//fxaaSubPix->val_f = .75f; //
		fxaaSubPix->val_f = .01f;

		fxaaSubPix->min = .001f;
		fxaaSubPix->tab = 1;
		multiObj.push_back(fxaaSubPix);

		fxaaEdgeThr = make_shared<MultiAttr>();
		fxaaEdgeThr->name = "edgeThr";
		fxaaEdgeThr->grp = "fxaa";
		fxaaEdgeThr->type = "float";
		fxaaEdgeThr->typeX = "FBO";
		//fxaaEdgeThr->val_f = .125f; //
		fxaaEdgeThr->val_f = .01f;

		fxaaEdgeThr->min = .001f;
		fxaaEdgeThr->tab = 1;
		multiObj.push_back(fxaaEdgeThr);

		fxaaEdgeThrMin = make_shared<MultiAttr>();
		fxaaEdgeThrMin->name = "edgeThrMin";
		fxaaEdgeThrMin->grp = "fxaa";
		fxaaEdgeThrMin->type = "float";
		fxaaEdgeThrMin->typeX = "FBO";
		fxaaEdgeThrMin->val_f = .0833f; //
		//fxaaEdgeThrMin->val_f = .001f;

		fxaaEdgeThrMin->min = .001f;
		fxaaEdgeThrMin->tab = 1;
		multiObj.push_back(fxaaEdgeThrMin);

	//PAINT
	clearBehav = make_shared<MultiAttr>();
	clearBehav->name = "clearBehav";
	clearBehav->grp = "paint";
	clearBehav->type = "enum";
	clearBehav->typeX = "FBO";
	//clearBehav->val_s = "OnBake";
	//clearBehav->val_s = "OnVMup";
	clearBehav->val_s = "Manual";
	clearBehav->comboList = { "OnBake", "OnVMup", "Manual" };
	clearBehav->repop = 0;
	multiObj.push_back(clearBehav);

	displMode = make_shared<MultiAttr>();
	displMode->name = "displMode";
	displMode->grp = "paint";
	displMode->type = "enum";
	displMode->typeX = "FBO";
	displMode->val_s = "FULL";
	displMode->comboList = { "FULL", "LAYER", "MAP" };
	displMode->repop = 0;
	multiObj.push_back(displMode);

	edgeThr = make_shared<MultiAttr>();
	edgeThr->name = "edgeThr";
	edgeThr->grp = "paint";
	edgeThr->type = "float";
	edgeThr->typeX = "FBO";
	edgeThr->val_f = .6f;
	edgeThr->min = .001f;
	multiObj.push_back(edgeThr);

		//SSAO
		ssaoBias = make_shared<MultiAttr>();
		ssaoBias->name = "bias";
		ssaoBias->grp = "ssao";
		ssaoBias->type = "float";
		ssaoBias->typeX = "FBO";
		ssaoBias->val_f = .075f;
		ssaoBias->min = 0.f;
		ssaoBias->max = 1.f;
		multiObj.push_back(ssaoBias);

		ssaoInten = make_shared<MultiAttr>();
		ssaoInten->name = "inten";
		ssaoInten->grp = "ssao";
		ssaoInten->type = "float";
		ssaoInten->typeX = "FBO";
		ssaoInten->val_f = 4.f;
		ssaoInten->min = 0.f;
		multiObj.push_back(ssaoInten);

		ssaoRad = make_shared<MultiAttr>();
		ssaoRad->name = "rad";
		ssaoRad->grp = "ssao";
		ssaoRad->type = "float";
		ssaoRad->typeX = "FBO";
		ssaoRad->val_f = 1.f;
		ssaoRad->min = .001f;
		multiObj.push_back(ssaoRad);

	//TRANSP
	transpW = make_shared<MultiAttr>();
	transpW->name = "transpW";
	transpW->grp = "transp";
	transpW->type = "float";
	transpW->typeX = "FBO";
	transpW->val_f = .005f;
	transpW->min = .001f;
	transpW->max = 1.f;
	multiObj.push_back(transpW);

	//SSR
	ssrInten = make_shared<MultiAttr>();
	ssrInten->name = "ssrInten";
	ssrInten->grp = "ssr";
	ssrInten->type = "float";
	ssrInten->typeX = "FBO";
	ssrInten->val_f = 1.f;
	ssrInten->min = 0.f;
	ssrInten->max = 100.f;
	multiObj.push_back(ssrInten);

	ssrIter = make_shared<MultiAttr>();
	ssrIter->name = "iter";
	ssrIter->grp = "ssr";
	ssrIter->type = "int";
	ssrIter->typeX = "FBO";
	//ssrIter->val_i = 75;
	ssrIter->val_i = 50;
	ssrIter->min = 1;
	ssrIter->tab = 1;
	multiObj.push_back(ssrIter);

	ssrRefine = make_shared<MultiAttr>();
	ssrRefine->name = "refine";
	ssrRefine->grp = "ssr";
	ssrRefine->type = "int";
	ssrRefine->typeX = "FBO";
	ssrRefine->val_i = 4;
	ssrRefine->min = 0;
	ssrRefine->tab = 1;
	multiObj.push_back(ssrRefine);

	ssrPixStride = make_shared<MultiAttr>();
	ssrPixStride->name = "pixStride";
	ssrPixStride->grp = "ssr";
	ssrPixStride->type = "int";
	ssrPixStride->typeX = "FBO";
	ssrPixStride->val_i = 10;
	ssrPixStride->min = 0;
	ssrPixStride->tab = 1;
	multiObj.push_back(ssrPixStride);

	ssrPixStrideZ = make_shared<MultiAttr>();
	ssrPixStrideZ->name = "pixStrideZ";
	ssrPixStrideZ->grp = "ssr";
	ssrPixStrideZ->type = "float";
	ssrPixStrideZ->typeX = "FBO";
	ssrPixStrideZ->val_f = 400.f; //////
	ssrPixStrideZ->min = 0.f;
	ssrPixStrideZ->tab = 1;
	multiObj.push_back(ssrPixStrideZ);

	ssrPixZSize = make_shared<MultiAttr>();
	ssrPixZSize->name = "pixZSize";
	ssrPixZSize->grp = "ssr";
	ssrPixZSize->type = "float";
	ssrPixZSize->typeX = "FBO";
	//ssrPixZSize->val_f = .9f; //
	ssrPixZSize->val_f = 5.f; //
	ssrPixZSize->min = 0.f;
	ssrPixZSize->tab = 1;
	multiObj.push_back(ssrPixZSize);

	ssrMaxRayDist = make_shared<MultiAttr>();
	ssrMaxRayDist->name = "maxRayDist";
	ssrMaxRayDist->grp = "ssr";
	ssrMaxRayDist->type = "float";
	ssrMaxRayDist->typeX = "FBO";
	ssrMaxRayDist->val_f = 200.f;
	ssrMaxRayDist->min = 0.f;
	ssrMaxRayDist->tab = 1;
	multiObj.push_back(ssrMaxRayDist);

	ssrEdgeFade = make_shared<MultiAttr>();
	ssrEdgeFade->name = "edgeFade";
	ssrEdgeFade->grp = "ssr";
	ssrEdgeFade->type = "float";
	ssrEdgeFade->typeX = "FBO";
	ssrEdgeFade->val_f = .75f;
	ssrEdgeFade->min = 0.f;
	ssrEdgeFade->max = .99f;
	ssrEdgeFade->tab = 1;
	multiObj.push_back(ssrEdgeFade);

	ssrEyeFade0 = make_shared<MultiAttr>();
	ssrEyeFade0->name = "eyeFade0";
	ssrEyeFade0->grp = "ssr";
	ssrEyeFade0->type = "float";
	ssrEyeFade0->typeX = "FBO";
	ssrEyeFade0->val_f = 0.f;
	ssrEyeFade0->min = 0.f;
	ssrEyeFade0->max = 1.f;
	ssrEyeFade0->tab = 1;
	multiObj.push_back(ssrEyeFade0);

	ssrEyeFade1 = make_shared<MultiAttr>();
	ssrEyeFade1->name = "eyeFade1";
	ssrEyeFade1->grp = "ssr";
	ssrEyeFade1->type = "float";
	ssrEyeFade1->typeX = "FBO";
	ssrEyeFade1->val_f = .75f; // 1.f
	ssrEyeFade1->min = 0.f;
	ssrEyeFade1->max = 1.f;
	ssrEyeFade1->tab = 1;
	multiObj.push_back(ssrEyeFade1);

	// ETC
	ripple = make_shared<MultiAttr>();
	ripple->name = "ripple";
	ripple->type = "bool";
	ripple->val_b = 0;
	multiObj.push_back(ripple);

	dieMsgAlpha = make_shared<MultiAttr>();
	dieMsgAlpha->name = "dieMsgAlpha";
	dieMsgAlpha->type = "float";
	dieMsgAlpha->val_f = 1.f;
	multiObj.push_back(dieMsgAlpha);

	dirtyShadow = dirtyVM = deletable = selectable = 1;
	expand = gridV = ignoreOutliner = ref = selected = tempSel = VAO_loaded = 0;
	VAO = false;
	type = "EMPTY";

	biasM = glm::mat4(
		.5f, 0.f, 0.f, 0.f, \
		0.f, .5f, 0.f, 0.f,
		0.f, 0.f, .5f, 0.f,
		.5f, .5f, .5f, 1.f);

	Crand = genColorID();

	// texSel
	texSel.type = "ALBEDO";
	texSel.map.name = "BLANK_ALBEDO";
	texSel.map.ID = 9999;
	texSel.layer.name = "layer0";
	texSel.layer.ID = 9999;

	//setTexSel_init(); // for non selected storage ... currently using with Paint.cpp only

	Cgiz = glm::vec3(0.f);
	Cgiz_stored = glm::vec3(0.f);

	pivRt = glm::vec3(0.f);
	vertsOnObj = 0;

	distO = 0.f;
	lookO = glm::vec3(0.f, 0.f, -1.f);
	rightO = glm::vec3(1.f, 0.f, 0.f);
	targO = glm::vec3(0.f);
	upO = glm::vec3(0.f, 1.f, 0.f);

	spotTarget = glm::vec3(0.f);

	//TXT
	txtOrigin = glm::vec2(-.95f, .8f);

	//////////////
	m_NumBones = 0;
}

void Object::setTexSel_init()
{
	vector<string> typeList = { "ALBEDO", "ALPHA", "ANISO", "LENS", "METALLIC", "RUFF" };

	for (auto &i : typeList)
	{
		for (auto &j : myAbj.allTexMaps)
		{
			//GET STARTING TEXSEL.MAP.ID AND TEXSEL.LAYER.ID
			if (j.type == texSel.type && j.name == texSel.map.name) //type = ALBEDO //map.name = BLANK_ALBEDO
			{
				//cout << "texSel type / map.name = " << texSel.type << " " << texSel.map.name << endl;
				texSel.map.ID = j.ID;

				for (auto &k : j.layer)
				{
					if (k.name == texSel.layer.name)
						texSel.layer.ID = k.ID;
				}
			}

			if (i == j.type)
			{
				if (j.name == texSel.map.name) //"BLANK"
				{
					//texSel (on init) is: type, ID (0), name, ID
					texSel.typeMap.push_back({ j.type, 0, j.name, j.ID });
				}

				for (auto &k : j.layer)
				{
					if (k.name == texSel.layer.name) //"layer0"
						texSel.mapLayer.push_back({ j.name, j.ID, k.name, k.ID });
				}
			}
		}
	}
}

Object::Object(const Object &obj) //COPY CONSTRUCTOR
{
	name = obj.name->Clone();
	multiObj.resize(obj.multiObj.size());

	for (uint i = 0; i < obj.multiObj.size(); ++i)
	{
		multiObj[i] = obj.multiObj[i]->Clone();

		if (multiObj[i]->name == obj.multiObj[i]->name)
		{
			//TRANSFORM
			if		(multiObj[i]->name == "t") t = multiObj[i];
			else if (multiObj[i]->name == "r") r = multiObj[i];
			else if (multiObj[i]->name == "v") v = multiObj[i];
			else if (multiObj[i]->name == "bb") bb = multiObj[i];
			else if (multiObj[i]->name == "anim") anim = multiObj[i];

			//SHADER
			else if (multiObj[i]->name == "albedoM") albedoM = multiObj[i];
			else if (multiObj[i]->name == "alphaM") alphaM = multiObj[i];
			else if (multiObj[i]->name == "anisoM") anisoM = multiObj[i];
			else if (multiObj[i]->name == "metallicM") metallicM = multiObj[i];
			else if (multiObj[i]->name == "normalM") normalM = multiObj[i];
			else if (multiObj[i]->name == "ruffM") ruffM = multiObj[i];
			else if (multiObj[i]->name == "dudvM") dudvM = multiObj[i];

			//TILE
			else if (multiObj[i]->name == "albedoTile") albedoTile = multiObj[i];
			else if (multiObj[i]->name == "alphaTile") alphaTile = multiObj[i];
			else if (multiObj[i]->name == "anisoTile") anisoTile = multiObj[i];
			else if (multiObj[i]->name == "normalTile") normalTile = multiObj[i];
			else if (multiObj[i]->name == "ruffTile") ruffTile = multiObj[i];

			//BASE
			else if (multiObj[i]->name == "Ko") Ko = multiObj[i];
			else if (multiObj[i]->name == "ior") ior = multiObj[i];
			else if (multiObj[i]->name == "ruffA") ruffA = multiObj[i];
			else if (multiObj[i]->name == "ruffOren") ruffOren = multiObj[i];

			else if (multiObj[i]->name == "shadowCast") shadowCast = multiObj[i];
			else if (multiObj[i]->name == "twoSided") twoSided = multiObj[i];
			else if (multiObj[i]->name == "Cwire") Cwire = multiObj[i];
			else if (multiObj[i]->name == "normWt") normWt = multiObj[i];
			else if (multiObj[i]->name == "piv") piv = multiObj[i];
			else if (multiObj[i]->name == "rotOrder") rotOrder = multiObj[i];

			//CAMLI
			else if (multiObj[i]->name == "camLiType") camLiType = multiObj[i];

			//CAM
			else if (multiObj[i]->name == "fov") fov = multiObj[i];
			else if (multiObj[i]->name == "nearClip") nearClip = multiObj[i];
			else if (multiObj[i]->name == "farClip") farClip = multiObj[i];
			else if (multiObj[i]->name == "nearShadow") nearShadow = multiObj[i];
			else if (multiObj[i]->name == "farShadow") farShadow = multiObj[i];
			else if (multiObj[i]->name == "orthoFree") orthoFree = multiObj[i];
			else if (multiObj[i]->name == "orthoType") orthoType = multiObj[i];
			else if (multiObj[i]->name == "orthoZoom") orthoZoom = multiObj[i];

			//LIGHT
			else if (multiObj[i]->name == "Cl") Cl = multiObj[i];
			else if (multiObj[i]->name == "lInten") lInten = multiObj[i];
			else if (multiObj[i]->name == "lSpotI") lSpotI = multiObj[i];
			else if (multiObj[i]->name == "lSpotO") lSpotO = multiObj[i];

			//VOLUME LIGHT
			else if (multiObj[i]->name == "volCone") volCone = multiObj[i];
			else if (multiObj[i]->name == "volDist") volDist = multiObj[i];
			else if (multiObj[i]->name == "volS") volS = multiObj[i];

			//FSQ
			else if (multiObj[i]->name == "cube_specM") cubeM = multiObj[i]; // FSQ

			//BLOOM
			else if (multiObj[i]->name == "bloomInten") bloomInten = multiObj[i];
			else if (multiObj[i]->name == "bloomLensInten") bloomLensInten = multiObj[i];
			else if (multiObj[i]->name == "lensM") lensM = multiObj[i];

			//HDR
			else if (multiObj[i]->name == "adaptTime") adaptTime = multiObj[i];
			else if (multiObj[i]->name == "adaptAuto") adaptAuto = multiObj[i];
			else if (multiObj[i]->name == "expo") expo = multiObj[i];
			else if (multiObj[i]->name == "Kgi") Kgi = multiObj[i];
			else if (multiObj[i]->name == "vign") vign = multiObj[i];
			else if (multiObj[i]->name == "vignDist") vignDist = multiObj[i];

			//FXAA
			else if (multiObj[i]->name == "fxaaBlur") fxaaBlur = multiObj[i];
			else if (multiObj[i]->name == "fxaaSubPix") fxaaSubPix = multiObj[i];
			else if (multiObj[i]->name == "fxaaEdgeThr") fxaaEdgeThr = multiObj[i];
			else if (multiObj[i]->name == "fxaaEdgeThrMin") fxaaEdgeThrMin = multiObj[i];

			//PAINT
			else if (multiObj[i]->name == "clearBehav") clearBehav = multiObj[i];
			else if (multiObj[i]->name == "displMode") displMode = multiObj[i];
			else if (multiObj[i]->name == "edgeThr") edgeThr = multiObj[i];

			//SSAO
			else if (multiObj[i]->name == "ssaoBias") ssaoBias = multiObj[i];
			else if (multiObj[i]->name == "ssaoInten") ssaoInten = multiObj[i];
			else if (multiObj[i]->name == "ssaoRad") ssaoRad = multiObj[i];

			//TRANSP
			else if (multiObj[i]->name == "transpW") transpW = multiObj[i];

			//SSR
			else if (multiObj[i]->name == "ssrInten") ssrInten = multiObj[i];
			else if (multiObj[i]->name == "ssrIter") ssrIter = multiObj[i];
			else if (multiObj[i]->name == "ssrRefine") ssrRefine = multiObj[i];
			else if (multiObj[i]->name == "ssrPixStride") ssrPixStride = multiObj[i];
			else if (multiObj[i]->name == "ssrPixZSize") ssrPixZSize = multiObj[i];
			else if (multiObj[i]->name == "ssrPixStrideZ") ssrPixStrideZ = multiObj[i];
			else if (multiObj[i]->name == "ssrMaxRayDist") ssrMaxRayDist = multiObj[i];
			else if (multiObj[i]->name == "ssrEdgeFade") ssrEdgeFade = multiObj[i];
			else if (multiObj[i]->name == "ssrEyeFade0") ssrEyeFade0 = multiObj[i];
			else if (multiObj[i]->name == "ssrEyeFade1") ssrEyeFade1 = multiObj[i];

			//ETC
			else if (multiObj[i]->name == "ripple") ripple = multiObj[i];
		}
	}

	//VBO vertex attrs
	VAO_loaded = 0;
	VAO = 0;

	pE = obj.pE;
	nE = obj.nE;
	tE = obj.tE;
	uvE = obj.uvE;
	idxE = obj.idxE;

	parentTo = obj.parentTo;

	//CAM
	distO = obj.distO;
	lookO = obj.lookO;
	rightO = obj.rightO;
	upO = obj.upO;
	targO = obj.targO;

	//SPOT
	spotTarget = obj.spotTarget;

	//UPDATE
	dirtyShadow = obj.dirtyShadow;
	dirtyVM = obj.dirtyVM;

	//ETC
	deletable = obj.deletable;
	expand = obj.expand;
	gridV = obj.gridV;
	ignoreOutliner = obj.ignoreOutliner;
	selectable = obj.selectable;
	selected = obj.selected;
	ref = obj.ref;
	vertsOnObj = obj.vertsOnObj;
	dupeStenFix = obj.dupeStenFix;
	type = obj.type;

	//GLSL
	Crand = genColorID();
	showN = obj.showN;
	gaussStage = obj.gaussStage;

	//GIZ
	Cgiz = obj.Cgiz;
	Cgiz_stored = obj.Cgiz_stored;
	gizType = obj.gizType;
	gizSideObj = obj.gizSideObj;

	//TXT
	txtOrigin = obj.txtOrigin;

	//TRANSFORM
	MVP = obj.MVP;
	MV = obj.MV;
	NM = obj.NM;
	MM = obj.MM;
	PM = obj.PM;
	VM = obj.VM;
	TM = obj.TM;
	RM = obj.RM;
	SM = obj.SM;
	debugSkellyMM = obj.debugSkellyMM;

	bbScaleM = obj.bbScaleM;
	bbrotM = obj.bbrotM;
	bbtransM = obj.bbtransM;
	obbMVP = obj.obbMVP;

	bbMin = obj.bbMin;
	bbMax = obj.bbMax;
	bbCenter = obj.bbCenter;
	bbSize = obj.bbSize;
	bbSizeFull = obj.bbSizeFull;

	pivM = obj.pivM;
	pivRtM = obj.pivRtM;
	rpM = obj.rpM;
	rM = obj.rM;
	pivRt = obj.pivRt;

	linkedGrp = obj.linkedGrp;
	aabbMVP = obj.aabbMVP;

	curSceneNI = obj.curSceneNI;
	prevSceneNI = obj.prevSceneNI;
	blendingTime = obj.blendingTime;
}

void Object::VAO_load()
{
	glGetError();

	if (!VAO_loaded)
	{
		for (auto &i : myAbj.GLDataSh)
		{
			if (i.obj.get() == this)
			{
				glCreateVertexArrays(1, &VAO);

				if (type == "BB")
				{
					glEnableVertexArrayAttrib(VAO, 0);
					glVertexArrayVertexBuffer(VAO, 0, i.VBO_P, 0, sizeof(glm::vec3));
					glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

					glVertexArrayElementBuffer(VAO, i.VBO_IDX);
				}

				else if (type == "GRID")
				{
					glEnableVertexArrayAttrib(VAO, 0);
					glVertexArrayVertexBuffer(VAO, 0, i.VBO_P, 0, sizeof(glm::vec3));
					glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
				}

				else if (type == "TXT")
				{
					glEnableVertexArrayAttrib(VAO, 0);
					glVertexArrayVertexBuffer(VAO, 0, i.VBO_P, 0, 1);
					glVertexArrayAttribIFormat(VAO, 0, 1, GL_UNSIGNED_BYTE, 0);
				}

				else if (type == "GIZ_CIRC" || type == "GIZ_CONE" || type == "GIZ_CUBE" || type == "GIZ_DUAL_HANDLE" || type == "GIZ_CIRC_HALF" || type == "GIZ_LINE" || type == "CAMLI")
				{
					glEnableVertexArrayAttrib(VAO, 0);
					glVertexArrayVertexBuffer(VAO, 0, i.VBO_P, 0, sizeof(glm::vec3));
					glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

					if (type == "GIZ_CUBE")
						glVertexArrayElementBuffer(VAO, i.VBO_IDX);
				}

				else if (type == "OBJ" || type == "VOL")
				{
					glEnableVertexArrayAttrib(VAO, 0);
					glVertexArrayVertexBuffer(VAO, 0, i.VBO_P, 0, sizeof(glm::vec3));
					glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

					glEnableVertexArrayAttrib(VAO, 1);
					glVertexArrayVertexBuffer(VAO, 1, i.VBO_UV, 0, sizeof(glm::vec2));
					glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);

					glEnableVertexArrayAttrib(VAO, 2);
					glVertexArrayVertexBuffer(VAO, 2, i.VBO_T, 0, sizeof(glm::vec3));
					glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 0);

					glEnableVertexArrayAttrib(VAO, 3);
					glVertexArrayVertexBuffer(VAO, 3, i.VBO_N, 0, sizeof(glm::vec3));
					glVertexArrayAttribFormat(VAO, 3, 3, GL_FLOAT, GL_FALSE, 0);

					glEnableVertexArrayAttrib(VAO, 4);
					glVertexArrayVertexBuffer(VAO, 4, i.VBO_BONEID, 0, sizeof(glm::ivec4));
					glVertexArrayAttribIFormat(VAO, 4, 4, GL_INT, GL_FALSE);

					glEnableVertexArrayAttrib(VAO, 5);
					glVertexArrayVertexBuffer(VAO, 5, i.VBO_BONEWT, 0, sizeof(glm::vec4));
					glVertexArrayAttribFormat(VAO, 5, 4, GL_FLOAT, GL_FALSE, 0);

					glVertexArrayElementBuffer(VAO, i.VBO_IDX);
				}

				vertsOnObj = (int)pE.size();
			}
		}

		VAO_loaded = 1;
	}

	glErrorPrint("Couldn't load VAO");
}

void Object::glErrorPrint(const char *msg)
{
	if (glGetError() != GL_NO_ERROR)
	{
		const char* APPEND_DETAIL_STRING = ": %s\n";
		const size_t APPEND_LENGTH = strlen(APPEND_DETAIL_STRING) + 1;
		const size_t message_length = strlen(msg);
		char* display_message = (char*)malloc(message_length + APPEND_LENGTH);

		memcpy(display_message, msg, message_length);
		memcpy(&display_message[message_length], APPEND_DETAIL_STRING, APPEND_LENGTH);

		fprintf(stderr, display_message, glGetError());
		free(display_message);
		exit(EXIT_FAILURE);
	}
}

glm::vec3 Object::genColorID()
{
	int myRand = rand();
	int r = (myRand & 0x000000FF) >> 0;
	int g = (myRand & 0x0000FF00) >> 8;
	int b = (myRand & 0x00FF0000) >> 16;
	glm::vec3 myColorID(r / 255.f, g / 255.f, b / 255.f);

	bool preExist = 0;

	for (auto &i : myAbj.allObj)
	{
		if (i->Crand == myColorID)
			preExist = 1;
	}

	if (preExist)
	{
		genColorID();

		return glm::vec3(1.f);
	}

	else
		return myColorID;
}

void Object::rename(string newName) //recursive
{
	if (!ref)
	{
		bool preExist = 0;

		for (auto &i : myAbj.allObj)
		{
			if (i->name->val_s == newName)
				preExist = 1;
		}

		if (preExist)
		{
			newName = getIncName(newName);
			rename(newName);
		}

		else
		{
			for (auto &i : myAbj.allObj)
			{
				if (i->parentTo && i->name->val_s != "pivot")
				{
					if (i->parentTo->name->val_s == name->val_s)
						i->parentTo->name->val_s = newName;
				}
			}

			name->val_s = newName;
		}
	}
}

string Object::getIncName(string dupeName)
{
	size_t last_index = dupeName.find_last_not_of("0123456789");
	string trailingNumbers = dupeName.substr(last_index + 1);
	dupeName.erase(last_index + 1);

	int incrementedTrailingNum = atoi(trailingNumbers.c_str()) + 1; // string2int

	stringstream incrementedName;
	incrementedName << dupeName << incrementedTrailingNum;

	return incrementedName.str();
}

bool Object::camLiTypeGet(string toFind)
{
	bool found = 0;

	if (type == "CAMLI")
	{
		auto myType = camLiType->val_s;

		if (toFind == "cam")
		{
			if (myType == "ORTHO" || myType == "PERSP" || myType == "THIRD")
				found = 1;
		}

		else if (toFind == "dirOrtho")
		{
			if (myType == "DIR" || myType == "ORTHO")
				found = 1;
		}

		else if (toFind == "light")
		{
			if (myType == "DIR" || myType == "POINT" || myType == "SPOT")
				found = 1;
		}
	}

	return found;
}

glm::mat4 Object::rotOrderUse(string myRotOrder)
{
	string rotOrder0(1, myRotOrder.at(0));
	string rotOrder1(1, myRotOrder.at(1));
	string rotOrder2(1, myRotOrder.at(2));

	glm::vec3 axX(1.f, 0.f, 0.f);
	glm::vec3 axY(0.f, 1.f, 0.f);
	glm::vec3 axZ(0.f, 0.f, 1.f);

	glm::mat4 order0, order1, order2;

	//0
	if (rotOrder0 == "X")      order0 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.x), axX);
	else if (rotOrder0 == "Y") order0 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.y), axY);
	else if (rotOrder0 == "Z") order0 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.z), axZ);

	//1
	if (rotOrder1 == "X")      order1 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.x), axX);
	else if (rotOrder1 == "Y") order1 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.y), axY);
	else if (rotOrder1 == "Z") order1 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.z), axZ);

	//2
	if (rotOrder2 == "X")      order2 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.x), axX);
	else if (rotOrder2 == "Y") order2 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.y), axY);
	else if (rotOrder2 == "Z") order2 = glm::rotate(glm::mat4(1.f), glm::radians(r->val_3.z), axZ);

	glm::mat4 myRM = order0 * order1 * order2;

	return order0 * order1 * order2;
}

void Object::tileMaps(GLuint proH)
{
	glm::vec4 albedoAlphaTile, metallicRuffTile, normalTileUp, anisoReplaceMeTile;

	albedoAlphaTile.x = albedoTile->val_2.x;
	albedoAlphaTile.y = albedoTile->val_2.y;
	albedoAlphaTile.z = alphaTile->val_2.x;
	albedoAlphaTile.w = alphaTile->val_2.y;

	metallicRuffTile.x = 1.f;
	metallicRuffTile.y = 1.f;
	metallicRuffTile.z = ruffTile->val_2.x;
	metallicRuffTile.w = ruffTile->val_2.y;

	normalTileUp.x = normalTile->val_2.x;
	normalTileUp.y = normalTile->val_2.y;
	normalTileUp.z = normWt->val_f;
	normalTileUp.w = 0.f;

	anisoReplaceMeTile.x = anisoTile->val_2.x;
	anisoReplaceMeTile.y = anisoTile->val_2.y;
	anisoReplaceMeTile.z = 1.f;
	anisoReplaceMeTile.w = 1.f;

	glProgramUniform4fv(proH, glGetUniformLocation(proH, "albedoAlphaTile"), 1, &albedoAlphaTile.r);
	glProgramUniform4fv(proH, glGetUniformLocation(proH, "metallicRuffTile"), 1, &metallicRuffTile.r);
	glProgramUniform4fv(proH, glGetUniformLocation(proH, "normalTile"), 1, &normalTileUp.r);
	glProgramUniform4fv(proH, glGetUniformLocation(proH, "anisoReplaceMeTile"), 1, &anisoReplaceMeTile.r);
}

void Object::mvpGet()
{
	SM = glm::scale(glm::mat4(1.f), glm::vec3(sx->val_f, sy->val_f, sz->val_f));

	//if (type == "CAMLI" && camLiType->val_s != "DIR")
	if (type == "CAMLI" && camLiType->val_s == "PERSP")
	{
		//cout << "name for yawPitchRoll : " << name->val_s << endl;
		RM = glm::yawPitchRoll(glm::radians(r->val_3.x), glm::radians(r->val_3.y), 0.f);
	}

	else
	{
		RM = rotOrderUse(rotOrder->val_s);
	}

	TM = glm::translate(glm::mat4(1.f), glm::vec3(tx->val_f, ty->val_f, tz->val_f));

	if (this == myAbj.paintStroke.get())
	{
		PM2D = glm::ortho(-1.f * myAbj.aspect, 1.f * myAbj.aspect, -1.f, 1.f, -1.f, 1.f);
		TM = glm::translate(glm::mat4(1.f), glm::vec3(tx->val_f, ty->val_f, tz->val_f) * myAbj.aspectXYZ);
	}

	if (name->val_s == "giz")
	{
		if (myAbj.gizSpace == "local")
			RM = parentTo->RM;

		SM = glm::scale(glm::mat4(1.f), glm::vec3(myAbj.gizScale));
	}

	if (name->val_s == "pivot" || name->val_s == "giz")
	{
		//TM = glm::translate(glm::mat4(1.f), parentTo->piv->val_3);
		TM = glm::translate(glm::mat4(1.f), glm::vec3(parentTo->tx->val_f, parentTo->ty->val_f, parentTo->tz->val_f));
	}

	//PIV
	pivM = glm::translate(glm::mat4(1.f), glm::vec3(tx->val_f, ty->val_f, tz->val_f) - piv->val_3);
	pivRtM = glm::translate(glm::mat4(1.f), pivRt);

	if (camLiTypeGet("light") && (camLiType->val_s == "SPOT")) //facing its target
	{
		glm::mat4 myShadowVM = glm::lookAt(glm::vec3(tx->val_f, ty->val_f, tz->val_f), spotTarget, glm::vec3(0.f, 1.f, 0.f));
		RM = glm::inverse(myShadowVM);
		glm::mat4 toOrigin = glm::translate(glm::mat4(1.f), -glm::vec3(tx->val_f, ty->val_f, tz->val_f));
		RM = toOrigin * RM;
	}

	if (camLiTypeGet("light") && (camLiType->val_s == "DIR")) //facing its target
	{
		//cout << "facing its target : " << endl;
		//cout << "name = " << name->val_s << endl;
		//cout << "t = " << glm::to_string(glm::vec3(tx->val_f, ty->val_f, tz->val_f)) << endl;
		//cout << "targ0 = " << glm::to_string(targO) << endl;
		//cout << endl;
 
		//glm::mat4 myShadowVM = glm::lookAt(glm::vec3(tx->val_f, ty->val_f, tz->val_f), targO, glm::vec3(0.f, 1.f, 0.f));
		//RM = glm::inverse(myShadowVM);
		//glm::mat4 toOrigin = glm::translate(glm::mat4(1.f), -glm::vec3(tx->val_f, ty->val_f, tz->val_f));
		//RM = toOrigin * RM;
	}

	////MM
	//    if (piv->val_3 == glm::vec3(0.f)) MM = TM * RM * SM;
	//    else MM = TM * pivRtM * glm::inverse(pivM) * RM * SM * pivM;

	//if (debugSkel->val_b == 0)
		MM = TM * RM * SM;


	//MM = TM * RM * SM;

	if (debugSkel->val_b && (debugSkelName->val_s == "joint1" || debugSkelName->val_s == "joint2" || debugSkelName->val_s == "joint3" || debugSkelName->val_s == "joint4" || debugSkelName->val_s == "joint5" || debugSkelName->val_s == "joint6" || debugSkelName->val_s == "joint7"))
	{
		MM = debugSkellyMM;// *SM;
		//MM = TM;
	}

	glm::mat4 PM_stored, VM_stored;

	if (type == "CAMLI")
	{
		PM_stored = PM;
		VM_stored = VM;
	}

	if (gizSideObj)
	{
		PM = myAbj.PMgizSide;
		VM = myAbj.VMgizSide;
	}

	else
	{
		if (name->val_s == "teapot3")
		{
			////calc persp PM

			////cout << "PM for teapot3 at mvpGet = " << glm::to_string(PM) << endl;


			//float fakeAspect = (float)myAbj.width / myAbj.height;
			//float fakeFOV = 50.f;
			////float fakeFOV = 35.f;

			//float fakeNearClip = .001f;
			//float fakeFarClip = 1000.f;


			//PM = glm::perspective(glm::radians(fakeFOV), fakeAspect, fakeNearClip, fakeFarClip);



			PM = myAbj.selCamLi->PM; //ortho
		}

		else
			PM = myAbj.selCamLi->PM;

		VM = myAbj.selCamLi->VM;



		//PM = myAbj.selCamLi->PM;
		//VM = myAbj.selCamLi->VM;
	}

	//else
	//{
	//	PM = myAbj.selCamLi->PM;
	//	VM = myAbj.selCamLi->VM;
	//}

	if (parentTo == 0 || name->val_s == "pivot")
		MV = VM * MM;

	//else if (type == "GIZ_CIRC" || type == "GIZ_CIRC_HALF")
	//	MV = VM * parentTo->TM * parentTo->SM * MM;

	else if ((type == "GIZ_CIRC" || type == "GIZ_CIRC_HALF") && !spherebbTgl)
		MV = VM * parentTo->TM * parentTo->SM * MM;

	else if ((type == "GIZ_CIRC" || type == "GIZ_CIRC_HALF") && spherebbTgl)
	{
		//glm::mat4 centerTrans = glm::translate(glm::mat4(1.f), centerAvg);
		MV = VM * myAbj.translateSphereVol; ///
	}

	else
		MV = VM * parentTo->MM * MM;

	{
		//BOUNDING BOX DISPLAY FOR BONES !!!
		if (bb->val_b && aabbTgl == 0 && obbTgl == 0)
		{
			MVP = PM * MV * obbMVP; //renders the individual bones
		}

		else if (bb->val_b && aabbTgl == 1 && obbTgl == 0)
		{
			MVP = PM * VM * aabbMVP;
			//MVP = PM * VM * TM * SM * aabbMVP;
			//MVP = PM * VM * aabbMVP;
			//MVP = PMs * MV * aabbMVP;
			//MVP = PM * VM * TM * RM * SM * aabbMVP;
			//MVP = PM * VM * TM * SM * aabbMVP;
		}

		else if (bb->val_b && aabbTgl == 0 && obbTgl == 1)
		{
			MVP = PM * MV * obbMVP;
		}

		//if (spherebbTgl == 1)
		//{
		//	//MVP = PM * TM * RM * SM * obbMVP;
		//	//MVP = PM * VM * TM * RM * SM * obbMVP;
		//	//MV = VM * parentTo->TM * parentTo->SM * MM;
		//	MV = VM * MM;
		//}

		else if (this == myAbj.paintStroke.get())
			MVP = PM2D * MM;

		else
			MVP = PM * MV;
	}

	NM = glm::mat3(glm::transpose(glm::inverse(MV)));

	if (type == "CAMLI")
	{
		PM = PM_stored;
		VM = VM_stored;
	}
}

void Object::setTarg(glm::vec3 foc, float minD)
{
	targO = foc;
	distO = glm::distance(glm::vec3(tx->val_f, ty->val_f, tz->val_f), targO);

	if (minD != 0.f)
		distO = glm::min(minD, distO);

	auto V = glm::lookAt(glm::vec3(tx->val_f, ty->val_f, tz->val_f), targO, upO);

	if (V[0][0] < 0)
		r->val_3.x = glm::degrees((float)(PI - asinf(-V[2][0])));

	else
		r->val_3.x = glm::degrees(asinf(-V[2][0]));

	r->val_3.y = glm::degrees(asinf(-V[1][2]));

	setDirty();
}

void Object::setDirty()
{
	dirtyVM = 1;

	if (camLiTypeGet("light"))
		dirtyShadow = 1;
}

void Object::parentObj(string parentName)
{
	bool found = 0;

	for (auto &i : myAbj.allObj)
	{
		if (i->name->val_s == parentName)
		{
			found = 1;
			parentTo = i;

			break;
		}
	}

	if (!found)
		cout << "parentObj() could not find " << parentName;
}

void Object::shadowMatrixPass(string type)
{
	shared_ptr<Object> shadowObjTemp;
	glm::mat4 PM_shadow, VM_shadow, depth_or_depthBiasMVP;

	if (type == "render")
		shadowObjTemp = myAbj.shadowObj;

	else if (type == "UBO")
		shadowObjTemp = myAbj.shadowObjUBO;

	//if (shadowObjTemp->camLiType->val_s == "SPOT")
	if (shadowObjTemp->camLiType->val_s == "DIR")
	{
		glm::vec3 lightInvDir(0.f, 10.f, 10.f);
		//glm::vec3 lightInvDir(0.f, 30.f, 10.f);
		VM_shadow = glm::lookAt(lightInvDir, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
		//VM_shadow = glm::lookAt(shadowObjTemp->r->val_3, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

		//PM_shadow = glm::ortho(-10.f, 10.f, -10.f, 10.f, -10.f, 10.f);
		//PM_shadow = glm::ortho(-20.f, 20.f, -20.f, 20.f, -20.f, 20.f);
		//PM_shadow = glm::ortho(-30.f, 30.f, -30.f, 30.f, -30.f, 30.f);
		//PM_shadow = glm::ortho(-40.f, 40.f, -40.f, 40.f, -40.f, 40.f);
		PM_shadow = glm::ortho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);
		VM_shadow = glm::inverse(shadowObjTemp->RM);

		if (type == "UBO")
			depth_or_depthBiasMVP = biasM * PM_shadow * VM_shadow * MM;

		else if (type == "render")
			depth_or_depthBiasMVP = PM_shadow * VM_shadow * MM;
	}

	else if (shadowObjTemp->camLiType->val_s == "POINT")
	{
		if (type == "render")
			depth_or_depthBiasMVP = myAbj.PM_cube * myAbj.VM_cube * myAbj.MM_cube * MM;
	}

	else if (shadowObjTemp->camLiType->val_s == "SPOT")
	{
		PM_shadow = glm::perspective(45.f, 1.f, 2.f, 200.f);
		//PM_shadow = glm::perspective(45.f, 1.f, 2.f, 100.f);

		VM_shadow = glm::lookAt(glm::vec3(shadowObjTemp->tx->val_f, shadowObjTemp->ty->val_f, shadowObjTemp->tz->val_f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

		depth_or_depthBiasMVP = PM_shadow * VM_shadow * MM; //

		if (type == "UBO")
			depth_or_depthBiasMVP = biasM * PM_shadow * VM_shadow * MM;

		else if (type == "render")
			depth_or_depthBiasMVP = PM_shadow * VM_shadow * MM;
	}

	if (type == "UBO")
		glNamedBufferSubData(myAbj.uboLight, myAbj.lightIter * sizeof(LightData) - sizeof(glm::mat4), sizeof(depth_or_depthBiasMVP), &depth_or_depthBiasMVP);

	else if (type == "render")
	{
		auto &proH = myAbj.pro;

		glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "depthMVP"), 1, GL_FALSE, &depth_or_depthBiasMVP[0][0]);
	}
}

void Object::proUse()
{
	for (auto &i : myAbj.GLDataSh)
	{
		auto proN = myAbj.proN;

		if (i.obj.get() == this)
		{
			auto &proH = myAbj.pro;
			auto proN = myAbj.proN;

			if (proN == "pGBufferAnim" || proN == "pShadowAnim" || proN == "pStencilGeoAnim" || proN == "pStencilHiAnim" || proN == "pDepthRevAnim" || proN == "pColorIDAnim" || proN == "pNormalRuffAnim")
			{
				for (auto &j : animBones)
				{
					//cout << "bone name = " << j.name.c_str() << endl; //"gBones[0]/1/2/3"
					//cout << "j.animatedXform = " << glm::to_string(j.animatedXform) << endl;

					glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, j.name.c_str()), 1, GL_TRUE, &j.animatedXform[0][0]);
				}
			}

			if ((proN == "pGBuffer" || proN == "pGBufferAnim" || proN == "pTransp") && myAbj.lightCt > 0) //
			{
				//per frame light buffer UBO subdata used AFTER dirty shadow gen w/ writeShadow()
				myAbj.lightIter = 1;

				for (auto &j : myAbj.allCamLi)
				{
					if (j->v->val_b && j->camLiTypeGet("light"))
					{
						myAbj.shadowObjUBO = j;
						shadowMatrixPass("UBO");
						++myAbj.lightIter;
					}
				}
			}

			//OBJ MATRIX
			glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MVP"), 1, GL_FALSE, &MVP[0][0]);
			glProgramUniformMatrix3fv(proH, glGetUniformLocation(proH, "NM"), 1, GL_FALSE, &NM[0][0]);

			glm::vec4 comboU;

			if (myAbj.proN == "pBB")
			{
				auto temp = (selected) ? myAbj.Csel : Cwire->val_3;
				comboU = glm::vec4(temp, 1.f);

				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.r);
			}

			if (myAbj.proN == "pColorID" || myAbj.proN == "pColorIDAnim")
			{
				comboU = glm::vec4(Crand, 1.f);

				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.r);
			}

			if (proN == "pWireframe")
			{
				auto temp = (selected) ? myAbj.Csel : Cwire->val_3;
				comboU = glm::vec4(temp, 1.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Cwire"), 1, &comboU.x);
			}

			if (proN == "pCursor")
			{
				float clipSpaceX = myAbj.pMouseNew.x / myAbj.width;
				float clipSpaceY = myAbj.pMouseNew.y / myAbj.height;

				float viewSpaceX = clipSpaceX * 2.f - 1.f;
				float viewSpaceY = -(clipSpaceY * 2.f - 1.f);

				//float aspectRatio = myAbj.width / myAbj.height;
				float aspectRatio = 1.f / ((float)myAbj.width / (float)myAbj.height);

				glm::vec3 cursorP(viewSpaceX, viewSpaceY, 0.f);
				//glm::vec3 cursorS(.1f);

				glm::vec3 cursorS;
				cursorS.x = .06f * aspectRatio;
				cursorS.y = .06f * 1.f;
				cursorS.z = .06f * 1.f;

				glm::mat4 cursorMM = glm::translate(glm::mat4(1.f), cursorP) * glm::scale(glm::mat4(1.f), cursorS); //
				glm::mat4 cursorMVP = cursorMM;

				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "cursorMVP"), 1, GL_FALSE, &cursorMVP[0][0]);

				for (auto &j : myAbj.allTexMaps)
				{
					if (myAbj.cursorName == j.name)
					{
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
						//glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex1_64);
					}

					//if (j.name == "cursorD0")
					//	glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
				}
			}

			if (proN == "pSky")
			{
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "PMinv_cube"), 1, GL_FALSE, &myAbj.PMinv_cube[0][0]);
				glBindTextureUnit(0, myAbj.cubeM_specular_32);
			}

			else if (proN == "pGrid")
			{
				comboU = glm::vec4(myAbj.Cgrid, 1.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Cgrid"), 1, &comboU.x);
			}

			else if (proN == "pShadow" || proN == "pShadowAnim") //WRITE TO A SINGLE LIGHT to create shadowmap
			{
				shadowMatrixPass("render");
			}

			else if (proN == "pTransp")
			{
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MV"), 1, GL_FALSE, &MV[0][0]);
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MM"), 1, GL_FALSE, &MM[0][0]);

				comboU = glm::vec4(ior->val_f, ruffOren->val_f, Ko->val_f, myAbj.debug0);

				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				auto shadowCastF = (shadowCast->val_b) ? 1.f : 0.f;
				auto rippleF = (ripple->val_b) ? 1.f : 0.f;
				comboU = glm::vec4(ruffA->val_2, shadowCastF, rippleF);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.lightCt, myAbj.dudvTime, 0.f, myAbj.myFSQ->Kgi->val_f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU2"), 1, &comboU.x);

				glProgramUniform1i(proH, glGetUniformLocation(proH, "debugTgl0"), myAbj.debug0);

				tileMaps(proH);

				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == albedoM->val_s)
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);

					else if (j.name == alphaM->val_s)
						glProgramUniformHandleui64ARB(proH, 1, topLayer(j).tex0_64);

					else if (j.name == normalM->val_s)
						glProgramUniformHandleui64ARB(proH, 4, topLayer(j).tex0_64);

					else if (j.name == ruffM->val_s)
						glProgramUniformHandleui64ARB(proH, 5, topLayer(j).tex0_64);
				}

				glBindTextureUnit(7, myAbj.cubeM_specular_32);
				glBindTextureUnit(8, myAbj.cubeM_irradiance_32);
			}

			else if (proN == "pTranspComp")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.gBuf7_64);
			}

			else if (proN == "pGBuffer" || proN == "pGBufferAnim")
			{
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MV"), 1, GL_FALSE, &MV[0][0]);
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MM"), 1, GL_FALSE, &MM[0][0]);

				comboU = glm::vec4(ior->val_f, ruffOren->val_f, Ko->val_f, myAbj.debug0);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				auto shadowCastF = (shadowCast->val_b) ? 1.f : 0.f;
				auto rippleF = (ripple->val_b) ? 1.f : 0.f;
				comboU = glm::vec4(ruffA->val_2, shadowCastF, rippleF);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.lightCt, myAbj.dudvTime, 0.f, myAbj.myFSQ->Kgi->val_f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU2"), 1, &comboU.x);

				glProgramUniform1i(proH, glGetUniformLocation(proH, "debugTgl0"), myAbj.debug0);

				tileMaps(proH);

				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == albedoM->val_s)
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);

					else if (j.name == alphaM->val_s)
						glProgramUniformHandleui64ARB(proH, 1, topLayer(j).tex0_64);

					else if (j.name == anisoM->val_s)
					{
						float anisoType;

						if (anisoM->val_s == "BLANK_ANISO")
							anisoType = 0.f;

						else if (anisoM->val_s == "VIEW_ANISO")
							anisoType = 1.f;

						else //CUSTOM MAP
							anisoType = 2.f;

						glProgramUniform1f(proH, glGetUniformLocation(proH, "anisoType"), anisoType);
						glProgramUniformHandleui64ARB(proH, 2, topLayer(j).tex0_64);
					}

					else if (j.name == metallicM->val_s)
						glProgramUniformHandleui64ARB(proH, 3, topLayer(j).tex0_64);

					else if (j.name == normalM->val_s)
						glProgramUniformHandleui64ARB(proH, 4, topLayer(j).tex0_64);

					else if (j.name == ruffM->val_s)
						glProgramUniformHandleui64ARB(proH, 5, topLayer(j).tex0_64);

					else if (j.name == dudvM->val_s)
						glProgramUniformHandleui64ARB(proH, 6, topLayer(j).tex0_64);
				}

				glBindTextureUnit(7, myAbj.cubeM_specular_32);
				glBindTextureUnit(8, myAbj.cubeM_irradiance_32);

				//for future release : shadows only need to be generated up at a certain distance (25, 50)
				//in pShadow only render objs at dist < 50
				//in gBuffer only calc lights for objs at dist < 50

				int start = 9;
				int realIdx = 0;

				//PT SHADOWS SHOULD BE 9 / 10
				for (uint j = 0; j < myAbj.allShadow.size(); ++j)
				{
					for (uint k = 0; k < myAbj.allCamLi.size(); ++k)
					{
						if (myAbj.allShadow[j].name == myAbj.allCamLi[k]->name->val_s)
						{
							if (myAbj.allCamLi[k]->camLiType->val_s == "POINT")
							{
								//cout << "POINT SHADOWS for : " << myAbj.allShadow[j].name << " " << start + realIdx << " " << start << " " << realIdx << endl;
								glBindTextureUnit(start + realIdx, myAbj.allShadow[j].tex1_32);
								++realIdx;
							}
						}
					}
				}

				start = 11;
				realIdx = 0;

				//DIR / SPOT SHADOWS SHOULD BE 11 / 12 / 13
				for (uint j = 0; j < myAbj.allShadow.size(); ++j)
				{
					for (uint k = 0; k < myAbj.allCamLi.size(); ++k)
					{
						if (myAbj.allShadow[j].name == myAbj.allCamLi[k]->name->val_s)
						{
							if (myAbj.allCamLi[k]->camLiType->val_s == "DIR" || myAbj.allCamLi[k]->camLiType->val_s == "SPOT")
							{
								//cout << "SPOT SHADOWS for : " << myAbj.allShadow[j].name << " " << start + realIdx << " " << start << " " << realIdx << " " << j << endl;


								glProgramUniformHandleui64ARB(proH, start + realIdx, myAbj.allShadow[j].tex0_64);
								//glBindTextureUnit(start + realIdx, myAbj.allShadow[j].tex0_64);

								++realIdx;

								//glProgramUniformHandleui64ARB(proH, 11, myAbj.allShadow[j].tex0_64);
								//glProgramUniformHandleui64ARB(proH, 12, myAbj.allShadow[j].tex0_64);
							}		
						}
					}
				}

			}

			else if (proN == "pBill")
			{
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MM"), 1, GL_FALSE, &MM[0][0]);

				glm::vec3 camRight_WS(VM[0][0], VM[1][0], VM[2][0]);
				comboU = glm::vec4(camRight_WS, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "camRight_WS"), 1, &comboU.x);

				glm::vec3 camUP_WS(VM[0][1], VM[1][1], VM[2][1]);
				comboU = glm::vec4(camUP_WS, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "camUp_WS"), 1, &comboU.x);
			}

			else if (proN == "pNormalRuff" || proN == "pNormalRuffAnim")
			{
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MM"), 1, GL_FALSE, &MM[0][0]);

				comboU = glm::vec4(ssrInten->val_f, 0.f, 0.f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				tileMaps(proH);

				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == ruffM->val_s)
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
				}
			}

			else if (proN == "pDown")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.downSamp_64);
				glProgramUniform2fv(proH, glGetUniformLocation(proH, "texelSize"), 1, &myAbj.texelSize.r);
			}

			else if (proN == "pSSAO_32" || proN == "pSSAO_64")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.gBuf5_64);
				glBindTextureUnit(1, myAbj.gBuf_DS_32);

				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == "rand")
						glProgramUniformHandleui64ARB(proH, 2, topLayer(j).tex0_64);
				}

				comboU = glm::vec4(ssaoBias->val_f, ssaoInten->val_f, ssaoRad->val_f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
			}

			else if (proN == "pGauss")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.rttGaussIn64);
				glProgramUniform1i(proH, glGetUniformLocation(proH, "gaussStage"), gaussStage);
			}

			else if (proN == "pDef")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.gBuf0_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.gBuf1_64);
				glProgramUniformHandleui64ARB(proH, 2, myAbj.gBuf2_64);
				glProgramUniformHandleui64ARB(proH, 3, myAbj.gBuf3_64);
				glProgramUniformHandleui64ARB(proH, 4, myAbj.gBuf4_64);
				glProgramUniformHandleui64ARB(proH, 5, myAbj.gBuf5_64);
				glProgramUniformHandleui64ARB(proH, 8, myAbj.ssaoGaussN.tex1_64);
				glProgramUniformHandleui64ARB(proH, 9, myAbj.bgN.tex0_64); // sky

				for (auto &j : myAbj.allCubeIrradSpec)
				{
					if (j.name == myAbj.myCube)
					{
						for (auto &k : myAbj.allTexMaps)
						{
							if (k.name == j.irrad)
								myAbj.cubeM_irradiance_32 = k.layer[0].tex0_32;

							else if (k.name == j.spec)
								myAbj.cubeM_specular_32 = k.layer[0].tex0_32;
						}
					}
				}

				glBindTextureUnit(10, myAbj.cubeM_specular_32);
				glBindTextureUnit(11, myAbj.cubeM_irradiance_32);
				glBindTextureUnit(12, myAbj.gBuf_DS_32);

				comboU = glm::vec4(myAbj.myFSQ->Kgi->val_f, myAbj.lightCt, myAbj.debug0, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				float runningTime = (float)((double)GetTickCount() - (double)myAbj.m_rippleStartTime) / 1000.f; //
				glProgramUniform1f(proH, glGetUniformLocation(proH, "time"), runningTime);

				comboU = glm::vec4(myAbj.selCamLi->farClip->val_f, myAbj.selCamLi->nearClip->val_f, 0.f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "farNearClip"), 1, &comboU.x);
			}

			else if (proN == "pLumaInit")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.defN.tex0_64);
			}

			else if (proN == "pLumaAdapt")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.lumaAdaptN[!myAbj.currLum].tex0_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.lumaInitN.tex0_64);

				glProgramUniform1f(proH, glGetUniformLocation(proH, "dTime"), myAbj.dTime);
			}

			else if (proN == "pBloom")
			{
				for (int j = 0; j < 6; ++j)
					glProgramUniformHandleui64ARB(proH, j, myAbj.bloomGaussN[j].tex1_64);

				glProgramUniformHandleui64ARB(proH, 6, myAbj.defN.tex0_64);

				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == lensM->val_s)
						glProgramUniformHandleui64ARB(proH, 7, topLayer(j).tex0_64);
				}

				comboU = glm::vec4(myAbj.myFSQ->bloomInten->val_f, myAbj.myFSQ->bloomLensInten->val_f, myAbj.debug0, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
			}

			else if (proN == "pTonemap")
			{
				//bloom
				//glProgramUniformHandleui64ARB(proH, 0, myAbj.defN.tex0_64); //no bloom
				glProgramUniformHandleui64ARB(proH, 0, myAbj.bloomN.tex0_64); //bloom
				glProgramUniformHandleui64ARB(proH, 1, myAbj.lumaAdaptN[myAbj.currLum].tex0_64);
				glProgramUniformHandleui64ARB(proH, 2, myAbj.bgN.tex1_64);

				comboU = glm::vec4(log(myAbj.myFSQ->expo->val_f), myAbj.myFSQ->adaptAuto->val_b, myAbj.myFSQ->vign->val_b, myAbj.myFSQ->vignDist->val_f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.debug0, 0.f, 0.f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);
			}

			else if (proN == "pFxaa")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.tonemapN.tex0_64);

				comboU = glm::vec4(myAbj.edgeDetect_mode, myAbj.myFSQ->fxaaSubPix->val_f, myAbj.myFSQ->fxaaEdgeThr->val_f, myAbj.myFSQ->fxaaEdgeThrMin->val_f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
			}

			else if (proN == "pSSR")
			{
				// projection matrix that maps to screen pixels (not NDC)
				auto screenScaleM = glm::scale(glm::mat4(1.f), glm::vec3(myAbj.width, myAbj.height, 1.f));

				auto trs = glm::mat4(1.f);
				trs[0][0] = trs[0][3] = trs[1][1] = trs[1][3] = .5f;

				auto PM_d3d = PM;
				PM_d3d[2][3] = PM_d3d[3][2];
				PM_d3d[3][2] = PM[2][3];

				auto PM_SS_d3d = PM_d3d * trs * screenScaleM;
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "PM_SS_d3d"), 1, GL_FALSE, &PM_SS_d3d[0][0]);

				glProgramUniformHandleui64ARB(proH, 0, myAbj.normalRuff0_64); //N_VS, ruffM
				glBindTextureUnit(1, myAbj.gBufAddT_DS_32);
				glProgramUniformHandleui64ARB(proH, 2, myAbj.depthRevN.DS_64);
				glProgramUniformHandleui64ARB(proH, 3, myAbj.tonemapN.tex0_64); // w/ giz
				//glProgramUniformHandleui64ARB(proH, 3, myAbj.myGL->tonemapN.tex1_64); // no giz

				comboU = glm::vec4(myAbj.selCamLi->farClip->val_f, myAbj.selCamLi->nearClip->val_f, myAbj.myFSQ->ssrIter->val_i, myAbj.myFSQ->ssrRefine->val_i);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.myFSQ->ssrPixStride->val_i, myAbj.myFSQ->ssrPixStrideZ->val_f, myAbj.myFSQ->ssrPixZSize->val_f, myAbj.myFSQ->ssrMaxRayDist->val_f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.myFSQ->ssrEdgeFade->val_f, myAbj.myFSQ->ssrEyeFade0->val_f, myAbj.myFSQ->ssrEyeFade1->val_f, myAbj.debug0);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU2"), 1, &comboU.x);
			}

			else if (proN == "pFinal")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.fxaaN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.ssrN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 2, myAbj.cursorN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 3, myAbj.defN.tex0_64);
				//glProgramUniformHandleui64ARB(proH, 4, myAbj.brushN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 4, myAbj.brushN.tex1_64);
				glProgramUniformHandleui64ARB(proH, 5, myAbj.normalRuff1_64);
				glProgramUniformHandleui64ARB(proH, 6, myAbj.gBuf7_64); //BOIT revealage
				glProgramUniformHandleui64ARB(proH, 7, myAbj.billN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 8, myAbj.tonemapN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 9, myAbj.bgN.tex1_64); // sky
				glProgramUniformHandleui64ARB(proH, 10, myAbj.gBuf6_64);

				comboU = glm::vec4(myAbj.rezGate_LD, myAbj.rezGate_RU);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "LDRU"), 1, &comboU.x);

				bool rezGateTgl = (myAbj.selB == myAbj.selCamLi) ? 1 : 0;
				comboU = glm::vec4(rezGateTgl, myAbj.dragDrop, myAbj.debug0, myAbj.dudvTime);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
			}

			else if (proN == "pStereoPost")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.fxaaN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.ssrN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 2, myAbj.defN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 5, myAbj.normalRuff1_64);
				glProgramUniformHandleui64ARB(proH, 6, myAbj.gBuf7_64); //BOIT revealage
			}

			else if (proN == "pStereoPrev")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.stereoPrevN.tex0_64);
			}

			else if (proN == "pFilterSizeMatch")
			{
				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == "rand")
						glProgramUniformHandleui64ARB(proH, 2, topLayer(j).tex0_64);
				}
			}

			else if (proN == "pFinalStereo")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.stereoN[0].tex0_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.stereoN[1].tex0_64);

				comboU = glm::vec4(myAbj.rezGate_LD, myAbj.rezGate_RU);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "LDRU"), 1, &comboU.x);

				bool rezGateTgl = (myAbj.selB == myAbj.selCamLi) ? 1 : 0;
				comboU = glm::vec4(rezGateTgl, myAbj.dragDrop, myAbj.debug0, myAbj.dudvTime);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.selCamLi->farClip->val_f, myAbj.selCamLi->nearClip->val_f, myAbj.showHideTaskbar, myAbj.stereoMethod);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.channel, 0.f, 0.f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU2"), 1, &comboU.x);
			}

			else if (proN == "pEdgeDetect")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.alphaGaussN.tex1_64);

				//comboU = glm::vec4(myAbj.edgeDetect_mode, myAbj.edgeThr->val_f, 0.f, 0.f);
				comboU = glm::vec4(myAbj.edgeDetect_mode, .6f, 0.f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
			}

			else if (proN == "pPaintStroke")
			{
				for (auto &j : myAbj.allTexMaps)
				{
					if (myAbj.cursorName == j.name)
					{
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
						//glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex1_64);
					}

					//if (j.name == myAbj.selEraser->name)
					//{
					//	if (myAbj.paintType == "ERASER")
					//	{
					//		glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
					//	}
					//}
				}

				glProgramUniform4fv(proH, glGetUniformLocation(proH, "brushRGBA"), 1, &myAbj.brushRGBA.x);
			}

			else if (proN == "pEraseMix")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.brushBGN.tex1_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.eraserN.tex0_64);
			}

			else if (proN == "pCopyTex")
			{
				if (myAbj.copyTgt == 0)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.brushTempN.tex0_64);

				else if (myAbj.copyTgt == 1)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.brushTempN.tex1_64);

				else if (myAbj.copyTgt == 2)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.brushBGN.tex0_64);

				else if (myAbj.copyTgt == 3)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.brushBGN.tex1_64);

				else if (myAbj.copyTgt == 4)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.brushN.tex0_64);

				else if (myAbj.copyTgt == 5)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.brushN.tex1_64);

				else if (myAbj.copyTgt == 10)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.myLayerIdx.layer[0].tex0_64);

				else if (myAbj.copyTgt == 11)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.eraserN.tex0_64);

				else if (myAbj.copyTgt == 12)
					glProgramUniformHandleui64ARB(proH, 0, myAbj.eraserN.tex1_64);

				else if (myAbj.copyTgt == 99)
				{
					glProgramUniformHandleui64ARB(proH, 0, myAbj.eraserN.tex1_64);

					for (auto &j : myAbj.allTexMaps)
					{
						if (j.name == "debugBG")
							glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
					}
				}
			}

			else if (proN == "pPaintProj")
			{
				glProgramUniformHandleui64ARB(proH, 0, myAbj.brushN.tex0_64);
				glProgramUniformHandleui64ARB(proH, 1, myAbj.myLayerIdx.layer[0].tex1_64);

				auto ProjectorM = biasM * myAbj.selCamLi->PM * myAbj.selCamLi->VM * MM;
				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "ProjectorM"), 1, GL_FALSE, &ProjectorM[0][0]);
			}

			else if (proN == "pAlphaAsRGBA")
			{
				glProgramUniformHandleui64ARB(proH, 0, topLayer(myAbj.sobelMap).tex0_64);
			}

			else if (proN == "pBlendMode")
			{
				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == "REPLACEME")
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
				}
			}

			else if (proN == "pGiz")
			{
				comboU = glm::vec4(Cgiz, 1.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Cgiz"), 1, &comboU.x);
			}

			else if (proN == "pGiz_circ2")
			{
				float myBorder = .1f;
				glProgramUniform1fv(proH, glGetUniformLocation(proH, "border"), 1, &myBorder);

				comboU = glm::vec4(Cgiz, 1.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Cgiz"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.selCamLi->rightO, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "circRight"), 1, &comboU.x);

				comboU = glm::vec4(myAbj.selCamLi->upO, 1);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "PM"), 1, GL_FALSE, &PM[0][0]);
			}

			else if (proN == "pGiz_circ")
			{
				comboU = glm::vec4(Cgiz, 1.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Cgiz"), 1, &comboU.x);

				if (type == "GIZ_CIRC")
				{
					comboU = glm::vec4(myAbj.selCamLi->rightO, 0.f);
					glProgramUniform4fv(proH, glGetUniformLocation(proH, "circRight"), 1, &comboU.x);

					comboU = glm::vec4(myAbj.selCamLi->upO, 1);
					glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
				}

				else if (type == "GIZ_CIRC_HALF")
				{
					glm::vec3 axX(1.f, 0.f, 0.f);
					glm::vec3 axY(0.f, 1.f, 0.f);
					glm::vec3 axZ(0.f, 0.f, 1.f);

					if (myAbj.gizSpace == "local" && myAbj.selB)
					{
						glm::vec4 xLocal(myAbj.selB->MM * glm::vec4(axX, 0.f));
						axX = glm::normalize(glm::vec3(xLocal));

						glm::vec4 yLocal(myAbj.selB->MM * glm::vec4(axY, 0.f));
						axY = glm::normalize(glm::vec3(yLocal));

						glm::vec4 zLocal(myAbj.selB->MM * glm::vec4(axZ, 0.f));
						axZ = glm::normalize(glm::vec3(zLocal));
					}

					glm::vec3 circHalfRight, circHalfFront;

					if (name->val_s == "gizCircHalfX")
					{
						circHalfRight = glm::normalize(glm::cross(myAbj.selCamLi->lookO, axX));
						circHalfFront = glm::normalize(glm::cross(circHalfRight, axX));
						myAbj.gizHoverCheckX = circHalfFront;
					}

					else if (name->val_s == "gizCircHalfY")
					{
						circHalfRight = glm::normalize(glm::cross(myAbj.selCamLi->lookO, axY));
						circHalfFront = glm::normalize(glm::cross(circHalfRight, axY));
						myAbj.gizHoverCheckY = circHalfFront;
					}

					else if (name->val_s == "gizCircHalfZ")
					{
						circHalfRight = glm::normalize(glm::cross(myAbj.selCamLi->lookO, axZ));
						circHalfFront = glm::normalize(glm::cross(circHalfRight, axZ));
						myAbj.gizHoverCheckZ = circHalfFront;
					}
					 
					comboU = glm::vec4(circHalfRight, 0.f);
					glProgramUniform4fv(proH, glGetUniformLocation(proH, "circRight"), 1, &comboU.x);

					comboU = glm::vec4(circHalfFront, 0);
					glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
				}
			}

			else if (proN == "pSelRect")
			{
				glm::vec4 LDRU(myAbj.selRect_LD, myAbj.selRect_RU);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "LDRU"), 1, &LDRU.x);
			}

			else if (proN == "pStencilHi" || proN == "pStencilHiAnim")
			{
				comboU = glm::vec4(myAbj.Csel, 1.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "CstencilHi"), 1, &comboU.x);
			}

			else if (proN == "pTxtDie")
			{
				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == "atlas")
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
				}

				comboU = glm::vec4(myAbj.Ctxt, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Ctxt"), 1, &comboU.x);

				glm::vec2 txtCellSize(1.f / 16, (300.f / 384) / 6);
				glm::vec2 txtCellOffset(.5f / 256);

				auto txtSize = 3.f;
				//auto txtSize = .8f;


				glm::vec2 txtSizeUse(.75f * 16 / (myAbj.width / txtSize), .75f * 33.33 / (myAbj.height / txtSize));

				comboU = glm::vec4(txtCellSize, txtCellOffset);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				comboU = glm::vec4(txtSizeUse, txtOrigin);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);

				comboU = glm::vec4(dieMsgAlpha->val_f, 0.f, 0.f, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU2"), 1, &comboU.x);
				//vec4 comboU0; //vec4(Kgi, NUM_LIGHTS, debug0, 0.f)

			}

			//else if (proN == "pTxtDie")
			//{
			//	for (auto &j : myAbj.allTexMaps)
			//	{
			//		if (j.name == "atlas")
			//			glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
			//	}

			//	comboU = glm::vec4(myAbj.Ctxt, 0.f);
			//	glProgramUniform4fv(proH, glGetUniformLocation(proH, "Ctxt"), 1, &comboU.x);

			//	glm::vec2 txtCellSize(1.f / 16, (300.f / 384) / 6);
			//	glm::vec2 txtCellOffset(.5f / 256);

			//	//auto txtSize = 4.8f;
			//	auto txtSize = 3.f;

			//	//auto txtSize = 1.f;
			//	//auto txtSize = .8f;


			//	glm::vec2 txtSizeUse(.75f * 16 / (myAbj.width / txtSize), .75f * 33.33 / (myAbj.height / txtSize));

			//	comboU = glm::vec4(txtCellSize, txtCellOffset);
			//	glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

			//	comboU = glm::vec4(txtSizeUse, txtOrigin);
			//	glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);

			//	comboU = glm::vec4(dieMsgAlpha->val_f, 0.f, 0.f, 0.f);
			//	glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU2"), 1, &comboU.x);
			//	//vec4 comboU0; //vec4(Kgi, NUM_LIGHTS, debug0, 0.f)

			//}

			else if (proN == "pTxt")
			{
				for (auto &j : myAbj.allTexMaps)
				{
					if (j.name == "atlas")
						glProgramUniformHandleui64ARB(proH, 0, topLayer(j).tex0_64);
				}

				comboU = glm::vec4(myAbj.Ctxt, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "Ctxt"), 1, &comboU.x);

				glm::vec2 txtCellSize(1.f / 16, (300.f / 384) / 6);
				glm::vec2 txtCellOffset(.5f / 256);

				auto txtSize = .8f;
				glm::vec2 txtSizeUse(.75f * 16 / (myAbj.width / txtSize), .75f * 33.33 / (myAbj.height / txtSize));

				comboU = glm::vec4(txtCellSize, txtCellOffset);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);

				comboU = glm::vec4(txtSizeUse, txtOrigin);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU1"), 1, &comboU.x);
			}

			else if (proN == "pVolumeLight")
			{
				cout << "pVolumeLight for : " << name->val_s << endl;

				glProgramUniformMatrix4fv(proH, glGetUniformLocation(proH, "MV"), 1, GL_FALSE, &MV[0][0]);

				comboU = glm::vec4(parentTo->Cl->val_3, 0.f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "parentCl"), 1, &comboU.x);

				auto volTipView = glm::vec3(VM * glm::vec4(parentTo->tx->val_f, parentTo->ty->val_f, parentTo->tz->val_f, 1.f));

				comboU = glm::vec4(volTipView, parentTo->volDist->val_f);
				glProgramUniform4fv(proH, glGetUniformLocation(proH, "comboU0"), 1, &comboU.x);
			}
		}
	}
}

void Object::render()
{
	if (twoSided->val_s == "BLACK" || twoSided->val_s == "FULL")
		glDisable(GL_CULL_FACE);

	proUse();

	if (bb->val_b)
	{
		glLineWidth(2.f);

		glBindVertexArray(myAbj.myBB->VAO);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * 2));
		glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * 2));

		glLineWidth(1.f);
	}

	else
	{
		if (type == "SELRECT")
		{
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		else if (type == "FBO")
		{
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		else if (type == "GRID")
		{
			glLineWidth(2.f);

			glBindVertexArray(VAO);

			int gridLines = myAbj.gridLines + 1;
			for (int i = 0; i < gridLines; ++i)
				glDrawArrays(GL_LINE_STRIP, gridLines * i, gridLines);

			glLineWidth(1.f);
		}

		else if (type == "OBJ")
		{
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)idxE.size(), GL_UNSIGNED_INT, 0);
		}

		else if (type == "BILL")
		{
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)idxE.size(), GL_UNSIGNED_INT, 0);
		}

		else if (type == "GIZ_CUBE")
		{
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)idxE.size(), GL_UNSIGNED_INT, 0);
		}

		else if (type == "VOL")
		{
			glBindVertexArray(myAbj.myVolCone->VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)myAbj.myVolCone->idxE.size(), GL_UNSIGNED_INT, 0);
		}

		else if (type == "CAMLI")
		{
			glLineWidth(2.f);
			glDisable(GL_DEPTH_TEST);

			if (camLiTypeGet("cam"))
			{
				glBindVertexArray(VAO);
				glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)pE.size());
			}

			else
			{
				if (camLiType->val_s == "DIR")
				{
					glBindVertexArray(VAO);
					glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)pE.size());
				}

				else if (camLiType->val_s == "POINT")
				{
					glBindVertexArray(VAO);
					glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)pE.size());
				}

				else if (camLiType->val_s == "SPOT")
				{
					glBindVertexArray(VAO);
					glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)pE.size());
				}
			}

			glLineWidth(1.f);
			glEnable(GL_DEPTH_TEST);
		}

		else if (type == "TXT")
		{
			glBindVertexArray(VAO);
			glEnableVertexArrayAttrib(VAO, 0);
			glDrawArrays(GL_POINTS, 0, (GLsizei)strlen(txt2D));
		}

		else if (type == "GIZ_CONE" || type == "GIZ_DUAL_HANDLE")
		{
			if (type == "GIZ_DUAL_HANDLE")
				glDisable(GL_CULL_FACE);

			glBindVertexArray(VAO);
			glEnableVertexArrayAttrib(VAO, 0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)pE.size());

			if (type == "GIZ_DUAL_HANDLE")
				glEnable(GL_CULL_FACE);
		}

		else if (type == "GIZ_CIRC" || type == "GIZ_CIRC_HALF" || type == "GIZ_LINE")
		{
			glLineWidth(3.f);

			glBindVertexArray(VAO);
			glEnableVertexArrayAttrib(VAO, 0);
			glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)pE.size());

			glLineWidth(1.f);
		}

		else if (type == "GIZ_CUBE")
		{
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)idxE.size(), GL_UNSIGNED_INT, 0);
		}
	}

	if (twoSided->val_s == "BLACK" || twoSided->val_s == "FULL")
		glEnable(GL_CULL_FACE);
}

void Object::deleteVAO_VBO()
{
	glGetError();

	for (auto it = myAbj.GLDataSh.begin(); it != myAbj.GLDataSh.end(); )
	{
		if ((*it).obj.get() == this)
		{
			glDeleteBuffers(1, &(*it).VBO_P);
			glDeleteBuffers(1, &(*it).VBO_UV);
			glDeleteBuffers(1, &(*it).VBO_T);
			glDeleteBuffers(1, &(*it).VBO_N);
			glDeleteBuffers(1, &(*it).VBO_IDX);
			glErrorPrint("Couldnt delete VBOs");

			it = myAbj.GLDataSh.erase(it);
		}

		else
			++it;
	}

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	VAO_loaded = 0;

	glErrorPrint("Couldnt delete VAOs");
}

void Object::setAnim(string animName)
{
	for (auto &i : myAbj.aiAnimScenes)
	{
		if (i.nameIdx.name == animName)
		{
			curSceneNI.name = i.nameIdx.name;
			curSceneNI.idx = i.nameIdx.idx;
		}
	}
}

void Object::boneTransformGrp_AI(int grpIdx, uint numBones)
{
	//cout << "myAbj.aiAnimScenes.size() = / numBones / name = " << myAbj.aiAnimScenes.size() << " " << numBones << " " << name->val_s << endl;

	for (uint i = 0; i < myAbj.aiAnimScenes.size(); i++)
	{
		if ((myAbj.aiAnimScenes[i].animated == 1) && (i == grpIdx))
		{
			vector<glm::mat4> Transforms;
			boneTransform_AI(Transforms, grpIdx, numBones);
			animBones.clear();

			for (uint j = 0; j < numBones; j++)
			{
				string gBonesName;
				gBonesName.append("gBones[");
				gBonesName.append(to_string(j));
				gBonesName.append("]");

				AnimBone xformNameCombo;
				xformNameCombo.animatedXform = Transforms[j];
				xformNameCombo.name = gBonesName;
				xformNameCombo.nameMesh = name->val_s;
				animBones.push_back(xformNameCombo);
			}
		}
	}
}

void Object::boneTransform_AI(vector<glm::mat4> &Transforms, int grpIdx, uint numBones)
{
	float TicksPerSecond = 24.f;
	float TimeInTicks = animationTime0 * TicksPerSecond;
	//float AnimationTime = fmod(TimeInTicks, 50.f); // duration

	float AnimationTime = fmod(TimeInTicks, (float)myAbj.aiAnimScenes[curSceneNI.idx].scene->mAnimations[0]->mDuration + 1.f); // duration

	Matrix4f Identity;
	Identity.InitIdentity();

	ApplyPose_AI(AnimationTime, myAbj.aiAnimScenes[curSceneNI.idx].scene->mRootNode, Identity, myAbj.aiAnimScenes[curSceneNI.idx].scene, grpIdx); // UNCOMMENT !!!!!


	Transforms.resize(numBones);

	for (uint i = 0; i < numBones; i++)
		Transforms[i] = m_BoneInfo[i].FinalTransformation; /////////
}

void Object::ApplyPose_AI(float AnimationTime, const aiNode *pNode, Matrix4f ParentTransform, const aiScene *scene, int grpIdx)
{
	string NodeName = pNode->mName.data;
	//cout << "NodeName = " << NodeName << endl;

	const aiAnimation* pAnimation = scene->mAnimations[0]; //

	Matrix4f NodeTransform = pNode->mTransformation;
	const aiNodeAnim *pNodeAnim = FindNodeAnim(pAnimation, NodeName); //find channel 0

	if (pNodeAnim)
	{
		//cout << "NodeName = " << NodeName << endl;

		aiQuaternion RotationQ;
		CalcInterpolatedRotationAI_stock(AnimationTime, pNodeAnim, RotationQ);
		Matrix4f RotationM = Matrix4f(RotationQ.GetMatrix());

		aiVector3D Translation;
		CalcInterpolatedPositionAI_stock(AnimationTime, pNodeAnim, Translation);
		Matrix4f TranslationM;
		TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);

		NodeTransform = TranslationM * RotationM;
	}

	//Matrix4f GlobalTransform = ParentTransform * NodeTransform;
	//Matrix4f GlobalTransform = NodeTransform;

	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end())
	{
		uint BoneIndex = m_BoneMapping[NodeName];

		Matrix4f usableGlobalInvXform;

		for (auto &i : myAbj.aiAnimScenes)
		{
			if (i.groupIdx == grpIdx)
				usableGlobalInvXform = i.globalInvXform;
		}

		m_BoneInfo[BoneIndex].FinalTransformation = toGLM(usableGlobalInvXform * ParentTransform * NodeTransform * m_BoneInfo[BoneIndex].BoneOffset);
	}

	for (uint i = 0; i < pNode->mNumChildren; i++)
	{
		ApplyPose_AI(AnimationTime, pNode->mChildren[i], ParentTransform * NodeTransform, scene, grpIdx);

	}
}

void Object::CalcInterpolatedPositionAI_stock(float AnimationTime, const aiNodeAnim *pNodeAnim, aiVector3D &out)
{
	if (pNodeAnim->mNumPositionKeys == 1)
	{
		//cout << "in frame size == 1...need at least 2 vals to interpolate...pos" << endl;
		out = pNodeAnim->mPositionKeys[0].mValue;
		//cout << "val = " << out.x << " " << out.y << " " << out.z << endl;
		return;
	}

	uint PositionIndex = FindPositionAI(AnimationTime, pNodeAnim);
	uint NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);

	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mRotationKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	Factor = glm::clamp(Factor, 0.f, 1.f);

	aiVector3D start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	aiVector3D end = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D delta = end - start;
	out = start + Factor * delta;

	//cout << fixed << "PositionIndex / start = " << PositionIndex << " " << start.x << " " << start.y << " " << start.z << endl;
	//cout << fixed << "PositionIndex / end = " << PositionIndex << " " << end.x << " " << end.y << " " << end.z << endl;

}

void Object::CalcInterpolatedRotationAI_stock(float AnimationTime, const aiNodeAnim *pNodeAnim, aiQuaternion &out)
{
	if (pNodeAnim->mNumRotationKeys == 1)
	{
		//cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
		out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	uint RotationIndex = FindRotationAI(AnimationTime, pNodeAnim);
	uint NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);

	//cout << "AnimationTime = " << AnimationTime << endl;
	//cout << "Rot / next index = " << RotationIndex << " " << NextRotationIndex << endl;

	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	Factor = glm::clamp(Factor, 0.f, 1.f);

	aiQuaternion startQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	aiQuaternion endQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;

	//cout << "RotationIndex / startQ = " << RotationIndex << " " << startQ.w << " " << startQ.x << " " << startQ.y << " " << startQ.z << endl;
	//cout << "RotationIndex / endQ = " << NextRotationIndex << " " << endQ.w << " " << endQ.x << " " << endQ.y << " " << endQ.z << endl;
	//cout << "RotationIndex / startQ = " << RotationIndex << " " << pNodeAnim->mRotationKeys[RotationIndex].mValue.w << " " << pNodeAnim->mRotationKeys[RotationIndex].mValue.x << " " << pNodeAnim->mRotationKeys[RotationIndex].mValue.y << " " << pNodeAnim->mRotationKeys[RotationIndex].mValue.z << endl;

	aiQuaternion::Interpolate(out, startQ, endQ, Factor);
	out = out.Normalize();
}

uint Object::FindRotationAI(float AnimationTime, const aiNodeAnim *pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (uint i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
	{
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
			return i;
	}

	return 0;
}

uint Object::FindPositionAI(float AnimationTime, const aiNodeAnim *pNodeAnim)
{
	for (uint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
			return i;
	}

	return 0;
}

const aiNodeAnim* Object::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
	for (uint i = 0; i < pAnimation->mNumChannels; i++)
	{
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

		if (string(pNodeAnim->mNodeName.data) == NodeName)
		{
			return pNodeAnim;
		}
	}

	return NULL;
}

glm::mat4 Object::toGLM(aiMatrix4x4 myAiMatrix)
{
	float bbb[16] =
	{
		(float)myAiMatrix[0][0], (float)myAiMatrix[0][1], (float)myAiMatrix[0][2], (float)myAiMatrix[0][3],
		(float)myAiMatrix[1][0], (float)myAiMatrix[1][1], (float)myAiMatrix[1][2], (float)myAiMatrix[1][3],
		(float)myAiMatrix[2][0], (float)myAiMatrix[2][1], (float)myAiMatrix[2][2], (float)myAiMatrix[2][3],
		(float)myAiMatrix[3][0], (float)myAiMatrix[3][1], (float)myAiMatrix[3][2], (float)myAiMatrix[3][3],

	};

	return glm::make_mat4(bbb);
}

glm::mat4 Object::toGLM(Matrix4f myMatrix)
{
	float bbb[16] =
	{
		(float)myMatrix[0], (float)myMatrix[1], (float)myMatrix[2], (float)myMatrix[3],
		(float)myMatrix[4], (float)myMatrix[5], (float)myMatrix[6], (float)myMatrix[7],
		(float)myMatrix[8], (float)myMatrix[9], (float)myMatrix[10], (float)myMatrix[11],
		(float)myMatrix[12], (float)myMatrix[13], (float)myMatrix[14], (float)myMatrix[15],

	};

	return glm::make_mat4(bbb);
}

glm::mat4 Object::toMatrix4f(glm::mat4 myMatrix)
{
	float bbb[16] =
	{
		(float)myMatrix[0][0], (float)myMatrix[1][0], (float)myMatrix[2][0], (float)myMatrix[3][0],
		(float)myMatrix[0][1], (float)myMatrix[1][1], (float)myMatrix[2][1], (float)myMatrix[3][1],
		(float)myMatrix[0][2], (float)myMatrix[1][2], (float)myMatrix[2][2], (float)myMatrix[3][2],
		(float)myMatrix[0][3], (float)myMatrix[1][3], (float)myMatrix[2][3], (float)myMatrix[3][3],

	};

	return glm::make_mat4(bbb);
}

void Object::boneTransformGrpABJ_solo()
{
	/* SINGLE ANIMATION */
	float TicksPerSecond = 24.f;
	float TimeInTicks = animationTime0 * TicksPerSecond;
	//float AnimationTime = fmod(TimeInTicks, 8.f); // duration
	float AnimationTime = fmod(TimeInTicks, 24.f); // duration
	//float AnimationTime = fmod(TimeInTicks, 50.f); // duration

	//float AnimationTime = fmod(TimeInTicks, 120.f); // duration

	//cout << "animationTime0 = " << animationTime0 << endl;
	//cout << fixed << "AnimationTime = " << AnimationTime << endl;
	//cout << "AnimationTime = " << AnimationTime << endl;

	//cout << "START ApplyPose" << endl;

	ApplyPose(AnimationTime, myAbj.allAnims[0].trackData[0], glm::mat4(1.f)); // UNCOMMENT !!!!!
}

void Object::ApplyPose(float AnimationTime, TrackData track, const glm::mat4 &ParentTransform)
{

	//for (uint i = 0; i < 24; i++) {
	//	//cout << "quat[i] = " << i << endl;
	//	glm::quat startQi = glm::quat(track.frameData[i].decompR);
	//	cout << i << " " << glm::to_string(startQi) << endl;
	//}


	glm::quat RotationQ;
	CalcInterpolatedRotationGLM_solo(AnimationTime, track, RotationQ);
	glm::mat4 RotationM = glm::toMat4(RotationQ);

	glm::vec3 Translation;
	CalcInterpolatedPositionGLM_solo(AnimationTime, track, Translation);
	glm::mat4 TranslationM = glm::translate(glm::mat4(1.f), Translation);

	//	// Combine the above transformations
	//glm::mat4 NodeTransform = TranslationM * RotationM;
	//glm::mat4 NodeTransform = RotationM;
	glm::mat4 NodeTransform = TranslationM;
	//glm::mat4 NodeTransform = glm::mat4(1.f);

	for (int i = 0; i < myBindSkeleton.skeletonCt; ++i)
	{
		if (myBindSkeleton.skeletonData[i].name == track.name)
		{
			string gBonesName;
			gBonesName.append("gBones[");
			gBonesName.append(to_string(track.id));
			gBonesName.append("]");

			AnimBone xformNameCombo;

			//cout << "myBindSkeleton.skeletonData[i].inverseBindpose = " << i << " " << glm::to_string(myBindSkeleton.skeletonData[i].inverseBindpose) << endl;


			//if (i == 0)
			//{
			//	NodeTransform = glm::mat4(1.f);
			//	NodeTransform[3][0] = 2.957f;

			//}

			//else
			//{
			//	NodeTransform = glm::mat4(1.f);
			//}

			glm::mat4 toMatrix4fGLMD = toMatrix4f(myBindSkeleton.skeletonData[i].inverseBindpose);
			cout << "myBindSkeleton.skeletonData[i].inverseBindpose = " << i << " " << glm::to_string(toMatrix4fGLMD) << endl;
			
			cout << "NodeTransform = " << glm::to_string(NodeTransform) << endl << endl;
			
			//glm::mat4 toMatrix4fGLM = toMatrix4f(ParentTransform * NodeTransform * myBindSkeleton.skeletonData[i].inverseBindpose);

			glm::mat4 toMatrix4fGLM = toMatrix4f(NodeTransform * myBindSkeleton.skeletonData[i].inverseBindpose);


			//xformNameCombo.animatedXform = ParentTransform * NodeTransform * myBindSkeleton.skeletonData[i].inverseBindpose;
			xformNameCombo.animatedXform = toMatrix4fGLM;

			//xformNameCombo.animatedXform = ParentTransform * NodeTransform;

			//xformNameCombo.animatedXform = glm::mat4(1.f);
			xformNameCombo.name = gBonesName;
			xformNameCombo.nameMesh = name->val_s;

			animBones.push_back(xformNameCombo);
		}
	}

	for (auto &i : myAbj.allAnims[0].trackData)
	{
		if (i.parent == track.name)
		{
			//cout << "found parent / child for : " << track.name << " " << i.name << endl;
			ApplyPose(AnimationTime, i, ParentTransform * NodeTransform);
		}
	}
}


uint Object::FindPositionGLM_solo(float AnimationTime, TrackData track)
{
	for (uint i = 0; i < track.frameData.size() - 1; i++)
	{
		if (AnimationTime < (float)track.frameData[i + 1].frame)
		{
			return i;
		}
	}

	return 0;
}

void Object::CalcInterpolatedPositionGLM_solo(float AnimationTime, TrackData track, glm::vec3 &out)
{
	if (track.frameData.size() == 1)
	{
		cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
		out = myAbj.allAnims[0].trackData[0].frameData[0].decompT;
		return;
	}

	uint PositionIndex = FindPositionGLM_solo(AnimationTime, track);

	uint NextPositionIndex = (PositionIndex + 1);
	//cout << "PositionIndex = " << PositionIndex << endl;

	//cout << "size of pos keys = " << track.frameData.size() << endl;

	float DeltaTime = (float)(track.frameData[NextPositionIndex].frame - track.frameData[PositionIndex].frame);
	//cout << "DeltaTime = " << DeltaTime << endl;

	float Factor = 0.f;
	Factor = (AnimationTime - (float)track.frameData[PositionIndex].frame) / DeltaTime;
	Factor = glm::clamp(Factor, 0.f, 1.f);
	//cout << "factor = " << Factor << endl;

	glm::vec3 start = track.frameData[PositionIndex].decompT;
	glm::vec3 end = track.frameData[NextPositionIndex].decompT;
	glm::vec3 delta = end - start;

	out = start + Factor * delta;

	//out = glm::lerp(start, end, Factor);

}

void Object::CalcInterpolatedRotationGLM_solo(float AnimationTime, TrackData track, glm::quat &out)
{

	//for (uint i = 0; i < 24; i++) {
	//	cout << "quat[i] = " << i << endl;
	//	glm::quat startQi = glm::quat(track.frameData[i].decompR);
	//	cout << glm::to_string(startQi);
	//}

	if (track.frameData.size() == 1)
	{
		cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
		out = myAbj.allAnims[0].trackData[0].frameData[0].decompR;
		return;
	}

	uint PositionIndex = FindPositionGLM_solo(AnimationTime, track);
	uint NextPositionIndex = (PositionIndex + 1);

	float DeltaTime = (float)(track.frameData[NextPositionIndex].frame - track.frameData[PositionIndex].frame);
	float Factor = 0.f;
	Factor = (AnimationTime - (float)track.frameData[PositionIndex].frame) / DeltaTime;
	Factor = glm::clamp(Factor, 0.f, 1.f);

	glm::quat startQ = glm::quat(track.frameData[PositionIndex].decompR);
	glm::quat endQ = glm::quat(track.frameData[NextPositionIndex].decompR);

	out = glm::slerp(startQ, endQ, Factor);
	out = glm::normalize(out);

	//cout << "RotationIndex / startQ = " << PositionIndex << " " << glm::to_string(startQ) << endl;
	//cout << "RotationIndex / endQ = " << NextPositionIndex << " " << glm::to_string(endQ) << endl;
}





//void Object::boneTransformGrpABJ_solo()
//{
//	/* SINGLE ANIMATION */
//	float TicksPerSecond = 24.f;
//	float TimeInTicks = animationTime0 * TicksPerSecond;
//	//float AnimationTime = fmod(TimeInTicks, 8.f); // duration
//	//float AnimationTime = fmod(TimeInTicks, 24.f); // duration
//	float AnimationTime = fmod(TimeInTicks, 50.f); // duration
//
//	//float AnimationTime = fmod(TimeInTicks, 120.f); // duration
//
//	//cout << "animationTime0 = " << animationTime0 << endl;
//	//cout << fixed << "AnimationTime = " << AnimationTime << endl;
//	//cout << "AnimationTime = " << AnimationTime << endl;
//
//	//cout << "START ApplyPose" << endl;
//
//	ApplyPose(AnimationTime, myAbj.allAnims[0].trackData[0], glm::mat4(1.f)); // UNCOMMENT !!!!!
//}
//
//uint Object::FindPositionGLM_solo(float AnimationTime, TrackData track)
//{
//	for (uint i = 0; i < track.frameData.size() - 1; i++)
//	{
//		if (AnimationTime < (float)track.frameData[i + 1].frame)
//		{
//			return i;
//		}
//	}
//
//	return 0;
//}
//
//void Object::CalcInterpolatedPositionGLM_solo(float AnimationTime, TrackData track, glm::vec3 &out)
//{
//	if (track.frameData.size() == 1)
//	{
//		cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
//		out = myAbj.allAnims[0].trackData[0].frameData[0].decompT;
//		return;
//	}
//
//	uint PositionIndex = FindPositionGLM_solo(AnimationTime, track);
//
//	uint NextPositionIndex = (PositionIndex + 1);
//	//cout << "PositionIndex = " << PositionIndex << endl;
//
//	//cout << "size of pos keys = " << track.frameData.size() << endl;
//
//	float DeltaTime = (float)(track.frameData[NextPositionIndex].frame - track.frameData[PositionIndex].frame);
//	//cout << "DeltaTime = " << DeltaTime << endl;
//
//	float Factor = 0.f;
//	Factor = (AnimationTime - (float)track.frameData[PositionIndex].frame) / DeltaTime;
//	Factor = glm::clamp(Factor, 0.f, 1.f);
//	//cout << "factor = " << Factor << endl;
//
//	glm::vec3 start = track.frameData[PositionIndex].decompT;
//	glm::vec3 end = track.frameData[NextPositionIndex].decompT;
//	glm::vec3 delta = end - start;
//
//	out = start + Factor * delta;
//
//	//out = glm::lerp(start, end, Factor);
//
//}
//
//void Object::CalcInterpolatedRotationGLM_solo(float AnimationTime, TrackData track, glm::quat &out)
//{
//	if (track.frameData.size() == 1)
//	{
//		cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
//		out = myAbj.allAnims[0].trackData[0].frameData[0].decompR;
//		return;
//	}
//
//	uint PositionIndex = FindPositionGLM_solo(AnimationTime, track);
//	uint NextPositionIndex = (PositionIndex + 1);
//
//	float DeltaTime = (float)(track.frameData[NextPositionIndex].frame - track.frameData[PositionIndex].frame);
//	float Factor = 0.f;
//	Factor = (AnimationTime - (float)track.frameData[PositionIndex].frame) / DeltaTime;
//	Factor = glm::clamp(Factor, 0.f, 1.f);
//
//	glm::quat startQ = glm::quat(track.frameData[PositionIndex].decompR);
//	glm::quat endQ = glm::quat(track.frameData[NextPositionIndex].decompR);
//
//	out = glm::slerp(startQ, endQ, Factor);
//	out = glm::normalize(out);
//}
//
//void Object::ApplyPose(float AnimationTime, TrackData track, const glm::mat4 &ParentTransform)
//{
//	glm::quat RotationQ;
//	CalcInterpolatedRotationGLM_solo(AnimationTime, track, RotationQ);
//	glm::mat4 RotationM = glm::toMat4(RotationQ);
//
//	glm::vec3 Translation;
//	CalcInterpolatedPositionGLM_solo(AnimationTime, track, Translation);
//	glm::mat4 TranslationM = glm::translate(glm::mat4(1.f), Translation);
//
////	// Combine the above transformations
//	glm::mat4 NodeTransform = TranslationM * RotationM;
//
//	for (int i = 0; i < myBindSkeleton.skeletonCt; ++i)
//	{
//		if (myBindSkeleton.skeletonData[i].name == track.name)
//		{
//			string gBonesName;
//			gBonesName.append("gBones[");
//			gBonesName.append(to_string(track.id));
//			gBonesName.append("]");
//
//			AnimBone xformNameCombo;
//
//			xformNameCombo.animatedXform = ParentTransform * NodeTransform * myBindSkeleton.skeletonData[i].inverseBindpose;
//			//xformNameCombo.animatedXform = ParentTransform * NodeTransform;
//
//			//xformNameCombo.animatedXform = glm::mat4(1.f);
//			xformNameCombo.name = gBonesName;
//			xformNameCombo.nameMesh = name->val_s;
//
//			animBones.push_back(xformNameCombo);
//		}
//	} 
//
//	for (auto &i : myAbj.allAnims[0].trackData)
//	{
//		if (i.parent == track.name)
//		{
//			//cout << "found parent / child for : " << track.name << " " << i.name << endl;
//			ApplyPose(AnimationTime, i, ParentTransform * NodeTransform);
//		}
//	}
//}
//




















void Object::boneTransformGrpABJ()
{
	//cout << "m_NumBones boneTransform = " << m_NumBones << endl;

	/* SINGLE ANIMATION */
	float TicksPerSecond = 24.f;
	//float TicksPerSecond = 30.f;
	//float TicksPerSecond = 60.f;
	//float TicksPerSecond = 120.f;

	float TimeInTicks = animationTime0 * TicksPerSecond;
	//float TimeInTicks = animationTime0;


	//float AnimationTime = fmod(TimeInTicks, 8.f); // duration
	//float AnimationTime = fmod(TimeInTicks, 24.f); // duration
	float AnimationTime = fmod(TimeInTicks, 50.f); // duration
	//float AnimationTime = fmod(TimeInTicks, 120.f); // duration

	//cout << fixed << "AnimationTime = " << AnimationTime << endl;
	//cout << fixed << "AnimationTime0 = " << animationTime0 << endl;
	//cout << "AnimationTime = " << AnimationTime << endl;

	//cout << "should be root = " << myBindSkeleton.skeletonData[0].name << " " << myBindSkeleton.skeletonData[0].parent << endl;


	//cout << "START ReadNodeHiNoBlendABJ" << endl;

	glm::mat4 IdentityM(1.f);
	//ReadNodeHiNoBlendABJ(AnimationTime, myBindSkeleton.skeletonData[0], IdentityM); // UNCOMMENT !!!!!

	animBones.clear();

	//if (debugSkelName->val_s == "joint4")
		ReadNodeHiNoBlendABJ(AnimationTime, myAbj.allAnims[0].trackData[0], IdentityM); // UNCOMMENT !!!!!
	//ReadNodeHiNoBlendABJ(AnimationTime, ROOT OF THE SKEL ANIM, PARENT TRANSFORM - STARTS AT IDENTITY);

	//cout << "DONE with ReadNodeHiNoBlendABJ" << endl;

	animBones.clear();
}

uint Object::FindPositionGLM(float AnimationTime, TrackData track)
{
	for (uint i = 0; i < track.frameData.size() - 1; i++)
	{
		if (AnimationTime < (float)track.frameData[i + 1].frame)
		{
			return i;
		}
	}

	return 0;
}

void Object::CalcInterpolatedPositionGLM(float AnimationTime, TrackData track, glm::vec3 &out)
{
	if (track.frameData.size() == 1)
	{
		cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
		out = myAbj.allAnims[0].trackData[0].frameData[0].decompT;
		return;
	}

	uint PositionIndex = FindPositionGLM(AnimationTime, track);

	uint NextPositionIndex = (PositionIndex + 1);
	//cout << "PositionIndex = " << PositionIndex << endl;

	//cout << "size of pos keys = " << track.frameData.size() << endl;

	float DeltaTime = (float)(track.frameData[NextPositionIndex].frame - track.frameData[PositionIndex].frame);
	//cout << "DeltaTime = " << DeltaTime << endl;

	float Factor = 0.f;
	Factor = (AnimationTime - (float)track.frameData[PositionIndex].frame) / DeltaTime;
	Factor = glm::clamp(Factor, 0.f, 1.f);
	//cout << "factor = " << Factor << endl;

	glm::vec3 start = track.frameData[PositionIndex].decompT;
	glm::vec3 end = track.frameData[NextPositionIndex].decompT;
	glm::vec3 delta = end - start;

	if (track.name == debugSkelName->val_s)
	{
		//cout << track.name << " interpolating T between " << PositionIndex << " " << glm::to_string(start) << " and " << NextPositionIndex << " " << glm::to_string(end) << endl;

		//out = start + (Factor * delta);
		//out = start + Factor * delta; //

		out = glm::lerp(start, end, Factor);

	}

	else
		out = glm::vec3(0.f);
}

void Object::CalcInterpolatedRotationGLM(float AnimationTime, TrackData track, glm::quat &out)
{
	if (track.frameData.size() == 1)
	{
		cout << "in frame size == 1...need at least 2 vals to interpolate..." << endl;
		out = myAbj.allAnims[0].trackData[0].frameData[0].decompR;
		return;
	}

	uint PositionIndex = FindPositionGLM(AnimationTime, track);
	uint NextPositionIndex = (PositionIndex + 1);

	float DeltaTime = (float)(track.frameData[NextPositionIndex].frame - track.frameData[PositionIndex].frame);
	float Factor = 0.f;
	Factor = (AnimationTime - (float)track.frameData[PositionIndex].frame) / DeltaTime;
	Factor = glm::clamp(Factor, 0.f, 1.f);

	glm::quat startQ = glm::quat(track.frameData[PositionIndex].decompR);
	glm::quat endQ = glm::quat(track.frameData[NextPositionIndex].decompR);

	//cout << "rot interp for " << track.name << endl;

	if (track.name == debugSkelName->val_s)
	{
		out = glm::slerp(startQ, endQ, Factor); // or whatever factor
		out = glm::normalize(out);
	}

	else
		out = glm::quat(0, 0, 0, 0);
}

void Object::ReadNodeHiNoBlendABJ(float AnimationTime, TrackData track, const glm::mat4 &ParentTransform)
{
	string NodeName = track.name;

	glm::mat4 NodeTransform(1.f);

	//{
		/* Interpolate ROTATION and generate RM */
		glm::quat RotationQ;
		CalcInterpolatedRotationGLM(AnimationTime, track, RotationQ);
		glm::mat4 RotationM = glm::toMat4(RotationQ);

		/* Interpolate TRANSLATION and generate TM */
		glm::vec3 myTVec;

		CalcInterpolatedPositionGLM(AnimationTime, track, myTVec);
		glm::mat4 TranslationM = glm::translate(glm::mat4(1.f), myTVec);

		//cout << "myTVec = " << glm::to_string(myTVec) << endl;

	//	// Combine the above transformations
		NodeTransform = TranslationM * RotationM;
		//NodeTransform = RotationM; //
		//NodeTransform = TranslationM; //
	//}

	glm::mat4 GlobalTransform = ParentTransform * NodeTransform;

	if (debugSkel->val_b)
	{
		//for (int i = 0; i < myBindSkeleton.skeletonCt; ++i)
		{
			//if (myBindSkeleton.skeletonData[i].name == track.name)
			if (track.name == debugSkelName->val_s)
			{
				//cout << "found match for " << track.name << endl;
				//cout << "AnimationTime = " << AnimationTime << endl;

				//cout << "myTVec = " << glm::to_string(myTVec) << endl;
				//cout << "parentXform = " << glm::to_string(ParentTransform) << endl;

				debugSkellyMM = GlobalTransform;
				//debugSkellyMM = TranslationM;

				//debugSkellyMM = NodeTransform;


				//string gBonesName;
				//gBonesName.append("gBones[");
				////gBonesName.append(to_string(myAbj.allAnims[0].trackData[0].id));
				//gBonesName.append(to_string(track.id));
				//gBonesName.append("]");

				//AnimBone xformNameCombo;
				//xformNameCombo.animatedXform = GlobalTransform;
				////xformNameCombo.animatedXform = glm::mat4(1.f);
				//xformNameCombo.name = gBonesName;
				//xformNameCombo.nameMesh = name->val_s;

				//animBones.push_back(xformNameCombo);

			}
		}

		//for (int i = 0; i < myBindSkeleton.skeletonCt; ++i)
		//{
			//if (myBindSkeleton.skeletonData[i].name == track.name)
			//{






	}

	//cout << "NodeTransform = " << glm::to_string(NodeTransform) << endl;

	//get list of num children

	//glm::mat4 NodeTransformationM;
	//vector<string> childList;


	for (auto &i : myAbj.allAnims[0].trackData)
	{
		if (i.parent == track.name)
		{
			//cout << "found parent / child for : " << track.name << " " << i.name << endl;
			ReadNodeHiNoBlendABJ(AnimationTime, i, ParentTransform * NodeTransform);
		}
	}
}

void Object::VertexBoneData::AddBoneData(uint BoneID, float Weight, shared_ptr<Object> myObj, uint VertexID)
{
	uint id[4] = { 0, 0, 0, 0 };
	float wt[4] = { 0.f, 0.f, 0.f, 0.f };

	//uint IDs[NUM_BONES_PER_VERTEX];
	//float Weights[NUM_BONES_PER_VERTEX];

	//glm::ivec4 id(0);
	//glm::vec4 wt(0.f);

	//for (uint i = 0; i < 4; i++)
	//{
	//	if (Weights[i] == 0.0)
	//	{
	//		IDs[i] = BoneID;
	//		Weights[i] = Weight; ///////////////////

	//		myObj->boneIdE[VertexID] = glm::ivec4(IDs[0], IDs[1], IDs[2], IDs[3]);
	//		myObj->boneWtE[VertexID] = glm::vec4(Weights[0], Weights[1], Weights[2], Weights[3]);
	//	}
	//}

	for (uint i = 0; i < 4; i++)
	{
		//if (Weights[i] == 0.0)
		if (myObj->boneWtE[VertexID][i] == 0.0)
		{
			IDs[i] = BoneID;
			Weights[i] = Weight; ///////////////////

			myObj->boneIdE[VertexID] = glm::ivec4(IDs[0], IDs[1], IDs[2], IDs[3]);
			myObj->boneWtE[VertexID] = glm::vec4(Weights[0], Weights[1], Weights[2], Weights[3]);

			//cout << "BoneID / IDs[i] / i : " << BoneID << " " << IDs[i] << " " << i << endl;
			//cout << "IDs[0] / IDs[1] / IDs[2]/ IDs[3] : " << IDs[0] << " " << IDs[1] << " " << IDs[2] << " " << IDs[3] << " " << endl;
			//cout << "boneIDE / vertexID = " << glm::to_string(myObj->boneIdE[VertexID]) << " " << VertexID << endl;
			//cout << "boneWtE / vertexID = " << glm::to_string(myObj->boneWtE[VertexID]) << " " << VertexID << endl;

			return;
		}

		else
		{
			//cout << "Weights[i] already set to : IDs[i] / Weights[i] : " << IDs[i] << " " << Weights[i] << endl;
		}

		//if (wt[i] == 0.f)
		//{
		//	//Weights[i] = Weight; ///////////////////

		//	id[i] = BoneID;
		//	wt[i] = Weight;

		//	myObj->boneIdE[VertexID] = glm::ivec4(id[0], id[1], id[2], id[3]);
		//	myObj->boneWtE[VertexID] = glm::vec4(wt[0], wt[1], wt[2], wt[3]);

		//	return;
		//}
	}
}

//void Object::VertexBoneData::AddBoneData(uint BoneID, float Weight, shared_ptr<Object> myObj, uint VertexID)
//{
//	uint id[4] = { 0, 0, 0, 0 };
//	float wt[4] = { 0.f, 0.f, 0.f, 0.f };
//
//	//uint IDs[NUM_BONES_PER_VERTEX];
//	//float Weights[NUM_BONES_PER_VERTEX];
//
//	//glm::ivec4 id(0);
//	//glm::vec4 wt(0.f);
//
//	for (uint i = 0; i < 4; i++)
//	{
//		if (Weights[i] == 0.0)
//		{
//			IDs[i] = BoneID;
//			Weights[i] = Weight; ///////////////////
//
//			myObj->boneIdE[VertexID] = glm::ivec4(IDs[0], IDs[1], IDs[2], IDs[3]);
//			myObj->boneWtE[VertexID] = glm::vec4(Weights[0], Weights[1], Weights[2], Weights[3]);
//
//			cout << "BoneID / IDs[i] / i : " << BoneID << IDs[i] << i << endl;
//			cout << "IDs[0] / IDs[1] / IDs[2]/ IDs[3] : " << IDs[0] << " " << IDs[1] << " " << IDs[2] << " " << IDs[3] << " " << endl;
//			cout << "boneIDE / vertexID = " << glm::to_string(myObj->boneIdE[VertexID]) << " " << VertexID << endl;
//			//cout << "boneWtE / vertexID = " << glm::to_string(myObj->boneWtE[VertexID]) << " " << VertexID << endl;
//
//			return;
//		}
//
//		//if (wt[i] == 0.f)
//		//{
//		//	//Weights[i] = Weight; ///////////////////
//
//		//	id[i] = BoneID;
//		//	wt[i] = Weight;
//
//		//	myObj->boneIdE[VertexID] = glm::ivec4(id[0], id[1], id[2], id[3]);
//		//	myObj->boneWtE[VertexID] = glm::vec4(wt[0], wt[1], wt[2], wt[3]);
//
//		//	return;
//		//}
//	}
//}