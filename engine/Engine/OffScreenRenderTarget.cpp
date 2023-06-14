#include "stdafx.h"
#include "OffScreenRenderTarget.h"

#include "Graphics.h"
#include "texture.h"

OffScreenRenderTarget::OffScreenRenderTarget(int inWidth, int inHeight, DXGI_FORMAT format, bool depthEnabled) :
	mWidth(inWidth), mHeight(inHeight), mDepthEnabled(depthEnabled), mScreenTexture(new Texture())
{
	mScreenTextureRenderView = mScreenTexture->CreateRenderTarget(inWidth, inHeight, format);
}



OffScreenRenderTarget::~OffScreenRenderTarget()
{
	delete mScreenTexture;
	mScreenTextureRenderView->Release();
}

void OffScreenRenderTarget::SetActiveRenderTarget() const
{
	Graphics::Get()->SetRenderTarget(mScreenTextureRenderView, mDepthEnabled ? Graphics::Get()->GetDepthView() : nullptr);
	Graphics::Get()->SetViewport(0.0f, 0.0f, mWidth, mHeight);
}

void OffScreenRenderTarget::SetAsInput(int slot) const
{
	mScreenTexture->SetActive(slot);
}


