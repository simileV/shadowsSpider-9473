#version 450 core

#if defined(GL_core_profile)
#extension GL_ARB_bindless_texture : require
#endif

in Vert
{
    vec2 uv;
} v;

layout(bindless_sampler, location = 0) uniform sampler2D aliased;
layout(location = 0) out vec3 Ci;

uniform vec4 comboU0; //vec4(fxaaSubPix, fxaaEdgeThr, fxaaEdgeThrMin)

//#define FXAA_QUALITY__PRESET 29
#define FXAA_QUALITY__PRESET 39


#ifndef FXAA_QUALITY__PRESET
    #define FXAA_QUALITY__PRESET 12
#endif

#if (FXAA_QUALITY__PRESET == 12)
    #define FXAA_QUALITY__PS 5
    #define FXAA_QUALITY__P0 1.0
    #define FXAA_QUALITY__P1 1.5
    #define FXAA_QUALITY__P2 2.0
    #define FXAA_QUALITY__P3 4.0
    #define FXAA_QUALITY__P4 12.0
#endif

#if (FXAA_QUALITY__PRESET == 13)
    #define FXAA_QUALITY__PS 6
    #define FXAA_QUALITY__P0 1.0
    #define FXAA_QUALITY__P1 1.5
    #define FXAA_QUALITY__P2 2.0
    #define FXAA_QUALITY__P3 2.0
    #define FXAA_QUALITY__P4 4.0
    #define FXAA_QUALITY__P5 12.0
#endif

#if (FXAA_QUALITY__PRESET == 15)
    #define FXAA_QUALITY__PS 8
    #define FXAA_QUALITY__P0 1.0
    #define FXAA_QUALITY__P1 1.5
    #define FXAA_QUALITY__P2 2.0
    #define FXAA_QUALITY__P3 2.0
    #define FXAA_QUALITY__P4 2.0
    #define FXAA_QUALITY__P5 2.0
    #define FXAA_QUALITY__P6 4.0
    #define FXAA_QUALITY__P7 12.0
#endif

#if (FXAA_QUALITY__PRESET == 20)
    #define FXAA_QUALITY__PS 3
    #define FXAA_QUALITY__P0 1.5
    #define FXAA_QUALITY__P1 2.0
    #define FXAA_QUALITY__P2 8.0
#endif

#if (FXAA_QUALITY__PRESET == 25)
    #define FXAA_QUALITY__PS 8
    #define FXAA_QUALITY__P0 1.0
    #define FXAA_QUALITY__P1 1.5
    #define FXAA_QUALITY__P2 2.0
    #define FXAA_QUALITY__P3 2.0
    #define FXAA_QUALITY__P4 2.0
    #define FXAA_QUALITY__P5 2.0
    #define FXAA_QUALITY__P6 4.0
    #define FXAA_QUALITY__P7 8.0
#endif

#if (FXAA_QUALITY__PRESET == 29)
    #define FXAA_QUALITY__PS 12
    #define FXAA_QUALITY__P0 1.0
    #define FXAA_QUALITY__P1 1.5
    #define FXAA_QUALITY__P2 2.0
    #define FXAA_QUALITY__P3 2.0
    #define FXAA_QUALITY__P4 2.0
    #define FXAA_QUALITY__P5 2.0
    #define FXAA_QUALITY__P6 2.0
    #define FXAA_QUALITY__P7 2.0
    #define FXAA_QUALITY__P8 2.0
    #define FXAA_QUALITY__P9 2.0
    #define FXAA_QUALITY__P10 4.0
    #define FXAA_QUALITY__P11 8.0
#endif

#if (FXAA_QUALITY__PRESET == 39)
        #define FXAA_QUALITY__PS 12
        #define FXAA_QUALITY__P0 1.0
        #define FXAA_QUALITY__P1 1.0
        #define FXAA_QUALITY__P2 1.0
        #define FXAA_QUALITY__P3 1.0
        #define FXAA_QUALITY__P4 1.0
        #define FXAA_QUALITY__P5 1.5
        #define FXAA_QUALITY__P6 2.0
        #define FXAA_QUALITY__P7 2.0
        #define FXAA_QUALITY__P8 2.0
        #define FXAA_QUALITY__P9 2.0
        #define FXAA_QUALITY__P10 4.0
        #define FXAA_QUALITY__P11 8.0
#endif

#define FxaaSat(x) clamp(x, 0.f, 1.f)

float FxaaLuma(vec4 rgba) { return rgba.w; }

