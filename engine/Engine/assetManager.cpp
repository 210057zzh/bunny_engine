#include "stdafx.h"
#include "assetManager.h"

AssetManager::AssetManager() :
	mShaderCache(this),
	mTextureCache(this),
	mMaterialCache(this),
	mMeshCache(this),
	mSkeletonCache(this),
	mAnimationCache(this)
{
}

AssetManager::~AssetManager()
= default;

Shader* AssetManager::GetShader(const std::wstring& shaderName)
{
	return mShaderCache.Get(shaderName);
}

void AssetManager::SetShader(const std::wstring& shaderName, Shader* pShader)
{
	mShaderCache.Cache(shaderName, pShader);
}

Texture* AssetManager::LoadTexture(const std::wstring& fileName)
{
	return mTextureCache.Load(fileName);
}

Material* AssetManager::LoadMaterial(const std::wstring& materialName)
{
	return mMaterialCache.Load(materialName);
}

Mesh* AssetManager::LoadMesh(const std::wstring& fileName)
{
	return mMeshCache.Load(fileName);
}

Skeleton* AssetManager::LoadSkeleton(const std::wstring& fileName)
{
	return mSkeletonCache.Load(fileName);
}

Animation* AssetManager::LoadAnimation(const std::wstring& fileName)
{
	return mAnimationCache.Load(fileName);
}

void AssetManager::Clear()
{
	mShaderCache.Clear();
	mMaterialCache.Clear();
	mTextureCache.Clear();
	mMeshCache.Clear();
	mSkeletonCache.Clear();
	mAnimationCache.Clear();
}
