#pragma once
#include "component.h"
#include "engineMath.h"

class AssetManager;
class Game;

class FollowCam : public Component
{
public:
	FollowCam(Game* pGame, RenderObj* pObj);

	void LoadProperties(const rapidjson::Value& properties) override;

	void Update(float deltaTime) override;

private:
	Vector3 mOffset;
	Game* mGame;
};