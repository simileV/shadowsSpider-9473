#include "Setup_texShaders.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CubemapDirections cubeDirs[6] =
{
	{ glm::vec3(1.f,  0.f,  0.f), glm::vec3(0.f, -1.f,  0.f) },
	{ glm::vec3(-1.f,  0.f,  0.f), glm::vec3(0.f, -1.f,  0.f) },
	{ glm::vec3(0.f,  1.f,  0.f), glm::vec3(0.f,  0.f,  1.f) },
	{ glm::vec3(0.f, -1.f,  0.f), glm::vec3(0.f,  0.f, -1.f) },
	{ glm::vec3(0.f,  0.f,  1.f), glm::vec3(0.f, -1.f,  0.f) },
	{ glm::vec3(0.f,  0.f, -1.f), glm::vec3(0.f, -1.f,  0.f) }
};

//CubemapDirections cubeDirs[6] =
//{
//	{ glm::vec3(1.f,  0.f,  0.f), glm::vec3(0.f, -1.f,  0.f) },
//	{ glm::vec3(-1.f,  0.f,  0.f), glm::vec3(0.f, -1.f,  0.f) },
//	{ glm::vec3(0.f,  1.f,  0.f), glm::vec3(0.f,  0.f,  -1.f) },
//	{ glm::vec3(0.f, -1.f,  0.f), glm::vec3(0.f,  0.f, 1.f) },
//	{ glm::vec3(0.f,  0.f,  1.f), glm::vec3(0.f, -1.f,  0.f) },
//	{ glm::vec3(0.f,  0.f, -1.f), glm::vec3(0.f, -1.f,  0.f) }
//};

void uboInit()
{
	////////////////
	////////////////
	glCreateBuffers(1, &myAbj.uboLight);
	glNamedBufferData(myAbj.uboLight, uboAligned(sizeof(LightData)) * 10, 0, GL_DYNAMIC_DRAW);
	glGetNamedBufferParameterui64vNV(myAbj.uboLight, GL_BUFFER_GPU_ADDRESS_NV, &myAbj.uboLight_64);
	glMakeNamedBufferResidentNV(myAbj.uboLight, GL_READ_ONLY);
	glBufferAddressRangeNV(GL_UNIFORM_BUFFER_ADDRESS_NV, 0, myAbj.uboLight_64, sizeof(LightData));

	////////////////
	////////////////
	glCreateBuffers(1, &myAbj.uboScene);
	glNamedBufferData(myAbj.uboScene, sizeof(SceneData), 0, GL_DYNAMIC_DRAW);
	glGetNamedBufferParameterui64vNV(myAbj.uboScene, GL_BUFFER_GPU_ADDRESS_NV, &myAbj.uboScene_64);
	glMakeNamedBufferResidentNV(myAbj.uboScene, GL_READ_ONLY);
	glBufferAddressRangeNV(GL_UNIFORM_BUFFER_ADDRESS_NV, 1, myAbj.uboScene_64, sizeof(SceneData));

	////////////////
	////////////////
	glCreateBuffers(1, &myAbj.uboDebug);
	glNamedBufferData(myAbj.uboDebug, sizeof(DebugData), 0, GL_DYNAMIC_DRAW);
	glGetNamedBufferParameterui64vNV(myAbj.uboDebug, GL_BUFFER_GPU_ADDRESS_NV, &myAbj.uboDebug_64);
	glMakeNamedBufferResidentNV(myAbj.uboDebug, GL_READ_ONLY);
	glBufferAddressRangeNV(GL_UNIFORM_BUFFER_ADDRESS_NV, 2, myAbj.uboDebug_64, sizeof(DebugData));
}

void uboUp()
{
	////////////////
	/* LIGHT */
	///////////////
	auto lightIter = 0;

	for (auto &i : myAbj.allCamLi)
	{
		if (i->v->val_b && i->camLiTypeGet("light"))
		{
			LightData lightD;

			float type;
			if (i->camLiType->val_s == "DIR") type = 1.f;
			else if (i->camLiType->val_s == "POINT") type = 2.f;
			else if (i->camLiType->val_s == "SPOT") type = 3.f;

			lightD.Cl_type = glm::vec4(i->Cl->val_3, type);
			
			lightD.falloff = glm::vec4(i->lInten->val_f, cos(glm::radians(i->lSpotI->val_f)), cos(glm::radians(i->lSpotO->val_f)), 0.f);
			//lightD.falloff = glm::vec4(10.f, 10.f, 10.f, 0.f);

			lightD.DirRot = i->MM * glm::vec4(0.f, 0.f, -1.f, 0.f);
			lightD.P_WS = glm::vec4(i->tx->val_f, i->ty->val_f, i->tz->val_f, 0.f);
			//_NOT_ UPLOADING SHADOW MATRIX HERE !!!!!!
			glNamedBufferSubData(myAbj.uboLight, sizeof(lightD) * lightIter, sizeof(LightData), &lightD);

			++lightIter;
		}
	}

	myAbj.UBO_light_needsUp = 0;

	////////////////
	/* SCENE */
	///////////////
	SceneData sceneD;
	sceneD.PM = myAbj.selCamLi->PM;
	sceneD.PMinv = glm::inverse(myAbj.selCamLi->PM);
	sceneD.VM = myAbj.selCamLi->VM;
	sceneD.VMinv = glm::inverse(myAbj.selCamLi->VM);
	sceneD.VPM = myAbj.selCamLi->PM * myAbj.selCamLi->VM;
	sceneD.comboU0 = glm::vec4(myAbj.myFSQ->Kgi->val_f, lightIter, 0.f, 0.f); //vec4(Kgi, NUM_LIGHTS, debug0, 0.f)
	glNamedBufferSubData(myAbj.uboScene, 0, sizeof(SceneData), &sceneD);

	////////////////
	/* DEBUG */
	///////////////
	DebugData debugD;
	debugD.comboU0 = glm::vec4(0.f, 1.f, 0.f, 1.f);
	debugD.comboU1 = glm::vec4(0.f, 0.f, 1.f, 1.f);
	glNamedBufferSubData(myAbj.uboDebug, 0, sizeof(DebugData), &debugD);
}

