#include "stdafx.h"
#include "RenderObj.h"

#include "Component.h"
#include "Graphics.h"
#include "Material.h"
#include "mesh.h"

RenderObj::RenderObj(const Mesh* mesh)
	: mMesh(mesh),
	mObjectConstantsBuffer(Graphics::Get()->CreateGraphicsBuffer(nullptr, sizeof(mPerObjectConstants), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC))
{
	mPerObjectConstants.c_modelToWorld = Matrix4::CreateRotationZ(Math::ToRadians(45.0f));
}

RenderObj::~RenderObj()
{
	mObjectConstantsBuffer->Release();
}

void RenderObj::Draw()
{
	Graphics::Get()->UploadBuffer(mObjectConstantsBuffer, &mPerObjectConstants, sizeof(mPerObjectConstants));
	Graphics::Get()->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_RENDEROBJ, 1, &mObjectConstantsBuffer);
	mMesh->Draw();
}

void RenderObj::AddComponent(Component* pComp)
{
	mComponents.emplace_back(pComp);
}

void RenderObj::Update(float deltaTime)
{
	for (auto p : mComponents)
	{
		p->Update(deltaTime);
	}
}

Vector3 RenderObj::GetPositionInWorld() const
{
	return mPerObjectConstants.c_modelToWorld.GetTranslation();
}
