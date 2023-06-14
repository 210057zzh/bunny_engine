#pragma once
#include "Component.h"

class Game;
class Animation;
class Skeleton;
class SkinnedObj;

class Character : public Component
{
public:
	Character(Game* game, SkinnedObj* obj);

	void LoadProperties(const rapidjson::Value& properties) override;
	bool SetAnim(const std::string& animName);
	void UpdateAnim(float deltaTime);
	void Update(float deltaTime) override;

	const Animation* mCurrentAnim = nullptr;

	SkinnedObj* mSkinnedParent;
	Skeleton* mSkeleton = nullptr;
	std::unordered_map<std::string, const Animation*> mAnims;
	float mTime = 0.0f;

	Game* mGame;


protected:

};
