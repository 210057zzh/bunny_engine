#pragma once
#include "Animation.h"
#include "assetCache.h"
#include "Material.h"
#include "mesh.h"
#include "Shader.h"
#include "Skeleton.h"
#include "texture.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	Shader* GetShader(const std::wstring& shaderName);
	void SetShader(const std::wstring& shaderName, Shader* pShader);

	Texture* LoadTexture(const std::wstring& fileName);

	Material* LoadMaterial(const std::wstring& materialName);

	Mesh* LoadMesh(const std::wstring& fileName);

	Skeleton* LoadSkeleton(const std::wstring& fileName);

	Animation* LoadAnimation(const std::wstring& fileName);


	void Clear();

private:
	AssetCache<Shader> mShaderCache;
	AssetCache<Texture> mTextureCache;
	AssetCache<Material> mMaterialCache;
	AssetCache<Mesh> mMeshCache;
	AssetCache<Skeleton> mSkeletonCache;
	AssetCache<Animation> mAnimationCache;
};
