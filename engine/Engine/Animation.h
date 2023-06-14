#pragma once
#include "BoneTransform.h"

class Skeleton;
class AssetManager;

class Animation
{
public:
	uint32_t GetNumBones() const;
	uint32_t GetNumFrames() const;
	float GetLength() const;

	static Animation* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);
	bool Load(const WCHAR* fileName);

	void GetGlobalPoseAtTime(
		std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime
	) const;

private:
	uint32_t mNumBones = 0;
	uint32_t mNumFrames = 0;
	float mLengthInSeconds = 0;
	std::vector<std::vector<BoneTransform>> mAnimData;
};