float CalcLuma(vec3 rgb)
{
    vec3 luma = vec3(.299f, .587f, .114f);
    luma = pow(luma, vec3(1.f / 2.2f)); //linearize

    return dot(rgb, luma);
}

vec4 MakeRGBA(vec3 rgb)
{
    return vec4(rgb, CalcLuma(rgb));
}

vec4 FxaaTexTop(sampler2D t, vec2 p)
{
    return MakeRGBA(textureLod(t, p, 0.f).rgb);
}

vec4 FxaaTexOff(sampler2D t, vec2 p, ivec2 o,vec2 r)
{
    return MakeRGBA(textureLodOffset(t, p, 0.f, o).rgb);
}

vec4 FxaaTexAlpha4(sampler2D t, vec2 p)
{
    vec4 R = textureGather(t, p, 0);
    vec4 G = textureGather(t, p, 1);
    vec4 B = textureGather(t, p, 2);

    float one = CalcLuma(vec3(R.r, G.r, B.r));
    float two = CalcLuma(vec3(R.g, G.g, B.g));
    float three = CalcLuma(vec3 (R.b, G.b, B.b));
    float four = CalcLuma(vec3 (R.a, G.a, B.a));

    return vec4(one, two, three, four);
}

vec4 FxaaTexOffAlpha4(sampler2D t, vec2 p, ivec2 o)
{
    vec4 R = textureGatherOffset(t, p, o, 0);
    vec4 G = textureGatherOffset(t, p, o, 1);
    vec4 B = textureGatherOffset(t, p, o, 2);

    float one = CalcLuma(vec3(R.r, G.r, B.r));
    float two = CalcLuma(vec3(R.g, G.g, B.g));
    float three = CalcLuma(vec3 (R.b, G.b, B.b));
    float four = CalcLuma(vec3 (R.a, G.a, B.a));

    return vec4(one, two, three, four);
}

