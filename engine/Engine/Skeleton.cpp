#include "stdafx.h"
#include "Skeleton.h"
#include "jsonUtil.h"
#include <rapidjson/include/rapidjson/document.h>

size_t Skeleton::GetNumBones() const
{
	return mBones.size();
}

const Skeleton::Bone& Skeleton::GetBone(size_t idx) const
{
	return mBones[idx];
}

const std::vector<Skeleton::Bone>& Skeleton::GetBones() const
{
	return mBones;
}

const std::vector<Matrix4>& Skeleton::GetGlobalInvBindPoses() const
{
	return mInverseBindMatrices;
}

Skeleton* Skeleton::StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager)
{
	auto* skeleton = new Skeleton();
	if (false == skeleton->Load(fileName))
	{
		delete skeleton;
		return nullptr;
	}
	return skeleton;
}

bool Skeleton::Load(const WCHAR* fileName)
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

	{
		const auto& bonesData = doc["bones"];
		mBones.reserve(bonesData.Size());
		for (rapidjson::SizeType i = 0; i < bonesData.Size(); i++)
		{
			std::string name;
			Vector3 translation;
			Quaternion rotation;
			int parent;
			const auto& boneData = bonesData[i];
			GetStringFromJSON(boneData, "name", name);
			GetIntFromJSON(boneData, "parent", parent);
			const auto& bindPoseData = boneData["bindpose"];
			GetQuaternionFromJSON(bindPoseData, "rot", rotation);
			GetVectorFromJSON(bindPoseData, "trans", translation);
			mBones.emplace_back();
			mBones.back().mParentIndex = parent;
			mBones.back().mBoneName = std::move(name);
			mBones.back().mTransform.mRotation = rotation;
			mBones.back().mTransform.mTranslation = translation;
		}
	}
	ComputeGlobalInvBindPose();

	return true;
}

void Skeleton::ComputeGlobalInvBindPose()
{
	mInverseBindMatrices.resize(mBones.size());
	for (size_t i = 0; i < mBones.size(); i++)
	{
		auto& bone = mBones[i];
		mInverseBindMatrices[i] = bone.mTransform.ToMatrix();
		if (bone.mParentIndex != -1)
		{
			mInverseBindMatrices[i] = mInverseBindMatrices[i] * mInverseBindMatrices[bone.mParentIndex];
		}
	}

	for (auto& m : mInverseBindMatrices)
	{
		m.Invert();
	}
}
