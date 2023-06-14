#include "stdafx.h"
#include "SimpleRotate.h"
#include "jsonUtil.h"
#include "RenderObj.h"

void SimpleRotate::LoadProperties(const rapidjson::Value& properties)
{
	GetFloatFromJSON(properties, "speed", mSpeed);
}

void SimpleRotate::Update(float deltaTime)
{
	static float angle = 0.0f;
	auto scale = mParent->mPerObjectConstants.c_modelToWorld.GetScale();
	auto translate = mParent->mPerObjectConstants.c_modelToWorld.GetTranslation();
	angle += deltaTime * mSpeed;

	mParent->mPerObjectConstants.c_modelToWorld = Matrix4::CreateScale(scale) * Matrix4::CreateRotationZ(angle)
		* Matrix4::CreateTranslation(translate);
}
