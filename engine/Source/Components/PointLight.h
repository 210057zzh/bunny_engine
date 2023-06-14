#pragma once
#include "Component.h"

class Game;

namespace Lights
{
	struct PointLightData;
}

class PointLight : public Component
{
public:
	PointLight(Game* game, RenderObj* obj);
	~PointLight() override;
	void LoadProperties(const rapidjson::Value& properties) override;
	void Update(float deltaTime) override;

private:
	Lights::PointLightData* mLightData;
	Game* mGame;
};
