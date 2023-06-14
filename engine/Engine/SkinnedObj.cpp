#include "stdafx.h"
#include "SkinnedObj.h"

#include "Graphics.h"

SkinnedObj::SkinnedObj(const Mesh* mesh) : RenderObj(mesh)
{
	mSkinBuffer = Graphics::Get()->CreateGraphicsBuffer(nullptr,
		sizeof(mSkinConstants), D3D11_BIND_CONSTANT_BUFFER,
		D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
}

SkinnedObj::~SkinnedObj()
{
	mSkinBuffer->Release();
}

void SkinnedObj::Draw()
{
	Graphics::Get()->UploadBuffer(mSkinBuffer, &mSkinConstants, sizeof(mSkinConstants));
	Graphics::Get()->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_SKIN, 1, &mSkinBuffer);

	RenderObj::Draw();
}


