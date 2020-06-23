#include "CreateN.h"

bool fboPrep()
{
	myAbj.gBufN = gBufN_create();

	myAbj.normalRuffN = normalRuffN_create();

	myAbj.depthRevN = depthRevN_create(myAbj.width, myAbj.height);
	up64N(myAbj.depthRevN, 1);

	myAbj.bgN = bgN_create(myAbj.width, myAbj.height); //giz / grid / sky
	up64N(myAbj.bgN, 1);

	myAbj.tonemapN = tonemapN_create();
	up64N(myAbj.tonemapN, 1);

	myAbj.alphaGaussN = dualN_create("alphaGauss", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.alphaGaussN, 1);

	myAbj.defN = defN_create();
	up64N(myAbj.defN, 1);

	myAbj.fxaaN = singleN_create("fxaa", GL_RGB16F, myAbj.width, myAbj.height);
	up64N(myAbj.fxaaN, 1);

	myAbj.brushN = dualN_create("brush", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.brushN, 1);

	myAbj.brushBGN = dualN_create("brushBG", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.brushBGN, 1);

	myAbj.brushTempN = dualN_create("brushTemp", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.brushTempN, 1);

	myAbj.eraserN = dualN_create("eraser", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.eraserN, 1);

	myAbj.cursorN = singleN_create("cursor", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.cursorN, 1);

	myAbj.sobelN = singleN_create("sobel", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.sobelN, 1);

	myAbj.ssaoN = singleN_create("ssao", GL_R16F, myAbj.width, myAbj.height);
	up64N(myAbj.ssaoN, 1);

	myAbj.billN = singleN_create("bill", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.billN, 1);

	myAbj.ssaoGaussN = dualN_create("ssaoGauss", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.ssaoGaussN, 1);

	myAbj.ssrN = singleN_create("ssr", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.ssrN, 1);

	myAbj.lumaInitN = singleN_create("lumaInit", GL_R16F, 1024, 1024);
	up64N(myAbj.lumaInitN, 1);

	myAbj.lumaAdaptN[0] = singleN_create("lumaAdapt0", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.lumaAdaptN[0], 1);

	myAbj.lumaAdaptN[1] = singleN_create("lumaAdapt1", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.lumaAdaptN[1], 1);

	//myAbj.stereoN[0] = singleN_create("stereo0", GL_R16F, myAbj.width, myAbj.height);
	myAbj.stereoN[0] = singleN_create("stereo0", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.stereoN[0], 1);

	//myAbj.stereoN[1] = singleN_create("stereo1", GL_R16F, myAbj.width, myAbj.height);
	myAbj.stereoN[1] = singleN_create("stereo1", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.stereoN[1], 1);

	myAbj.stereoPrevN = singleN_create("stereoPrev", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.stereoPrevN, 1);

	bloomBufferCreate();

	return 1;
}

