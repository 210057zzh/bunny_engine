﻿#include "stdafx.h"
#include "RenderCube.h"

#include "mesh.h"
#include "VertexBuffer.h"
#include "VertexFormat.h"

const static VertexPosNormalColorTexCoord cubeVertex[] =
{
	/*
	{Vector3(-0.500000, -0.500000, -0.500000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(-0.000000, 0.000000, -1.000000)},
	{Vector3(0.500000, 0.500000, -0.500000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(-0.000000, 0.000000, -1.000000)},
	{Vector3(-0.500000, 0.500000, -0.500000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(-0.000000, 0.000000, -1.000000)},
	{Vector3(0.500000, -0.500000, -0.500000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(0.000000, -0.000000, -1.000000)},
	{Vector3(0.500000, 0.500000, -0.500000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(0.000000, -0.000000, -1.000000)},
	{Vector3(-0.500000, -0.500000, -0.500000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(0.000000, -0.000000, -1.000000)},
	{Vector3(-0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(-1.000000, 0.000000, 0.000000)},
	{Vector3(-0.500000, 0.500000, -0.500000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(-1.000000, 0.000000, 0.000000)},
	{Vector3(-0.500000, 0.500000, 0.500000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(-1.000000, 0.000000, 0.000000)},
	{Vector3(-0.500000, -0.500000, -0.500000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(-1.000000, 0.000000, 0.000000)},
	{Vector3(-0.500000, 0.500000, -0.500000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(-1.000000, 0.000000, 0.000000)},
	{Vector3(-0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(-1.000000, 0.000000, 0.000000)},
	{Vector3(-0.500000, -0.500000, 0.500000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(0.000000, 0.000000, 1.000000)},
	{Vector3(0.500000, 0.500000, 0.500000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(0.000000, 0.000000, 1.000000)},
	{Vector3(0.500000, -0.500000, 0.500000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(0.000000, 0.000000, 1.000000)},
	{Vector3(-0.500000, 0.500000, 0.500000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(0.000000, 0.000000, 1.000000)},
	{Vector3(0.500000, 0.500000, 0.500000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(0.000000, 0.000000, 1.000000)},
	{Vector3(-0.500000, -0.500000, 0.500000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(0.000000, 0.000000, 1.000000)},
	{Vector3(0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(1.000000, 0.000000, 0.000000)},
	{Vector3(0.500000, 0.500000, -0.500000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(1.000000, 0.000000, 0.000000)},
	{Vector3(0.500000, -0.500000, -0.500000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(1.000000, 0.000000, 0.000000)},
	{Vector3(0.500000, 0.500000, 0.500000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(1.000000, 0.000000, -0.000000)},
	{Vector3(0.500000, 0.500000, -0.500000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(1.000000, 0.000000, -0.000000)},
	{Vector3(0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(1.000000, 0.000000, -0.000000)},
	{Vector3(-0.500000, 0.500000, -0.500000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(0.000000, 1.000000, 0.000000)},
	{Vector3(0.500000, 0.500000, 0.500000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(0.000000, 1.000000, 0.000000)},
	{Vector3(-0.500000, 0.500000, 0.500000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(0.000000, 1.000000, 0.000000)},
	{Vector3(0.500000, 0.500000, -0.500000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(0.000000, 1.000000, 0.000000)},
	{Vector3(0.500000, 0.500000, 0.500000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(0.000000, 1.000000, 0.000000)},
	{Vector3(-0.500000, 0.500000, -0.500000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(0.000000, 1.000000, 0.000000)},
	{Vector3(-0.500000, -0.500000, -0.500000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(0.000000, -1.000000, -0.000000)},
	{Vector3(0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(0.000000, -1.000000, -0.000000)},
	{Vector3(0.500000, -0.500000, -0.500000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,0.000000),
	Vector3(0.000000, -1.000000, -0.000000)},
	{Vector3(-0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,1.000000),
	Vector3(-0.000000, -1.000000, 0.000000)},
	{Vector3(0.500000, -0.500000, 0.500000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000),
	Vector3(-0.000000, -1.000000, 0.000000)},
	{Vector3(-0.500000, -0.500000, -0.500000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000),
	Vector3(-0.000000, -1.000000, 0.000000)},
	*/
	{Vector3(-0.500000, -0.500000, -0.500000),
		Vector3(-0.000000, 0.000000, -1.000000),
		Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
		Vector2(0.000000, 0.000000)},
	{ Vector3(0.500000, 0.500000, -0.500000),
	Vector3(-0.000000, 0.000000, -1.000000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, 0.500000, -0.500000),
	Vector3(-0.000000, 0.000000, -1.000000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(0.500000, -0.500000, -0.500000),
	Vector3(0.000000, -0.000000, -1.000000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(0.500000, 0.500000, -0.500000),
	Vector3(0.000000, -0.000000, -1.000000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, -0.500000, -0.500000),
	Vector3(0.000000, -0.000000, -1.000000),
	 Graphics::Color4(1.000000, 0.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(-0.500000, -0.500000, 0.500000),
	Vector3(-1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(-0.500000, 0.500000, -0.500000),
	Vector3(-1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(-0.500000, 0.500000, 0.500000),
	Vector3(-1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, -0.500000, -0.500000),
	Vector3(-1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(-0.500000, 0.500000, -0.500000),
	Vector3(-1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(-0.500000, -0.500000, 0.500000),
	Vector3(-1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(-0.500000, -0.500000, 0.500000),
	Vector3(0.000000, 0.000000, 1.000000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(0.500000, 0.500000, 0.500000),
	Vector3(0.000000, 0.000000, 1.000000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(0.500000, -0.500000, 0.500000),
	Vector3(0.000000, 0.000000, 1.000000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(-0.500000, 0.500000, 0.500000),
	Vector3(0.000000, 0.000000, 1.000000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(0.500000, 0.500000, 0.500000),
	Vector3(0.000000, 0.000000, 1.000000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, -0.500000, 0.500000),
	Vector3(0.000000, 0.000000, 1.000000),
	 Graphics::Color4(1.000000, 0.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(0.500000, -0.500000, 0.500000),
	Vector3(1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(0.500000, 0.500000, -0.500000),
	Vector3(1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(0.500000, -0.500000, -0.500000),
	Vector3(1.000000, 0.000000, 0.000000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(0.500000, 0.500000, 0.500000),
	Vector3(1.000000, 0.000000, -0.000000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(0.500000, 0.500000, -0.500000),
	Vector3(1.000000, 0.000000, -0.000000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(0.500000, -0.500000, 0.500000),
	Vector3(1.000000, 0.000000, -0.000000),
	 Graphics::Color4(0.000000, 1.000000, 1.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(-0.500000, 0.500000, -0.500000),
	Vector3(0.000000, 1.000000, 0.000000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(0.500000, 0.500000, 0.500000),
	Vector3(0.000000, 1.000000, 0.000000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, 0.500000, 0.500000),
	Vector3(0.000000, 1.000000, 0.000000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(0.500000, 0.500000, -0.500000),
	Vector3(0.000000, 1.000000, 0.000000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(0.500000, 0.500000, 0.500000),
	Vector3(0.000000, 1.000000, 0.000000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, 0.500000, -0.500000),
	Vector3(0.000000, 1.000000, 0.000000),
	 Graphics::Color4(1.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(-0.500000, -0.500000, -0.500000),
	Vector3(0.000000, -1.000000, -0.000000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
	{ Vector3(0.500000, -0.500000, 0.500000),
	Vector3(0.000000, -1.000000, -0.000000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(0.500000, -0.500000, -0.500000),
	Vector3(0.000000, -1.000000, -0.000000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,0.000000) },
	{ Vector3(-0.500000, -0.500000, 0.500000),
	Vector3(-0.000000, -1.000000, 0.000000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,1.000000) },
	{ Vector3(0.500000, -0.500000, 0.500000),
	Vector3(-0.000000, -1.000000, 0.000000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(1.000000,1.000000) },
	{ Vector3(-0.500000, -0.500000, -0.500000),
	Vector3(-0.000000, -1.000000, 0.000000),
	 Graphics::Color4(0.000000, 1.000000, 0.000000, 1.000000),
	 Vector2(0.000000,0.000000) },
};

const static uint16_t cubeIndex[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
};

/*
RenderCube::RenderCube(Material* material) :
	RenderObj(
		new VertexBuffer(
			cubeVertex,
			static_cast<uint32_t>(std::size(cubeVertex)),
			static_cast <uint32_t>(sizeof(*cubeVertex)),
			cubeIndex,
			static_cast <uint32_t>(std::size(cubeIndex)),
			static_cast <uint32_t>(sizeof(*cubeIndex))),
		material
	)
{
	char buffer[500];
	std::string result;
	for
	(int i = 0; i < std::size(cubeVertex); i += 3)
	{
		auto& a = cubeVertex[i];
		auto& b = cubeVertex[i + 1];
		auto& c = cubeVertex[i + 2];
		auto normal = Cross(a.pos - b.pos, c.pos - b.pos);
		for (int j = i; j < i + 3; j++)
		{
			auto& v = cubeVertex[j];
			sprintf_s(buffer,
				"{Vector3(%f, %f, %f),\n"
				"Vector3(%f, %f, %f),\n"
				" Graphics::Color4(%f, %f, %f, %f),\n"
				" Vector2(%f,%f)},\n"
				,
				v.pos.x, v.pos.y, v.pos.z,
				normal.x, normal.y, normal.z,
				v.color.r, v.color.g, v.color.b, v.color.a,
				v.texcoord.x, v.texcoord.y
			);
			result += buffer;
		}
	}
	int i = 0;
}
*/

RenderCube::RenderCube(Material* material) : RenderObj(nullptr)
{
	mMesh = new Mesh(new VertexBuffer(
		cubeVertex,
		static_cast<uint32_t>(std::size(cubeVertex)),
		static_cast <uint32_t>(sizeof(*cubeVertex)),
		cubeIndex,
		static_cast <uint32_t>(std::size(cubeIndex)),
		static_cast <uint32_t>(sizeof(*cubeIndex))),
		material);
}

RenderCube::~RenderCube()
{
	delete mMesh;
}