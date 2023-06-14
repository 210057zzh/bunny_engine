#pragma once
#include "BoneTransform.h"

class AssetManager;

class Skeleton
{
public:
	struct Bone
	{
		BoneTransform mTransform;
		std::string mBoneName;
		int mParentIndex = -1;
	};

	size_t GetNumBones() const;
	const Bone& GetBone(size_t idx) const;
	const std::vector<Bone>& GetBones() const;
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const;
	static Skeleton* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);
	bool Load(const WCHAR* fileName);

private:
	std::vector<Bone> mBones;
	std::vector<Matrix4> mInverseBindMatrices;
	void ComputeGlobalInvBindPose();
};
