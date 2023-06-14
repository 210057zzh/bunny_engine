#include "stdafx.h"
#include "CollisionBox.h"
#include "jsonUtil.h"
#include "RenderObj.h"



CollisionBox::CollisionBox(RenderObj* pObj, Physics* physics)
	: Component(pObj), mPhysics(physics)
{
	mPhysics->AddObj(this);
}

CollisionBox::~CollisionBox()
{
	mPhysics->RemoveObj(this);
}

void CollisionBox::LoadProperties(const rapidjson::Value& properties)
{
	GetVectorFromJSON(properties, "min", mAABB.mMinCorner);
	GetVectorFromJSON(properties, "max", mAABB.mMaxCorner);
}

const Physics::AABB CollisionBox::GetAABB() const
{
	const auto& transform = mParent->mPerObjectConstants.c_modelToWorld;
	const auto scale = transform.GetScale().x;
	auto copy = mAABB;
	copy.mMinCorner *= scale;
	copy.mMaxCorner *= scale;
	const auto translation = mParent->GetPositionInWorld();
	const auto translationTransform = Matrix4::CreateTranslation(translation);
	copy.mMinCorner = Transform(copy.mMinCorner, translationTransform);
	copy.mMaxCorner = Transform(copy.mMaxCorner, translationTransform);
	return copy;
}
