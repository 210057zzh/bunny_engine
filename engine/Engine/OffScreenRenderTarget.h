#pragma once

class Texture;

class OffScreenRenderTarget
{
public:
	ID3D11RenderTargetView* MScreenTextureRenderView() const
	{
		return mScreenTextureRenderView;
	}

	OffScreenRenderTarget(int inWidth, int inHeight, DXGI_FORMAT format, bool depthEnabled = false);
	~OffScreenRenderTarget();

	void SetActiveRenderTarget() const;
	void SetAsInput(int slot) const;


private:
	int mWidth{};
	int mHeight{};
	bool mDepthEnabled = false;
	Texture* mScreenTexture;
	ID3D11RenderTargetView* mScreenTextureRenderView;
};
