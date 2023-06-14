#include "stdafx.h"
#include "Animation.h"
#include "jsonUtil.h"
#include <rapidjson/include/rapidjson/document.h>

#include "Skeleton.h"

uint32_t Animation::GetNumBones() const
{
	return mNumBones;
}

uint32_t Animation::GetNumFrames() const
{
	return mNumFrames;
}

float Animation::GetLength() const
{
	return mLengthInSeconds;
}

Animation* Animation::StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager)
{
	auto anim = new Animation();
	if (!anim->Load(fileName))
	{
		delete anim;
		return nullptr;
	}
	return anim;
}

bool Animation::Load(const WCHAR* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		DbgAssert(false, "Unable to open Skeleton file");
		return false;
	}

	const auto& sequenceData = doc["sequence"];

	{
		int integer;
		GetIntFromJSON(sequenceData, "frames", integer);
		mNumFrames = integer;
		GetFloatFromJSON(sequenceData, "length", mLengthInSeconds);
		GetIntFromJSON(sequenceData, "bonecount", integer);
		mNumBones = integer;
	}

	mAnimData = std::vector<std::vector<BoneTransform>>(mNumBones, std::vector<BoneTransform>());

	const auto& tracksData = sequenceData["tracks"];

	for (rapidjson::SizeType i = 0; i < tracksData.Size(); i++)
	{
		const auto& trackData = tracksData[i];

		int boneIdx;
		GetIntFromJSON(trackData, "bone", boneIdx);

		const auto& transformsData = trackData["transforms"];

		mAnimData[boneIdx] = std::vector<BoneTransform>(mNumFrames);

		for (rapidjson::SizeType j = 0; j < transformsData.Size(); j++)
		{
			const auto& transformData = transformsData[j];

			GetQuaternionFromJSON(transformData, "rot", mAnimData[boneIdx][j].mRotation);
			GetVectorFromJSON(transformData, "trans", mAnimData[boneIdx][j].mTranslation);
		}
	}

	return true;
}

void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime) const
{
	const float secondsPerFrame = (float)GetLength() / (static_cast<float>(GetNumFrames()) - 1.0f);
	const float f = fmodf(inTime, secondsPerFrame) / secondsPerFrame;
	const auto frameIdx = static_cast<size_t>(inTime / secondsPerFrame);
	const size_t nextFrameIdx = frameIdx + 1 % mNumFrames;

	outPoses.clear();
	outPoses.resize(inSkeleton->GetNumBones());

	for (size_t i = 0; i < outPoses.size(); i++)
	{
		if (!mAnimData[i].empty())
		{
			outPoses[i] *=
				BoneTransform::Interpolate(mAnimData[i][frameIdx],
					mAnimData[i][nextFrameIdx],
					f).ToMatrix();
		}

		const auto parentIdx = inSkeleton->GetBone(i).mParentIndex;

		if (parentIdx != -1)
		{
			outPoses[i] *= outPoses[parentIdx];
		}
	}
}
