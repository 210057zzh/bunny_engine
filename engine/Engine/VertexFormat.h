#pragma once
#include "engineMath.h"
#include "Graphics.h"

struct VertexPosColor
{
	Vector3 pos;
	Graphics::Color4 color;
};

struct VertexPosColorTexCoord
{
	Vector3 pos;
	Graphics::Color4 color;
	Vector2 texcoord;
};

struct VertexPosNormalColorTexCoord
{
	Vector3 pos;
	Vector3 normal;
	Graphics::Color4 color;
	Vector2 texcoord;
};

struct VertexPosNormalTexCoord
{
	Vector3 pos;
	Vector3 normal;
	Vector2 texcoord;
};

struct VertexPosNormalBoneIndicesBoneWeightsTexCoord
{
	Vector3 pos;
	Vector3 normal;
	uint8_t boneIndices[4]{};
	uint8_t boneWeights[4]{};
	Vector2 texcoord;
};

struct VertexPosNormalTangentTexCoord
{
	Vector3 pos;
	Vector3 normal;
	Vector3 tangent;
	Vector2 texcoord;
};

struct VertexPosTexcoord
{
	Vector3 pos;
	Vector2 texcoord;
};

using VertexSkinned = VertexPosNormalBoneIndicesBoneWeightsTexCoord;
using VertexNormalMap = VertexPosNormalTangentTexCoord;
using VertexCopy = VertexPosTexcoord;
