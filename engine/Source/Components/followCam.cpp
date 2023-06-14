#include "stdafx.h"
#include "camera.h"
#include "components\followCam.h"
#include "game.h"
#include "jsonUtil.h"
#include "renderObj.h"
#include "stringUtil.h"


FollowCam::FollowCam(Game* pGame, RenderObj* pObj)
	: Component(pObj)
	, mGame(pGame)
{
	Matrix4 mat = mParent->mPerObjectConstants.c_modelToWorld;
	mat = Matrix4::CreateRotationX(Math::PiOver2) * mat;	//mrwTODO this 90 rotation accounts for the orientation of the model :(
}

void FollowCam::LoadProperties(const rapidjson::Value& properties)
{
	Component::LoadProperties(properties);
	GetVectorFromJSON(properties, "offset", mOffset);
}

void FollowCam::Update(float deltaTime)
{
	Camera* pCamera = mGame->mCamera;
	Matrix4 mat = Matrix4::CreateTranslation(mParent->mPerObjectConstants.c_modelToWorld.GetTranslation() + mOffset);
	mat.Invert();
	pCamera->mWorldToCameraMatrix = mat;
}