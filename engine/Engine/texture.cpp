#include "stdafx.h"
#include "texture.h"
#include "Graphics.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"
#include "DirectXTK\Inc\WICTextureLoader.h"
#include <string>

Texture::Texture()
	: mResource(nullptr)
	, mView(nullptr)
	, mWidth(0)
	, mHeight(0)
{
}

Texture::~Texture()
{
	Free();
}

void Texture::Free()
{
	if (nullptr != mView)
	{
		mView->Release();
		mView = nullptr;
	}
	if (nullptr != mResource)
	{
		mResource->Release();
		mResource = nullptr;
	}
	mWidth = 0;
	mHeight = 0;
}

bool Texture::Load(const WCHAR* fileName)
{
	Free();     // in case there was already a texture loaded here, release it

	ID3D11Device* pDev = Graphics::Get()->GetDevice();

	std::wstring fileStr(fileName);
	std::wstring extension = fileStr.substr(fileStr.find_last_of('.'));
	HRESULT hr = E_FAIL;
	if (extension == L".dds" || extension == L".DDS")
		hr = DirectX::CreateDDSTextureFromFile(pDev, fileName, &mResource, &mView);
	else
		hr = DirectX::CreateWICTextureFromFile(pDev, fileName, &mResource, &mView);
	DbgAssert(hr == S_OK, "Problem Creating Texture From File");
	if (S_OK != hr)
		return false;

	CD3D11_TEXTURE2D_DESC textureDesc;
	((ID3D11Texture2D*)mResource)->GetDesc(&textureDesc);
	mWidth = textureDesc.Width;
	mHeight = textureDesc.Height;

	return true;
}

Texture* Texture::StaticLoad(const WCHAR* fileName, AssetManager* pManager)
{
	Texture* pTex = new Texture();
	if (false == pTex->Load(fileName))
	{
		delete pTex;
		return nullptr;
	}
	return pTex;
}

void Texture::SetActive(int slot) const
{
	Graphics::Get()->SetActiveTexture(slot, mView);
}

ID3D11RenderTargetView* Texture::CreateRenderTarget(int inWidth, int inHeight, DXGI_FORMAT format)
{
	mResource = [this, inWidth, inHeight, format]
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = inWidth;
		desc.Height = inHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		ID3D11Texture2D* pTexture;

		Graphics::Get()->GetDevice()->CreateTexture2D(&desc, nullptr, &pTexture);

		return pTexture;
	}();

	mView = [this]
	{
		ID3D11ShaderResourceView* view;
		Graphics::Get()->GetDevice()->CreateShaderResourceView(mResource, nullptr, &view);
		return view;
	}();

	ID3D11RenderTargetView* view;
	Graphics::Get()->GetDevice()->CreateRenderTargetView(mResource, nullptr, &view);
	return view;
}
