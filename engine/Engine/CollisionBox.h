#pragma once
#include "Component.h"
#include "physics.h"

class CollisionBox : public Component
{
public:
	explicit CollisionBox(RenderObj* pObj, Physics* physics);
	~CollisionBox() override;
	void LoadProperties(const rapidjson::Value& properties) override;
	const Physics::AABB GetAABB() const;

private:
	Physics::AABB mAABB;
	Physics* mPhysics;
};
