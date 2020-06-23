#ifndef SETUP_TEXSHADERS_H
#define SETUP_TEXSHADERS_H

#include "Core.h"
#include "GL_render.h"
#include "Object.h"

inline size_t uboAligned(size_t size) { return ((size + 255) / 256) * 256; }

typedef struct
{
	glm::vec3 targ, up;
} CubemapDirections;

typedef struct
{
	uint dwSize;
	uint dwFlags;
	uint dwHeight;
	uint dwWidth;
	uint dwPitchOrLinearSize;
	uint dwDepth;
	uint dwMipMapCount;
	uint dwReserved1[11];

	struct
	{
		uint dwSize;
		uint dwFlags;
		uint dwFourCC;
		uint dwRGBBitCount;
		uint dwRBitMask;
		uint dwGBitMask;
		uint dwBBitMask;
		uint dwAlphaBitMask;
	} sPixelFormat;

	struct
	{
		uint dwCaps1;
		uint dwCaps2;
		uint dwDDSX;
		uint dwReserved;
	} sCaps;

	uint dwReserved2;

} ddsHeader;

void uboInit();
void uboUp();
void brushInit();

void mapInit();
AbjNode texN_create(string, string, string, int);
void up64N(AbjNode &, bool);
void up64T(GLuint &, GLuint64 &, bool);

void proInit();
GLuint glCreateProg(string, string, string);
GLuint glCreateShaderStage(const char *, GLenum);
char* glShaderRead(const char *);
void glShaderError(GLuint);
void glUseProgram2(string);

void addDeleteShadows(string);
AbjNode shadowN_create(string, int, int);
void writeShadow(shared_ptr<Object>);
AbjNode topLayer(TexMap);

//ETC
int countLights();
glm::vec2 toNDC(glm::vec2, string);
void getPtsBetweenRect();

//PP
GLuint gaussianLinear(GLuint, AbjNode);
void gaussianRecursivePasses(GLuint, AbjNode, int, int);
GLuint gaussianBlur(AbjNode, AbjNode, int);
GLuint gaussianBlur2(GLuint, AbjNode, int);
void downSampRender(AbjNode, AbjNode, int);
void bloomRender();

#endif