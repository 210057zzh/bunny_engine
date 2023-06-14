#pragma once
#include "engineMath.h"
#include "Graphics.h"

class AssetManager;
class Texture;
class Shader;

class Material
{
public:
	class MaterialConstants
	{
	public:
		Vector3 diffuseColor;
		uint8_t padding[4]{};
		Vector3 specularColor;
		float specularPower{};
	};
	MaterialConstants m_material_constants;

	Material();
	~Material();

	static Material* StaticLoad(const WCHAR* fileName, AssetManager* pManager);
	bool Load(const WCHAR* fileName, AssetManager* pAssetManager);

	void SetActive();
	void SetShader(const Shader* shader);
	void SetTexture(int slot, const Texture* texture);
	void SetDiffuseColor(const Vector3& color);
	void SetSpecularColor(const Vector3& color);
	void SetSpecularPower(float power);

private:
	const Shader* mShader = nullptr;
	const Texture* mTextures[Graphics::TEXTURE_SLOT_TOTAL] = {};
	ID3D11Buffer* mMaterialConstantsBuffer = nullptr;
};
