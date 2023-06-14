#include "stdafx.h"
#include "Character.h"

#include "assetManager.h"
#include "Game.h"
#include "JobManager.h"
#include "SkinnedObj.h"
#include "jsonUtil.h"
#include "Profiler.h"
#include "stringUtil.h"
#include "Jobs/CharacterJob.h"

Character::Character(Game* game, SkinnedObj* obj) :
	Component(obj), mSkinnedParent(obj), mGame(game)
{
}

void Character::LoadProperties(const rapidjson::Value& properties)
{
	std::wstring buffer;
	GetWStringFromJSON(properties, "skeleton", buffer);
	mSkeleton = mGame->mAssetManager->LoadSkeleton(buffer);
	const auto& animsData = properties["animations"];
	for (rapidjson::SizeType i = 0; i < animsData.Size(); i++)
	{
		const auto& animData = animsData[i];
		std::string shortName = animData[0].GetString();
		std::string animNameTemp = animData[1].GetString();

		std::wstring animName;
		StringUtil::String2WString(animName, animNameTemp);

		mAnims[shortName] = mGame->mAssetManager->LoadAnimation(animName);
	}
}

bool Character::SetAnim(const std::string& animName)
{
	const auto itr = mAnims.find(animName);
	if (itr != mAnims.end())
	{
		mCurrentAnim = itr->second;
		mTime = 0.0f;
		return true;
	}
	return false;
}

void Character::UpdateAnim(float deltaTime)
{
	if (mCurrentAnim)
	{
		mTime += deltaTime;

		mTime = fmodf(mTime, mCurrentAnim->GetLength());

		JobManager::Get().AddJob(std::make_unique<CharacterJob>(this));

	}
}

void Character::Update(float deltaTime)
{
	//PROFILE_SCOPE(CharacterUpdate);
	if (!mCurrentAnim)
	{
		SetAnim("run");
	}
	UpdateAnim(deltaTime);
}
