#include "stdafx.h"
#include "PointLight.h"
#include "Game.h"
#include "jsonUtil.h"
#include "RenderObj.h"


PointLight::PointLight(Game* game, RenderObj* obj) : Component(obj), mLightData(game->AllocateLight()), mGame(game)
{

}

PointLight::~PointLight()
{
	mGame->FreeLight(mLightData);
}

void PointLight::LoadProperties(const rapidjson::Value& properties)
{
	if (!mLightData)
		return;
	GetVectorFromJSON(properties, "lightColor", mLightData->lightColor);
	GetFloatFromJSON(properties, "innerRadius", mLightData->innerRadius);
	GetFloatFromJSON(properties, "outerRadius", mLightData->outerRadius);
}

void PointLight::Update(float deltaTime)
{
	if (!mLightData)
		return;
	mLightData->position = mParent->GetPositionInWorld();
}
