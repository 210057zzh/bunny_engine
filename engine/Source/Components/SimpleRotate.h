#pragma once
#include "Component.h"

class SimpleRotate : public Component
{
public:
	SimpleRotate(RenderObj* pObj)
		: Component(pObj)
	{
	}

	void LoadProperties(const rapidjson::Value& properties) override;

	void Update(float deltaTime) override;
private:
	float mSpeed = 0.0f;
};