vec4 FxaaPixelShader(
    sampler2D tex,
    vec2 pos,
    vec2 fxaaQualityRcpFrame,
    float fxaaQualitySubpix,
    float fxaaQualityEdgeThreshold,
    float fxaaQualityEdgeThresholdMin)
{
    vec2 posM;
    posM.x = pos.x;
    posM.y = pos.y;

    vec4 luma4A = FxaaTexAlpha4(tex, posM);
    vec4 luma4B = FxaaTexOffAlpha4(tex, posM, ivec2(-1, -1));

    #define lumaM luma4A.w
    #define lumaE luma4A.z
    #define lumaS luma4A.x
    #define lumaSE luma4A.y
    #define lumaNW luma4B.w
    #define lumaN luma4B.z
    #define lumaW luma4B.x

    float maxSM = max(lumaS, lumaM);
    float minSM = min(lumaS, lumaM);
    float maxESM = max(lumaE, maxSM);
    float minESM = min(lumaE, minSM);
    float maxWN = max(lumaN, lumaW);
    float minWN = min(lumaN, lumaW);
    float rangeMax = max(maxWN, maxESM);
    float rangeMin = min(minWN, minESM);
    float rangeMaxScaled = rangeMax * fxaaQualityEdgeThreshold;
    float range = rangeMax - rangeMin;
    float rangeMaxClamped = max(fxaaQualityEdgeThresholdMin, rangeMaxScaled);
    bool earlyExit = range < rangeMaxClamped;

    if (earlyExit)
        return FxaaTexTop(tex, pos);

    float lumaNE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, -1), fxaaQualityRcpFrame.xy));
    float lumaSW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1, 1), fxaaQualityRcpFrame.xy));

    float lumaNS = lumaN + lumaS;
    float lumaWE = lumaW + lumaE;
    float subpixRcpRange = 1.f / range;
    float subpixNSWE = lumaNS + lumaWE;
    float edgeHorz1 = (-2.f * lumaM) + lumaNS;
    float edgeVert1 = (-2.f * lumaM) + lumaWE;

    float lumaNESE = lumaNE + lumaSE;
    float lumaNWNE = lumaNW + lumaNE;
    float edgeHorz2 = (-2.f * lumaE) + lumaNESE;
    float edgeVert2 = (-2.f * lumaN) + lumaNWNE;

    float lumaNWSW = lumaNW + lumaSW;
    float lumaSWSE = lumaSW + lumaSE;
    float edgeHorz4 = (abs(edgeHorz1) * 2.f) + abs(edgeHorz2);
    float edgeVert4 = (abs(edgeVert1) * 2.f) + abs(edgeVert2);
    float edgeHorz3 = (-2.f * lumaW) + lumaNWSW;
    float edgeVert3 = (-2.f * lumaS) + lumaSWSE;
    float edgeHorz = abs(edgeHorz3) + edgeHorz4;
    float edgeVert = abs(edgeVert3) + edgeVert4;

    float subpixNWSWNESE = lumaNWSW + lumaNESE;
    float lengthSign = fxaaQualityRcpFrame.x;
    bool horzSpan = edgeHorz >= edgeVert;
    float subpixA = subpixNSWE * 2.f + subpixNWSWNESE;

    if (!horzSpan) lumaN = lumaW;
    if (!horzSpan) lumaS = lumaE;
    if (horzSpan) lengthSign = fxaaQualityRcpFrame.y;
    float subpixB = (subpixA * (1.f / 12.f)) - lumaM;

    float gradientN = lumaN - lumaM;
    float gradientS = lumaS - lumaM;
    float lumaNN = lumaN + lumaM;
    float lumaSS = lumaS + lumaM;
    bool pairN = abs(gradientN) >= abs(gradientS);
    float gradient = max(abs(gradientN), abs(gradientS));
    if (pairN) lengthSign = -lengthSign;
    float subpixC = FxaaSat(abs(subpixB) * subpixRcpRange);

    vec2 posB;
    posB.x = posM.x;
    posB.y = posM.y;
    vec2 offNP;
    offNP.x = (!horzSpan) ? 0.f : fxaaQualityRcpFrame.x;
    offNP.y = ( horzSpan) ? 0.f : fxaaQualityRcpFrame.y;
    if (!horzSpan) posB.x += lengthSign * .5f;
    if ( horzSpan) posB.y += lengthSign * .5f;

    vec2 posN;
    posN.x = posB.x - offNP.x * FXAA_QUALITY__P0;
    posN.y = posB.y - offNP.y * FXAA_QUALITY__P0;
    vec2 posP;
    posP.x = posB.x + offNP.x * FXAA_QUALITY__P0;
    posP.y = posB.y + offNP.y * FXAA_QUALITY__P0;
    float subpixD = ((-2.f)*subpixC) + 3.f;
    float lumaEndN = FxaaLuma(FxaaTexTop(tex, posN));
    float subpixE = subpixC * subpixC;
    float lumaEndP = FxaaLuma(FxaaTexTop(tex, posP));

    if (!pairN) lumaNN = lumaSS;
    float gradientScaled = gradient * 1.f / 4.f;
    float lumaMM = lumaM - lumaNN * .5f;
    float subpixF = subpixD * subpixE;
    bool lumaMLTZero = lumaMM < 0.f;

    lumaEndN -= lumaNN * .5f;
    lumaEndP -= lumaNN * .5f;
    bool doneN = abs(lumaEndN) >= gradientScaled;
    bool doneP = abs(lumaEndP) >= gradientScaled;
    if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P1;
    if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P1;
    bool doneNP = (!doneN) || (!doneP);
    if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P1;
    if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P1;

    if (doneNP) {
        if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
        if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
        if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
        if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
        doneN = abs(lumaEndN) >= gradientScaled;
        doneP = abs(lumaEndP) >= gradientScaled;
        if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P2;
        if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P2;
        doneNP = (!doneN) || (!doneP);
        if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P2;
        if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P2;

        #if (FXAA_QUALITY__PS > 3)
        if (doneNP) {
            if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
            if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
            if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
            if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
            doneN = abs(lumaEndN) >= gradientScaled;
            doneP = abs(lumaEndP) >= gradientScaled;
            if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P3;
            if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P3;
            doneNP = (!doneN) || (!doneP);
            if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P3;
            if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P3;

            #if (FXAA_QUALITY__PS > 4)
            if (doneNP) {
                if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                doneN = abs(lumaEndN) >= gradientScaled;
                doneP = abs(lumaEndP) >= gradientScaled;
                if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P4;
                if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P4;
                doneNP = (!doneN) || (!doneP);
                if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P4;
                if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P4;

                #if (FXAA_QUALITY__PS > 5)
                if (doneNP) {
                    if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                    if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                    if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                    if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                    doneN = abs(lumaEndN) >= gradientScaled;
                    doneP = abs(lumaEndP) >= gradientScaled;
                    if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P5;
                    if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P5;
                    doneNP = (!doneN) || (!doneP);
                    if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P5;
                    if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P5;

                    #if (FXAA_QUALITY__PS > 6)
                    if (doneNP) {
                        if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                        if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                        if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                        if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                        doneN = abs(lumaEndN) >= gradientScaled;
                        doneP = abs(lumaEndP) >= gradientScaled;
                        if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P6;
                        if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P6;
                        doneNP = (!doneN) || (!doneP);
                        if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P6;
                        if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P6;

                        #if (FXAA_QUALITY__PS > 7)
                        if (doneNP) {
                            if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                            if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                            if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                            if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                            doneN = abs(lumaEndN) >= gradientScaled;
                            doneP = abs(lumaEndP) >= gradientScaled;
                            if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P7;
                            if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P7;
                            doneNP = (!doneN) || (!doneP);
                            if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P7;
                            if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P7;

    #if (FXAA_QUALITY__PS > 8)
    if (doneNP) {
        if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
        if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
        if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
        if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
        doneN = abs(lumaEndN) >= gradientScaled;
        doneP = abs(lumaEndP) >= gradientScaled;
        if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P8;
        if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P8;
        doneNP = (!doneN) || (!doneP);
        if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P8;
        if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P8;

        #if (FXAA_QUALITY__PS > 9)
        if (doneNP) {
            if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
            if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
            if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
            if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
            doneN = abs(lumaEndN) >= gradientScaled;
            doneP = abs(lumaEndP) >= gradientScaled;
            if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P9;
            if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P9;
            doneNP = (!doneN) || (!doneP);
            if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P9;
            if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P9;

            #if (FXAA_QUALITY__PS > 10)
            if (doneNP) {
                if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                doneN = abs(lumaEndN) >= gradientScaled;
                doneP = abs(lumaEndP) >= gradientScaled;
                if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P10;
                if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P10;
                doneNP = (!doneN) || (!doneP);
                if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P10;
                if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P10;

                #if (FXAA_QUALITY__PS > 11)
                if (doneNP) {
                    if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                    if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                    if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                    if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                    doneN = abs(lumaEndN) >= gradientScaled;
                    doneP = abs(lumaEndP) >= gradientScaled;
                    if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P11;
                    if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P11;
                    doneNP = (!doneN) || (!doneP);
                    if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P11;
                    if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P11;

                    #if (FXAA_QUALITY__PS > 12)
                    if (doneNP) {
                        if (!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                        if (!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                        if (!doneN) lumaEndN = lumaEndN - lumaNN * .5f;
                        if (!doneP) lumaEndP = lumaEndP - lumaNN * .5f;
                        doneN = abs(lumaEndN) >= gradientScaled;
                        doneP = abs(lumaEndP) >= gradientScaled;
                        if (!doneN) posN.x -= offNP.x * FXAA_QUALITY__P12;
                        if (!doneN) posN.y -= offNP.y * FXAA_QUALITY__P12;
                        doneNP = (!doneN) || (!doneP);
                        if (!doneP) posP.x += offNP.x * FXAA_QUALITY__P12;
                        if (!doneP) posP.y += offNP.y * FXAA_QUALITY__P12;

                    }
                    #endif

                }
                #endif

            }
            #endif

        }
        #endif

    }
    #endif

                        }
                        #endif

                    }
                    #endif

                }
                #endif

            }
            #endif

        }
        #endif

    }

    float dstN = posM.x - posN.x;
    float dstP = posP.x - posM.x;
    if (!horzSpan) dstN = posM.y - posN.y;
    if (!horzSpan) dstP = posP.y - posM.y;

    bool goodSpanN = (lumaEndN < 0.f) != lumaMLTZero;
    float spanLength = (dstP + dstN);
    bool goodSpanP = (lumaEndP < 0.f) != lumaMLTZero;
    float spanLengthRcp = 1.f / spanLength;

    bool directionN = dstN < dstP;
    float dst = min(dstN, dstP);
    bool goodSpan = directionN ? goodSpanN : goodSpanP;
    float subpixG = subpixF * subpixF;
    float pixelOffset = (dst * (-spanLengthRcp)) + .5f;
    float subpixH = subpixG * fxaaQualitySubpix;

    float pixelOffsetGood = goodSpan ? pixelOffset : 0.f;
    float pixelOffsetSubpix = max(pixelOffsetGood, subpixH);
    if (!horzSpan) posM.x += pixelOffsetSubpix * lengthSign;
    if ( horzSpan) posM.y += pixelOffsetSubpix * lengthSign;

    return FxaaTexTop(tex, posM);
}

void main()
{
    vec2 texelSize = 1.f / textureSize(aliased, 0);

	//uniform vec4 comboU0; //vec4(fxaaSubPix, fxaaEdgeThr, fxaaEdgeThrMin)
	Ci = FxaaPixelShader(aliased, v.uv, texelSize, comboU0.x, comboU0.y, comboU0.z).rgb;
}