AbjNode texN_create(string name, string type, string pathIn, int idx)
{
	//this is basically singleN_create() / w a texture uploaded into slot 1 

	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);
	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };

	//upload tex into slot 0...consider additional slots (2 total) for brush's outline silhouette
	auto pathTex = "C:/Users/aleks/source/repos/Shadows_Spider_Tex/";

	auto pathTemp = pathTex + pathIn;
	const auto *path = pathTemp.c_str();

	GLuint fboNew2, tex, tex2;
	int imgW, imgH, chan;
	imgW = 999;
	imgH = 999;

	if (type == "CUBE_IRRAD" || type == "CUBE_SPEC")
	{
		auto *myFile = fopen(path, "rb");

		if (!myFile)
		{
			fprintf(stderr, "Error opening file '%s'\n", path);

			return { name, imgW, imgH, 0, 0, 0, 0, 0, 0, 0, 0, idx };
		}

		char filecode[4];
		fread(filecode, 1, 4, myFile);

		ddsHeader myHeader;
		fread(&myHeader, sizeof(ddsHeader), 1, myFile);

		vector<uint8_t*> _data;

		for (int i = 0; i < 6; ++i)
		{
			int w = myHeader.dwWidth;
			int h = myHeader.dwHeight;

			for (uint j = 0; j < myHeader.dwMipMapCount; ++j)
			{
				int size = w * h * 8;
				uint8_t *pixels = new uint8_t[size];

				fread(pixels, size, 1, myFile);
				_data.push_back(pixels);

				w = (w > 1) ? w >> 1 : 1;
				h = (h > 1) ? h >> 1 : 1;
			}
		}

		fclose(myFile);

		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &tex);

		for (int i = 0; i < 6; ++i)
		{
			auto w = myHeader.dwWidth;
			auto h = myHeader.dwHeight;

			for (uint j = 0; j < myHeader.dwMipMapCount; ++j)
			{
				void* texData = _data[i * myHeader.dwMipMapCount + j];

				glTextureImage2DEXT(tex, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j, GL_RGBA16F, w, h, 0, GL_RGBA, GL_HALF_FLOAT, texData);

				w >>= 1;
				h >>= 1;
				w = w ? w : 1;
				h = h ? h : 1;
			}
		}

		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}

	else
	{
		auto *img = stbi_load(path, &imgW, &imgH, &chan, 0);

		for (int h = 0; h < imgH / 2; ++h) //vFlip
		{
			auto top = h * imgW * chan;
			auto btm = (imgH - 1 - h) * imgW * chan;

			for (int w = 0; w < imgW * chan; ++w)
			{
				GLubyte temp = img[top];
				img[top] = img[btm];
				img[btm] = temp;
				++top;
				++btm;
			}
		}

		GLint formatI, formatP;
		if (chan == 3) { formatI = GL_RGB8; formatP = GL_RGB; }
		else if (chan == 4) { formatI = GL_RGBA16; formatP = GL_RGBA; }

		int numMip;
		if (pathIn == "txt/verasansmono.png") numMip = 1;
		else numMip = 1 + int(floor(log2(glm::max(imgW, imgH))));

		glCreateTextures(GL_TEXTURE_2D, 1, &tex);
		glTextureStorage2D(tex, numMip, formatI, imgW, imgH);
		glTextureSubImage2D(tex, 0, 0, 0, imgW, imgH, formatP, GL_UNSIGNED_BYTE, img);

		glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//ANISOTROPIC FILTERING
		GLint maxAniso = 0;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
		glGenerateTextureMipmap(tex);

		stbi_image_free(img);
	}

	glNamedFramebufferTexture(fboNew, DrawBuffers[0], tex, 0);
	glNamedFramebufferDrawBuffers(fboNew, 1, DrawBuffers);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with texN_create" << endl;

	if (type == "BRUSH")
	{
		glCreateFramebuffers(1, &fboNew2);
		glCreateTextures(GL_TEXTURE_2D, 1, &tex2);
		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };

		glTextureStorage2D(tex2, 1, GL_RGBA16F, imgW, imgH);
		glTextureParameteri(tex2, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(tex2, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(tex2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex2, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glNamedFramebufferTexture(fboNew2, DrawBuffers[0], tex2, 0);
		glNamedFramebufferDrawBuffers(fboNew2, 1, DrawBuffers);

		if (glCheckNamedFramebufferStatus(fboNew2, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "error with BRUSH fbo1 create" << endl;
	}

	else if (type != "CUBE_IRRAD" && type != "CUBE_SPEC")
	{
		//create the "copyTex" FBO
		glCreateFramebuffers(1, &fboNew2);
		glCreateTextures(GL_TEXTURE_2D, 1, &tex2);
		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };

		glTextureStorage2D(tex2, 1, GL_RGBA16F, imgW, imgH);
		glTextureParameteri(tex2, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(tex2, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glTextureParameteri(tex2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTextureParameteri(tex2, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(tex2, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(tex2, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glNamedFramebufferTexture(fboNew2, DrawBuffers[0], tex2, 0);
		glNamedFramebufferDrawBuffers(fboNew2, 1, DrawBuffers);

		if (glCheckNamedFramebufferStatus(fboNew2, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "error with TEX AKA COPYTEX fbo1 create" << endl;
	}

	return { name, imgW, imgH, fboNew, tex, 0, fboNew2, tex2, 0, 0, 0, idx };
}

void up64N(AbjNode &node, bool up)
{
	glMakeTextureHandleNonResidentARB(node.DS_64);
	glMakeTextureHandleNonResidentARB(node.tex0_64);
	glMakeTextureHandleNonResidentARB(node.tex1_64);

	if (up)
	{
		node.DS_64 = glGetTextureHandleARB(node.DS_32);
		glMakeTextureHandleResidentARB(node.DS_64);

		node.tex0_64 = glGetTextureHandleARB(node.tex0_32);
		glMakeTextureHandleResidentARB(node.tex0_64);

		node.tex1_64 = glGetTextureHandleARB(node.tex1_32);
		glMakeTextureHandleResidentARB(node.tex1_64);
	}

	else
	{
		glDeleteTextures(1, &node.DS_32);

		glDeleteTextures(1, &node.tex0_32);
		glDeleteFramebuffers(1, &node.fbo0);

		glDeleteTextures(1, &node.tex1_32);
		glDeleteFramebuffers(1, &node.fbo1);
	}
}

void up64T(GLuint &tex32, GLuint64 &tex64, bool up)
{
	glMakeTextureHandleNonResidentARB(tex64);

	if (up)
	{
		tex64 = glGetTextureHandleARB(tex32);
		glMakeTextureHandleResidentARB(tex64);
	}

	else
		glDeleteTextures(1, &tex32);
}

void mapInit() //NSIGHT
{
	//ALBEDO
	myAbj.allTexMaps.push_back({ "ABJ_ALBEDO", "ALBEDO", "albedo/ABJ.png" });

	myAbj.allTexMaps.push_back({ "BLANK_ALBEDO", "ALBEDO", "single/BLANK_white_256.tga" });
	myAbj.allTexMaps.push_back({ "BLACK_ALBEDO", "ALBEDO", "single/BLANK_black_256.tga" });
	myAbj.allTexMaps.push_back({ "CHECKER_ALBEDO", "ALBEDO", "albedo/checker.png" });
	//myAbj.allTexMaps.push_back({ "checker3", "ALBEDO", "albedo/checker3.png" });
	//myAbj.allTexMaps.push_back({ "uv", "ALBEDO", "albedo/uv.jpg" });
	//myAbj.allTexMaps.push_back({ "gold", "ALBEDO", "single/gold_256.tga" });
	//myAbj.allTexMaps.push_back({ "abj", "ALBEDO", "albedo/ABJ.png" });
	myAbj.allTexMaps.push_back({ "RED_ALBEDO", "ALBEDO", "single/colors/BLANK_red_256.png" });
	myAbj.allTexMaps.push_back({ "GREEN_ALBEDO", "ALBEDO", "single/colors/BLANK_green_256.png" });
	myAbj.allTexMaps.push_back({ "BLUE_ALBEDO", "ALBEDO", "single/colors/BLANK_blue_256.png" });
	myAbj.allTexMaps.push_back({ "SKIN1_ALBEDO", "ALBEDO", "single/BLANK_skin1_256.png" });

	//myAbj.allTexMaps.push_back({ "cyan", "ALBEDO", "single/colors/BLANK_cyan_256.png" });
	myAbj.allTexMaps.push_back({ "YELLOW_ALBEDO", "ALBEDO", "single/colors/BLANK_yellow_256.png" });
	myAbj.allTexMaps.push_back({ "MAGENTA_ALBEDO", "ALBEDO", "single/colors/BLANK_magenta_256.png" });

	//ALPHA
	myAbj.allTexMaps.push_back({ "BLANK_ALPHA", "ALPHA", "single/BLANK_white_1024.png" });
	myAbj.allTexMaps.push_back({ "GRASS_ALPHA", "ALPHA", "alpha/grass.png" });

	//ANISO
	myAbj.allTexMaps.push_back({ "BLANK_ANISO", "ANISO", "single/BLANK_white_256.tga" });
	myAbj.allTexMaps.push_back({ "VIEW", "ANISO", "single/BLANK_white_256.tga" });
	myAbj.allTexMaps.push_back({ "ROT1_ANISO", "ANISO", "aniso/rot1.jpg" });
	myAbj.allTexMaps.push_back({ "ROT2_ANISO", "ANISO", "aniso/rot2.jpg" });
	myAbj.allTexMaps.push_back({ "ROT3_ANISO", "ANISO", "aniso/rot3.jpg" });
	myAbj.allTexMaps.push_back({ "ROT4_ANISO", "ANISO", "aniso/rot4.jpg" });

	//BRUSH
	myAbj.allTexMaps.push_back({ "ROUND_BRUSH", "BRUSH", "brush/round_soft.tga" });
	myAbj.allTexMaps.push_back({ "SQUARE_BRUSH", "BRUSH", "brush/square.tga" });
	//myAbj.allTexMaps.push_back( { "round", "BRUSH", "brush/superSoft.tga" } );
	//myAbj.allTexMaps.push_back( { "round", "BRUSH", "brush/round_hard.tga" } );
	//myAbj.allTexMaps.push_back( { "round", "BRUSH", "brush/wavy.tga" } );

	//CUBE STRUCT VEC
	myAbj.allCubeIrradSpec.push_back({ "ENNIS", "ENNIS_CUBEIRRAD", "ENNIS_CUBESPEC" });
	myAbj.allCubeIrradSpec.push_back({ "GLACIER", "GLACIER_CUBEIRRAD", "GLACIER_CUBESPEC" });
	myAbj.allCubeIrradSpec.push_back({ "GRACE", "GRACE_CUBEIRRAD", "GRACE_CUBESPEC" });
	myAbj.allCubeIrradSpec.push_back({ "PISA", "PISA_CUBEIRRAD", "PISA_CUBESPEC" });
	myAbj.allCubeIrradSpec.push_back({ "UFFIZI", "UFFIZI_CUBEIRRAD", "UFFIZI_CUBESPEC" });

	//CUBE_IRRAD
	myAbj.allTexMaps.push_back({ "ENNIS_CUBEIRRAD", "CUBE_IRRAD", "cube/ennis_cube_irradiance.dds" });
	//myAbj.allTexMaps.push_back({ "GLACIER_CUBEIRRAD", "CUBE_IRRAD", "cube/glacier_cube_irradiance.dds" });
	//myAbj.allTexMaps.push_back({ "GRACE_CUBEIRRAD", "CUBE_IRRAD", "cube/grace_cube_irradiance.dds" });
	//myAbj.allTexMaps.push_back({ "PISA_CUBEIRRAD", "CUBE_IRRAD", "cube/pisa_cube_irradiance.dds" });
	//myAbj.allTexMaps.push_back({ "UFFIZI_CUBEIRRAD", "CUBE_IRRAD", "cube/uffizi_cube_irradiance.dds" });

	//CUBE_SPEC
	myAbj.allTexMaps.push_back({ "ENNIS_CUBESPEC", "CUBE_SPEC", "cube/ennis_cube_specular.dds" });
	//myAbj.allTexMaps.push_back({ "CLEARSKY_CUBESPEC", "CUBE_IRRAD", "cube/06-07_Day_G2_cube_specular.dds" });
	//myAbj.allTexMaps.push_back({ "GLACIER_CUBESPEC", "CUBE_SPEC", "cube/glacier_cube_specular.dds" });
	//myAbj.allTexMaps.push_back({ "GRACE_CUBESPEC", "CUBE_SPEC", "cube/grace_cube_specular.dds" });
	//myAbj.allTexMaps.push_back({ "PISA_CUBESPEC", "CUBE_SPEC", "cube/pisa_cube_specular.dds" });
	//myAbj.allTexMaps.push_back({ "UFFIZI_CUBESPEC", "CUBE_SPEC", "cube/uffizi_cube_specular.dds" });

	//CURSOR
	myAbj.allTexMaps.push_back({ "cursorReg", "cursor", "cursor/cursorReg1k.png" });

	//DUDV
	myAbj.allTexMaps.push_back({ "BLANK_DUDV", "DUDV", "single/BLANK_black_256.tga" });
	myAbj.allTexMaps.push_back({ "RIPPLE_DUDV", "DUDV", "dudv/dudv.jpg" });
	myAbj.allTexMaps.push_back({ "NORMAL_DUDV", "DUDV", "dudv/dudvNormal.jpg" });

	//LENS
	myAbj.allTexMaps.push_back({ "BLANK_LENS", "LENS", "lens/BLANK_black_256.png" });
	myAbj.allTexMaps.push_back({ "DIRTY_LENS", "LENS", "lens/abjLens1.png" });

	//METALLIC
	myAbj.allTexMaps.push_back({ "BLANK_METALLIC", "METALLIC", "single/BLANK_black_256.tga" });
	myAbj.allTexMaps.push_back({ "WHITE_METALLIC", "METALLIC", "single/BLANK_white_256.tga" });

	//NORMAL
	myAbj.allTexMaps.push_back({ "BLANK_NORMAL", "NORMAL", "normal/BLANK.png" });
	myAbj.allTexMaps.push_back({ "SQUARES_NORMAL", "NORMAL", "normal/squares.jpg" });
	myAbj.allTexMaps.push_back({ "VORONOI_NORMAL", "NORMAL", "normal/voronoi.jpg" });
	//myAbj.allTexMaps.push_back({ "VORONOI_NORMAL", "NORMAL", "normal/voronoi_flipG.jpg" });
	//myAbj.allTexMaps.push_back({ "TIGHTBRICK_NORMAL", "NORMAL", "normal/tightBrick.png" });
	//myAbj.allTexMaps.push_back({ "TIGHTBRICK_NORMAL", "NORMAL", "normal/skewBrick0.png" });
	myAbj.allTexMaps.push_back({ "TIGHTBRICK_NORMAL", "NORMAL", "normal/skewBrick1.png" });
	myAbj.allTexMaps.push_back({ "TIGHTBRICK2_NORMAL", "NORMAL", "normal/brick2.jpg" });

	//myAbj.allTexMaps.push_back({ "brushed_H", "NORMAL", "normal/brushed_H.png" });
	//myAbj.allTexMaps.push_back({ "brushed_V", "NORMAL", "normal/brushed_V.png" });
	//myAbj.allTexMaps.push_back({ "rand", "NORMAL", "normal/rand.png" }); // for ssao only

	//RUFF
	myAbj.allTexMaps.push_back({ "BLANK_RUFF", "RUFF", "single/BLANK_black_256.tga" });
	myAbj.allTexMaps.push_back({ "GRAY_RUFF", "RUFF", "single/BLANK_gray_256.tga" });
	myAbj.allTexMaps.push_back({ "WHITE_RUFF", "RUFF", "single/BLANK_white_256.tga" });
	//myAbj.allTexMaps.push_back({ "squiggle0", "RUFF", "ruff/squiggle0.tga" });
	//myAbj.allTexMaps.push_back({ "squiggle1", "RUFF", "ruff/squiggle1.tga" });

	//TXT
	myAbj.allTexMaps.push_back({ "atlas", "TXT", "txt/verasansmono.png" });

	uint IDct = 0;
	for (auto &i : myAbj.allTexMaps)
		i.loaded = 0;

	//push LAYERS back into maps
	for (auto &i : myAbj.allTexMaps)
	{
		i.layer.push_back({ texN_create("layer0", i.type, i.flat, 0) });

		//drag u/d and change idx debug
		if (i.name == "BLANK_ALBEDO")
		{
			i.layer.push_back({ texN_create("layer1", i.type, i.flat, 1) });
			i.layer.push_back({ texN_create("layer2", i.type, i.flat, 2) });
		}

		i.ID = IDct;
		++IDct;
	}

	//upload 64 bit bindless handles for ALL layers
	for (auto &i : myAbj.allTexMaps)
	{
		for (auto &j : i.layer)
		{
			up64N(j, 1);
			j.ID = IDct;
			++IDct;
		}
	}

	for (auto &i : myAbj.allTexMaps)
		i.loaded = 1;

	//GEN BRUSH OUTLINES FOR ALL BRUSHES AND PUSH BACK OUTLINE INTO MAP LAYER[1]
	//for brushes render the sobel outline into FBO1 / tex1
	//use 128x128 size
	myAbj.brushOutlineUpB = 1;
}

void proInit()
{
	myAbj.allPro.push_back({ "pAlphaAsRGBA", glCreateProg("fboV.glsl", "", "alphaAsRGBAF.glsl") });
	myAbj.allPro.push_back({ "pBB", glCreateProg("bbV.glsl", "", "bbF.glsl") });
	myAbj.allPro.push_back({ "pColorID", glCreateProg("colorIDV.glsl", "", "colorIDF.glsl") });
	myAbj.allPro.push_back({ "pColorIDAnim", glCreateProg("colorIDAnimV.glsl", "", "colorIDF.glsl") });
	myAbj.allPro.push_back({ "pBlendMode", glCreateProg("wsQuadV.glsl", "", "blendModeF.glsl") });
	myAbj.allPro.push_back({ "pBill", glCreateProg("billV.glsl", "", "billF.glsl") });
	myAbj.allPro.push_back({ "pBloom", glCreateProg("fboV.glsl", "", "bloomF.glsl") });
	myAbj.allPro.push_back({ "pCopyTex", glCreateProg("fboV.glsl", "", "copyTexF.glsl") });
	myAbj.allPro.push_back({ "pCursor", glCreateProg("cursorV.glsl", "", "cursorF.glsl") });
	myAbj.allPro.push_back({ "pDef", glCreateProg("fboV.glsl", "", "defF.glsl") });
	myAbj.allPro.push_back({ "pDepthRev", glCreateProg("depthRevV.glsl", "", "depthRevF.glsl") });
	myAbj.allPro.push_back({ "pDepthRevAnim", glCreateProg("depthRevAnimV.glsl", "", "depthRevF.glsl") });
	myAbj.allPro.push_back({ "pDown", glCreateProg("downV.glsl", "", "downF.glsl") });
	myAbj.allPro.push_back({ "pFinal", glCreateProg("fboV.glsl", "", "finalF.glsl") });

	myAbj.allPro.push_back({ "pFinalStereo", glCreateProg("fboV.glsl", "", "finalStereoF.glsl") });
	myAbj.allPro.push_back({ "pStereoPost", glCreateProg("fboV.glsl", "", "stereoPostF.glsl") });
	myAbj.allPro.push_back({ "pStereoPrev", glCreateProg("fboV.glsl", "", "stereoPrevF.glsl") });

	//myAbj.allPro.push_back({ "pFilterSizeMatch", glCreateProg("fboV.glsl", "", "filterSizeMatchF.glsl") });


	myAbj.allPro.push_back({ "pEdgeDetect", glCreateProg("fboV.glsl", "", "edgeDetectF.glsl") });
	myAbj.allPro.push_back({ "pEraseMix", glCreateProg("fboV.glsl", "", "eraseMixF.glsl") });
	myAbj.allPro.push_back({ "pFxaa", glCreateProg("fboV.glsl", "", "fxaaF.glsl") });
	myAbj.allPro.push_back({ "pGauss", glCreateProg("fboV.glsl", "", "gaussF.glsl") });
	myAbj.allPro.push_back({ "pGBuffer", glCreateProg("gBufferV.glsl", "", "gBufferF.glsl") });
	myAbj.allPro.push_back({ "pGBufferAnim", glCreateProg("gBufferAnimV.glsl", "", "gBufferF.glsl") });
	myAbj.allPro.push_back({ "pGiz", glCreateProg("gizV.glsl", "", "gizF.glsl") });
	myAbj.allPro.push_back({ "pGiz_circ", glCreateProg("giz_circV.glsl", "", "gizF.glsl") });
	myAbj.allPro.push_back({ "pGrid", glCreateProg("gizV.glsl", "", "gridF.glsl") });
	myAbj.allPro.push_back({ "pLumaInit", glCreateProg("fboV.glsl", "", "lumaInitF.glsl") });
	myAbj.allPro.push_back({ "pLumaAdapt", glCreateProg("fboV.glsl", "", "lumaAdaptF.glsl") });
	myAbj.allPro.push_back({ "pNormalRuff", glCreateProg("normalRuffV.glsl", "", "normalRuffF.glsl") });
	myAbj.allPro.push_back({ "pNormalRuffAnim", glCreateProg("normalRuffAnimV.glsl", "", "normalRuffF.glsl") });
	myAbj.allPro.push_back({ "pPaintProj", glCreateProg("paintProjV.glsl", "", "paintProjF.glsl") });
	myAbj.allPro.push_back({ "pPaintStroke", glCreateProg("wsQuadV.glsl", "", "paintStrokeF.glsl") });
	myAbj.allPro.push_back({ "pSelRect", glCreateProg("selRectV.glsl", "", "selRectF.glsl") });
	myAbj.allPro.push_back({ "pShadow", glCreateProg("shadowV.glsl", "", "shadowF.glsl") });
	myAbj.allPro.push_back({ "pShadowAnim", glCreateProg("shadowAnimV.glsl", "", "shadowF.glsl") });
	myAbj.allPro.push_back({ "pSky", glCreateProg("skyV.glsl", "", "skyF.glsl") });
	myAbj.allPro.push_back({ "pSSAO_32", glCreateProg("fboV.glsl", "", "ssao_32F.glsl") });
	myAbj.allPro.push_back({ "pSSAO_64", glCreateProg("fboV.glsl", "", "ssao_64F.glsl") });
	myAbj.allPro.push_back({ "pSSR", glCreateProg("fboV.glsl", "", "ssrF.glsl") });
	myAbj.allPro.push_back({ "pStencilGeo", glCreateProg("stencilGeoV.glsl", "", "stencilGeoF.glsl") });
	myAbj.allPro.push_back({ "pStencilGeoAnim", glCreateProg("stencilGeoAnimV.glsl", "", "stencilGeoF.glsl") });
	myAbj.allPro.push_back({ "pStencilHi", glCreateProg("stencilHiV.glsl", "", "stencilHiF.glsl") });
	myAbj.allPro.push_back({ "pStencilHiAnim", glCreateProg("stencilHiAnimV.glsl", "", "stencilHiF.glsl") });
	myAbj.allPro.push_back({ "pTonemap", glCreateProg("fboV.glsl", "", "tonemapF.glsl") });
	myAbj.allPro.push_back({ "pTransp", glCreateProg("transpV.glsl", "", "transpF.glsl") });
	myAbj.allPro.push_back({ "pTranspComp", glCreateProg("fboV.glsl", "", "transpCompF.glsl") });
	myAbj.allPro.push_back({ "pTxt", glCreateProg("txtV.glsl", "txtG.glsl", "txtF.glsl") });
	myAbj.allPro.push_back({ "pTxtDie", glCreateProg("txtV.glsl", "txtG.glsl", "txtDieF.glsl") });
	myAbj.allPro.push_back({ "pVolumeLight", glCreateProg("volumeLightV.glsl", "", "volumeLightF.glsl") });
	myAbj.allPro.push_back({ "pWireframe", glCreateProg("wireframeV.glsl", "", "wireframeF.glsl") });
}

GLuint glCreateProg(string vIn, string gIn, string fIn)
{
	auto pathGLSL = "./shaders/";

	auto vTemp = pathGLSL + vIn;
	const auto *vFile = vTemp.c_str();

	auto gTemp = pathGLSL + gIn;
	const auto *gFile = gTemp.c_str();

	auto fTemp = pathGLSL + fIn;
	const auto *fFile = fTemp.c_str();

	//
	auto proC = glCreateProgram();
	GLuint shaderV, shaderG, shaderF;

	if (vFile)
	{
		shaderV = glCreateShaderStage(vFile, GL_VERTEX_SHADER);

		if (!shaderV)
			return 0;

		glAttachShader(proC, shaderV);
	}

	if (gIn != "")
	{
		shaderG = glCreateShaderStage(gFile, GL_GEOMETRY_SHADER);

		if (!shaderG)
			return 0;

		glAttachShader(proC, shaderG);
	}

	if (fFile)
	{
		shaderF = glCreateShaderStage(fFile, GL_FRAGMENT_SHADER);

		if (!shaderF)
			return 0;

		glAttachShader(proC, shaderF);
	}

	glLinkProgram(proC);
	auto link_ok = GL_FALSE;
	glGetProgramiv(proC, GL_LINK_STATUS, &link_ok);

	if (!link_ok)
	{
		fprintf(stderr, "glLinkProgram:");
		glShaderError(proC);
		glDeleteProgram(proC);
		return 0;
	}

	glDetachShader(proC, shaderV);
	glDeleteShader(shaderV);

	if (gIn != "")
	{
		glDetachShader(proC, shaderG);
		glDeleteShader(shaderG);
	}

	glDetachShader(proC, shaderF);
	glDeleteShader(shaderF);

	return proC;
}

GLuint glCreateShaderStage(const char *file, GLenum type)
{
	const auto *source = glShaderRead(file);

	if (source == 0)
	{
		fprintf(stderr, "Error opening %s: ", file);
		perror("");

		return 0;
	}

	auto shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);

	free((void*)source);

	static char* incPaths[] = { "/" };
	//glCompileShaderIncludeARB(shader, 1, incPaths, NULL);
	glCompileShader(shader);

	auto compile_ok = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);

	if (compile_ok == GL_FALSE) // error here
	{
		fprintf(stderr, "%s:", file);
		glShaderError(shader);
		glDeleteShader(shader);

		return 0;
	}

	return shader;
}

char* glShaderRead(const char *file)
{
	auto *input = fopen(file, "rb");

	if (!input)
	{
		string unloadedShader = string(file);
		cout << "input prob in glShaderRead() for " << unloadedShader << endl;
		return 0;
	}

	if (fseek(input, 0, SEEK_END) == -1)
		return 0;

	auto size = ftell(input);

	if (size == -1)
		return 0;

	if (fseek(input, 0, SEEK_SET) == -1)
		return 0;

	auto *content = (char*)malloc((size_t)size + 1);

	if (content == 0)
		return 0;

	if (!(fread(content, 1, (size_t)size, input)) || ferror(input))
	{
		cout << "error reading shader" << endl;
		free(content);

		return 0;
	}

	fclose(input);
	content[size] = '\0';

	return content;
}

void glShaderError(GLuint object)
{
	auto log_length = 0;

	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);

	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);

	else
	{
		fprintf(stderr, "printlog: Not a shader or a program\n");

		return;
	}

	auto *log = (char*)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, 0, log);

	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, 0, log);

	fprintf(stderr, "%s", log);
	free(log);
}

void glUseProgram2(string name)
{
	bool found = 0;

	for (auto &i : myAbj.allPro)
	{
		if (i.name == name)
		{
			myAbj.pro = i.pro;
			found = 1;
		}
	}

	if (!found)
		cout << "couldn't find pro for : " << name << endl;

	glUseProgram(myAbj.pro);
	myAbj.proN = name;
}

void addDeleteShadows(string type)
{
	if (type == "add")
	{
		for (auto &i : myAbj.allCamLi)
		{
			if (i->v->val_b && i->camLiTypeGet("light"))
			{
				//int shadowSize = 1024; //
				int shadowSize = 2048;//
				//int shadowSize = 4096;//
				AbjNode shadowN = shadowN_create(i->name->val_s, shadowSize, shadowSize);

				glMakeTextureHandleNonResidentARB(shadowN.tex0_64);
				shadowN.tex0_64 = glGetTextureHandleARB(shadowN.tex0_32);
				glMakeTextureHandleResidentARB(shadowN.tex0_64);

				glMakeTextureHandleNonResidentARB(shadowN.tex1_64);
				shadowN.tex1_64 = glGetTextureHandleARB(shadowN.tex1_32);
				glMakeTextureHandleResidentARB(shadowN.tex1_64);

				myAbj.allShadow.push_back(shadowN);
			}
		}
	}

	else if (type == "delete")
	{
		//SHADOW FBO
		for (auto &i : myAbj.allShadow)
		{
			glMakeTextureHandleNonResidentARB(i.tex0_64);
			glDeleteTextures(1, &i.tex0_32);
			glDeleteFramebuffers(1, &i.fbo0);

			glMakeTextureHandleNonResidentARB(i.tex1_64);
			glDeleteTextures(1, &i.tex1_32);
			glDeleteFramebuffers(1, &i.fbo1);
		}

		myAbj.allShadow.clear();
	}

	else if (type == "refresh")
	{
		addDeleteShadows("delete");
		addDeleteShadows("add");
	}
}

AbjNode shadowN_create(string name, int widthIn, int heightIn)
{
	GLuint fboNew0; //spot / dir shadows
	glCreateFramebuffers(1, &fboNew0);

	GLfloat border[] = { 1.f, 1.f, 1.f, 1.f };

	GLuint texNew0;
	glCreateTextures(GL_TEXTURE_2D, 1, &texNew0);
	glTextureStorage2D(texNew0, 1, GL_DEPTH_COMPONENT32F, widthIn, heightIn);
	glTextureParameteri(texNew0, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTextureParameteri(texNew0, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTextureParameteri(texNew0, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(texNew0, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(texNew0, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTextureParameteri(texNew0, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTextureParameterfv(texNew0, GL_TEXTURE_BORDER_COLOR, border);

	glNamedFramebufferTexture(fboNew0, GL_DEPTH_ATTACHMENT, texNew0, 0);
	glNamedFramebufferDrawBuffer(fboNew0, GL_NONE);
	glNamedFramebufferReadBuffer(fboNew0, GL_NONE);

	if (glCheckNamedFramebufferStatus(fboNew0, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with shadowN_create FBO0" << endl;

	GLuint fboNew1; //point shadows
	glCreateFramebuffers(1, &fboNew1);

	GLuint texNew1;
	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &texNew1);
	glTextureParameteri(texNew1, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texNew1, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texNew1, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTextureParameteri(texNew1, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTextureParameteri(texNew1, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(texNew1, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(texNew1, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(texNew1, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTextureParameteri(texNew1, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

	for (int i = 0; i < 6; ++i)
		glTextureImage2DEXT(texNew1, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32F, widthIn, heightIn, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glNamedFramebufferTexture(fboNew1, GL_DEPTH_ATTACHMENT, texNew1, 0);
	glNamedFramebufferDrawBuffer(fboNew1, GL_NONE);
	glNamedFramebufferReadBuffer(fboNew1, GL_NONE);

	if (glCheckNamedFramebufferStatus(fboNew1, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with shadowN_create FBO1" << endl;

	return { name, widthIn, heightIn, fboNew0, texNew0, 0, fboNew1, texNew1 };
}

void writeShadow(shared_ptr<Object> obj)
{

	//for each light in allShadow, render each object into the light's FBO0...except for point lights which render into FBO1
	for (auto &i : myAbj.allShadow)
	{
		if (i.name == obj->name->val_s) // if it's a light
		{
			myAbj.shadowObj = obj; // store the light that we're rendering the shadowmap for

			if (obj->camLiType->val_s == "DIR" || obj->camLiType->val_s == "SPOT")
			{
				//cout << "in WRITESHADOW DIR/SPOT for " << obj->name->val_s << endl;
				
				glBindFramebuffer(GL_FRAMEBUFFER, i.fbo0);
				glViewport(0, 0, i.width, i.height);
				glClear(GL_DEPTH_BUFFER_BIT);

				glUseProgram2("pShadowAnim");

				for (auto &j : myAbj.allObj)
				{
					if (j->type == "OBJ" && j->shadowCast->val_b && searchUp(j) && j->anim->val_b && (j->Ko->val_f == 1.f && j->alphaM->val_s == "BLANK_ALPHA"))
						j->render(); //
				}

				glUseProgram2("pShadow");

				for (auto &j : myAbj.allObj)
				{
					if (j->type == "OBJ" && j->shadowCast->val_b && searchUp(j) && !j->anim->val_b && (j->Ko->val_f == 1.f && j->alphaM->val_s == "BLANK_ALPHA"))
						j->render(); //
				}
			}

			else if (obj->camLiType->val_s == "POINT")
			{
				//cout << "in WRITESHADOW POINT for " << obj->name->val_s << endl;

				//glBindFramebuffer(GL_FRAMEBUFFER, i.fbo1);
				//glViewport(0, 0, i.width, i.height);

				//for (int j = 0; j < 6; ++j)
				//{
				//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, i.tex1_32, 0);
				//	glDrawBuffer(GL_DEPTH_ATTACHMENT);
				//	glClear(GL_DEPTH_BUFFER_BIT);

				//	myAbj.MM_cube = glm::translate(glm::mat4(1.f), -glm::vec3(obj->tx->val_f, obj->ty->val_f, obj->tz->val_f));
				//	myAbj.VM_cube = glm::lookAt(glm::vec3(0.f), cubeDirs[j].targ, cubeDirs[j].up);
				//	myAbj.PM_cube = glm::perspective(glm::radians(90.f), 1.f, obj->nearShadow->val_f, obj->farShadow->val_f);

				//	glUseProgram2("pShadowAnim");

				//	for (auto &k : myAbj.allObj)
				//	{
				//		if (k->type == "OBJ" && k->shadowCast->val_b && searchUp(k) && k->anim->val_b)
				//			k->render(); //
				//	}

				//	glUseProgram2("pShadow");

				//	for (auto &k : myAbj.allObj)
				//	{
				//		if (k->type == "OBJ" && k->shadowCast->val_b && searchUp(k) && !k->anim->val_b)
				//			k->render(); //
				//	}
				//}
			}

			obj->dirtyShadow = 0;
		}
	}
}

AbjNode topLayer(TexMap mapIn)
{
	for (auto &i : mapIn.layer)
	{
		if (i.idx == 0)
			return i;
	}

	AbjNode myLayer;

	return myLayer;
}

int countLights()
{
	auto count = 0;

	for (auto &i : myAbj.allCamLi)
	{
		if (!i->ref && i->v->val_b && i->camLiTypeGet("light"))
			count++;
	}

	return count;
}

glm::vec2 toNDC(glm::vec2 pt, string mode) //normalized device coordinates
{
	if (mode == "SELRECT")
	{
		pt.x = (2.f * pt.x / myAbj.width) - 1.f;
		pt.y = (2.f * pt.y / myAbj.height) - 1.f;
		pt.y *= -1.f;
	}

	else
	{
		pt.x = pt.x / myAbj.width;
		pt.y = pt.y / myAbj.height;
	}

	return pt;
}

void getPtsBetweenRect()
{
	if (!myAbj.selRectPts_color.empty())
		myAbj.selRectPts_color.clear();

	int bigX, smallX, bigY, smallY;

	bigX = int(glm::max(myAbj.rayP.x, myAbj.pMouseNew.x));
	smallX = int(glm::min(myAbj.rayP.x, myAbj.pMouseNew.x));
	bigY = int(glm::max(myAbj.rayP.y, myAbj.pMouseNew.y));
	smallY = int(glm::min(myAbj.rayP.y, myAbj.pMouseNew.y));

	if (bigY - smallY > bigX - smallX) //bigger y diff
	{
		for (int y = smallY; y < bigY; ++y)
		{
			for (int x = smallX; x < bigX; ++x)
			{
				myAbj.selRectPts_color.push_back({ x, y });
				continue;
			}
		}
	}

	else if (bigX - smallX > bigY - smallY) //bigger x diff
	{
		for (int x = smallX; x < bigX; ++x)
		{
			for (int y = smallY; y < bigY; ++y)
			{
				myAbj.selRectPts_color.push_back({ x, y });
				continue;
			}
		}
	}
}

GLuint gaussianBlur2(GLuint src, AbjNode dest, int passes)
{
	if (passes == 0)
		return src;

	gaussianRecursivePasses(src, dest, passes, 0);

	return myAbj.tempGauss;
}

GLuint gaussianBlur(AbjNode src, AbjNode dest, int passes)
{
	if (passes == 0)
		return src.tex0_32;

	gaussianRecursivePasses(src.tex0_32, dest, passes, 0);

	return myAbj.tempGauss;
}

GLuint gaussianLinear(GLuint src, AbjNode dest)
{
	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
			glBindFramebuffer(GL_FRAMEBUFFER, dest.fbo0);

		else
			glBindFramebuffer(GL_FRAMEBUFFER, dest.fbo1);

		glViewport(0, 0, dest.width, dest.height);
		glClear(GL_COLOR_BUFFER_BIT);

		myAbj.rttGaussIn32 = (i == 0) ? src : dest.tex0_32;
		up64T(myAbj.rttGaussIn32, myAbj.rttGaussIn64, 1);

		myAbj.myFSQ->gaussStage = i;
		myAbj.myFSQ->render();
	}

	return dest.tex1_32;
}

void gaussianRecursivePasses(GLuint src, AbjNode dest, int passes, int iter)
{
	myAbj.tempGauss = gaussianLinear(src, dest);

	if (iter + 1 < passes)
		gaussianRecursivePasses(myAbj.tempGauss, dest, passes, iter + 1);
}

void downSampRender(AbjNode src, AbjNode dest, int downPixAmt)
{
	glBindFramebuffer(GL_FRAMEBUFFER, dest.fbo0);
	glViewport(0, 0, dest.width, dest.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	up64T(src.tex0_32, myAbj.downSamp_64, 1);

	myAbj.texelSize = glm::vec2(downPixAmt / src.width, downPixAmt / src.height);
	myAbj.myFSQ->render();
}

void bloomRender()
{
	glUseProgram2("pDown");

	for (int i = 0; i < 6; ++i) //DOWNSAMP
	{
		if (i == 0)
			downSampRender(myAbj.defN, myAbj.downN[i], 2);

		else
			downSampRender(myAbj.downN[i - 1], myAbj.downN[i], 2);
	}

	glUseProgram2("pGauss");

	for (int i = 0; i < 6; ++i)
		gaussianBlur(myAbj.downN[i], myAbj.bloomGaussN[i], 4);

	glBindFramebuffer(GL_FRAMEBUFFER, myAbj.bloomN.fbo0);
	glViewport(0, 0, myAbj.bloomN.width, myAbj.bloomN.height);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram2("pBloom");
	myAbj.myFSQ->render();
}

void brushInit()
{
	auto newBrush = make_shared<Brush>();
	newBrush->name = "round";
	//newBrush->scale = glm::vec3(.5f);
	newBrush->scale = glm::vec3(.05f);
	//newBrush->opac = 1.f;
	//newBrush->opac = .5f;
	newBrush->opac = .05f;
	//newBrush->opac = .025f;
	//newBrush->rgb = glm::vec3(0.f, 0.f, 1.f);
	myAbj.allBrushes.push_back(newBrush);

	auto newEraser = make_shared<Brush>();
	newEraser->name = "square";
	newEraser->scale = glm::vec3(.05f);
	newEraser->opac = 1.f;
	myAbj.allBrushes.push_back(newEraser);

	for (auto &i : myAbj.allBrushes)
	{
		if (i->name == "round")
			myAbj.selBrush = i;

		if (i->name == "square")
			myAbj.selEraser = i;
	}
}