AbjNode gBufN_create()
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	GLenum DrawBuffers[] =
	{
		GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7,
	};

	GLuint setupRTT[8];
	glCreateTextures(GL_TEXTURE_2D, 8, setupRTT);

	for (int i = 0; i < 8; ++i)
	{
		if (i == 0 || i == 7)
			glTextureStorage2D(setupRTT[i], 1, GL_RGBA32F, myAbj.width, myAbj.height);

		else
			glTextureStorage2D(setupRTT[i], 1, GL_RGBA32UI, myAbj.width, myAbj.height);

		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glNamedFramebufferTexture(fboNew, DrawBuffers[i], setupRTT[i], 0);
	}

	myAbj.gBuf0_32 = setupRTT[0];
	up64T(myAbj.gBuf0_32, myAbj.gBuf0_64, 1);

	myAbj.gBuf1_32 = setupRTT[1];
	up64T(myAbj.gBuf1_32, myAbj.gBuf1_64, 1);

	myAbj.gBuf2_32 = setupRTT[2];
	up64T(myAbj.gBuf2_32, myAbj.gBuf2_64, 1);

	myAbj.gBuf3_32 = setupRTT[3];
	up64T(myAbj.gBuf3_32, myAbj.gBuf3_64, 1);

	myAbj.gBuf4_32 = setupRTT[4];
	up64T(myAbj.gBuf4_32, myAbj.gBuf4_64, 1);

	myAbj.gBuf5_32 = setupRTT[5];
	up64T(myAbj.gBuf5_32, myAbj.gBuf5_64, 1);

	myAbj.gBuf6_32 = setupRTT[6];
	up64T(myAbj.gBuf6_32, myAbj.gBuf6_64, 1);

	myAbj.gBuf7_32 = setupRTT[7];
	up64T(myAbj.gBuf7_32, myAbj.gBuf7_64, 1);

	//DEPTH STEN
	glCreateTextures(GL_TEXTURE_2D, 1, &myAbj.gBuf_DS_32);
	glTextureStorage2D(myAbj.gBuf_DS_32, 1, GL_DEPTH32F_STENCIL8, myAbj.width, myAbj.height);
	glTextureParameteri(myAbj.gBuf_DS_32, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myAbj.gBuf_DS_32, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myAbj.gBuf_DS_32, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(myAbj.gBuf_DS_32, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glNamedFramebufferTexture(fboNew, GL_DEPTH_STENCIL_ATTACHMENT, myAbj.gBuf_DS_32, 0);
	glNamedFramebufferDrawBuffers(fboNew, 8, DrawBuffers);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with gBufN_create" << endl;

	return { "gBuf", myAbj.width, myAbj.height, fboNew };
}

AbjNode normalRuffN_create()
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	GLuint setupRTT[2];
	glCreateTextures(GL_TEXTURE_2D, 2, setupRTT);

	for (int i = 0; i < 2; ++i)
	{
		glTextureStorage2D(setupRTT[i], 1, GL_RGBA32F, myAbj.width, myAbj.height);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glNamedFramebufferTexture(fboNew, DrawBuffers[i], setupRTT[i], 0);
	}

	myAbj.normalRuff0_32 = setupRTT[0];
	up64T(myAbj.normalRuff0_32, myAbj.normalRuff0_64, 1);

	myAbj.normalRuff1_32 = setupRTT[1];
	up64T(myAbj.normalRuff1_32, myAbj.normalRuff1_64, 1);

	//DEPTH STEN
	glCreateTextures(GL_TEXTURE_2D, 1, &myAbj.gBufAddT_DS_32);
	glTextureStorage2D(myAbj.gBufAddT_DS_32, 1, GL_DEPTH32F_STENCIL8, myAbj.width, myAbj.height);
	glTextureParameteri(myAbj.gBufAddT_DS_32, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myAbj.gBufAddT_DS_32, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myAbj.gBufAddT_DS_32, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(myAbj.gBufAddT_DS_32, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glNamedFramebufferTexture(fboNew, GL_DEPTH_STENCIL_ATTACHMENT, myAbj.gBufAddT_DS_32, 0);
	glNamedFramebufferDrawBuffers(fboNew, 2, DrawBuffers);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with normalRuffN_create" << endl;

	return { "normalRuff", myAbj.width, myAbj.height, fboNew };
}

AbjNode defN_create()
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	GLuint setupRTT[2];
	glCreateTextures(GL_TEXTURE_2D, 2, setupRTT);

	for (int i = 0; i < 2; ++i)
	{
		glTextureStorage2D(setupRTT[i], 1, GL_RGBA16F, myAbj.width, myAbj.height);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (i == 1)
		{
			glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glNamedFramebufferTexture(fboNew, DrawBuffers[i], setupRTT[i], 0);
	}

	glNamedFramebufferDrawBuffers(fboNew, 2, DrawBuffers);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with defN_create" << endl;

	return { "def", myAbj.width, myAbj.height, fboNew, setupRTT[0], 0, 0, setupRTT[1] };
}

AbjNode depthRevN_create(int width, int height)
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	//DEPTH STEN
	GLuint myDS;
	glCreateTextures(GL_TEXTURE_2D, 1, &myDS);
	glTextureStorage2D(myDS, 1, GL_DEPTH32F_STENCIL8, width, height);
	glTextureParameteri(myDS, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myDS, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myDS, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(myDS, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glNamedFramebufferTexture(fboNew, GL_DEPTH_ATTACHMENT, myDS, 0);
	glNamedFramebufferDrawBuffer(fboNew, GL_NONE);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with depthRevN_create" << endl;

	return { "depthRev", width, height, fboNew, 0, 0, 0, 0, 0, myDS };
}

AbjNode bgN_create(int width, int height)
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	GLuint setupRTT[2];
	glCreateTextures(GL_TEXTURE_2D, 2, setupRTT);

	for (int i = 0; i < 2; ++i)
	{
		glTextureStorage2D(setupRTT[i], 1, GL_RGBA16F, width, height);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glNamedFramebufferTexture(fboNew, DrawBuffers[i], setupRTT[i], 0);
	}

	//DEPTH STEN
	GLuint myDS;
	glCreateTextures(GL_TEXTURE_2D, 1, &myDS);
	glTextureStorage2D(myDS, 1, GL_DEPTH32F_STENCIL8, width, height);
	glTextureParameteri(myDS, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myDS, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(myDS, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(myDS, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glNamedFramebufferTexture(fboNew, GL_DEPTH_STENCIL_ATTACHMENT, myDS, 0);
	glNamedFramebufferDrawBuffers(fboNew, 2, DrawBuffers);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with bgN_create" << endl;

	return { "bg", width, height, fboNew, setupRTT[0], 0, 0, setupRTT[1], 0, myDS };
}

AbjNode tonemapN_create()
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	GLuint setupRTT[2];
	glCreateTextures(GL_TEXTURE_2D, 2, setupRTT);

	for (int i = 0; i < 2; ++i)
	{
		glTextureStorage2D(setupRTT[i], 1, GL_RGB16F, myAbj.width, myAbj.height);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		if (myAbj.myFSQ->fxaaBlur->val_b)
		{
			glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		else
		{
			glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glNamedFramebufferTexture(fboNew, DrawBuffers[i], setupRTT[i], 0);
	}

	glNamedFramebufferDrawBuffers(fboNew, 2, DrawBuffers);

	if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "error with tonemapN_create" << endl;

	return { "tonemap", myAbj.width, myAbj.height, fboNew, setupRTT[0] , 0, 0, setupRTT[1] };
}

AbjNode singleN_create(string name, GLenum format, int width, int height)
{
	GLuint fboNew;
	glCreateFramebuffers(1, &fboNew);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	GLuint texNew[1];
	glCreateTextures(GL_TEXTURE_2D, 1, texNew);

	for (int i = 0; i < 1; ++i)
	{
		auto numMip = 1 + int(floor(log2(glm::max(width, height))));
		glTextureStorage2D(texNew[i], numMip, format, width, height);

		glTextureParameteri(texNew[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(texNew[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		if (name == "paintProj")
		{
			glTextureParameteri(texNew[i], GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(texNew[i], GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		if (name == "lumaInitN" || name == "lumaAdapt0" || name == "lumaAdapt1")
		{
			glTextureParameteri(texNew[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTextureParameteri(texNew[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		else
		{
			glTextureParameteri(texNew[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(texNew[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glGenerateTextureMipmap(texNew[i]);
		glNamedFramebufferTexture(fboNew, DrawBuffers[i], texNew[i], 0);
		glNamedFramebufferDrawBuffers(fboNew, 1, DrawBuffers);

		if (glCheckNamedFramebufferStatus(fboNew, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "error with singleN_create for : " << name << endl;
	}

	return { name, width, height, fboNew, texNew[0] };
}

AbjNode dualN_create(string name, GLenum format, int width, int height)
{
	GLuint nodeNew[2];
	glCreateFramebuffers(2, nodeNew);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	GLuint setupRTT[2];
	glCreateTextures(GL_TEXTURE_2D, 2, setupRTT);

	for (int i = 0; i < 2; ++i)
	{
		glTextureStorage2D(setupRTT[i], 1, format, width, height);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(setupRTT[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glNamedFramebufferTexture(nodeNew[i], DrawBuffers[0], setupRTT[i], 0);
		glNamedFramebufferDrawBuffers(nodeNew[i], 1, DrawBuffers);

		if (glCheckNamedFramebufferStatus(nodeNew[i], GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "error with dualN_create for : " << name << endl;
	}

	return { name, width, height, nodeNew[0], setupRTT[0], 0, nodeNew[1], setupRTT[1] };
}

void bloomBufferCreate()
{
	myAbj.bloomN = singleN_create("bloom", GL_RGBA16F, myAbj.width, myAbj.height);
	up64N(myAbj.bloomN, 1);

	auto widthB = myAbj.width / 2;
	auto heightB = myAbj.height / 2;

	for (int i = 0; i < 6; ++i)
	{
		string conc = "down";
		conc.append(to_string(i));

		myAbj.downN[i] = singleN_create(conc, GL_RGBA16F, widthB, heightB);
		up64N(myAbj.downN[i], 1);

		conc = "bloomGauss";
		conc.append(to_string(i));

		myAbj.bloomGaussN[i] = dualN_create(conc, GL_RGBA16F, widthB, heightB);
		up64N(myAbj.bloomGaussN[i], 1);

		widthB /= 2;
		heightB /= 2;
	}
}

void resizeTexClearMem()
{
	//GBUF FBO
	up64T(myAbj.gBuf0_32, myAbj.gBuf0_64, 0);
	up64T(myAbj.gBuf1_32, myAbj.gBuf1_64, 0);
	up64T(myAbj.gBuf2_32, myAbj.gBuf2_64, 0);
	up64T(myAbj.gBuf3_32, myAbj.gBuf3_64, 0);
	up64T(myAbj.gBuf4_32, myAbj.gBuf4_64, 0);
	up64T(myAbj.gBuf5_32, myAbj.gBuf5_64, 0);
	up64T(myAbj.gBuf6_32, myAbj.gBuf6_64, 0);
	up64T(myAbj.gBuf7_32, myAbj.gBuf7_64, 0);
	up64T(myAbj.gBuf_DS_32, myAbj.gBuf_DS_64, 0);
	glDeleteFramebuffers(1, &myAbj.gBufN.fbo0);

	//NORMALRUFF FBO
	up64T(myAbj.normalRuff0_32, myAbj.normalRuff0_64, 0);
	up64T(myAbj.normalRuff1_32, myAbj.normalRuff1_64, 0);
	up64T(myAbj.gBufAddT_DS_32, myAbj.gBufAddT_DS_64, 0);
	glDeleteFramebuffers(1, &myAbj.normalRuffN.fbo0);

	up64N(myAbj.alphaGaussN, 0);
	up64N(myAbj.bgN, 0);
	up64N(myAbj.bloomN, 0);
	up64N(myAbj.defN, 0);
	up64N(myAbj.fxaaN, 0);
	up64N(myAbj.brushN, 0);
	up64N(myAbj.brushBGN, 0);
	up64N(myAbj.brushTempN, 0);
	up64N(myAbj.sobelN, 0);
	up64N(myAbj.eraserN, 0);
	up64N(myAbj.cursorN, 0);
	up64N(myAbj.ssaoN, 0);
	up64N(myAbj.ssrN, 0);
	up64N(myAbj.ssaoGaussN, 0);
	up64N(myAbj.tonemapN, 0);

	up64N(myAbj.lumaInitN, 0);

	for (int i = 0; i < 2; ++i)
		up64N(myAbj.lumaAdaptN[i], 0);

	up64N(myAbj.stereoN[0], 0);
	up64N(myAbj.stereoN[1], 0);

	myAbj.fboReady = 0;
}