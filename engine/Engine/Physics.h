#pragma once
#include "engineMath.h"

class CollisionBox;

class Physics
{
public:
	class AABB
	{
	public:
		AABB() = default;
		AABB(Vector3 minCorner, Vector3 maxCorner);

		Vector3 mMinCorner;
		Vector3 mMaxCorner;
	};

	class LineSegment
	{
	public:
		LineSegment() = default;
		LineSegment(Vector3 start, Vector3 end);

		Vector3 mStartingPoint;
		Vector3 mEndingPoint;
	};

	static bool Intersect(const AABB& a, const AABB& b, AABB* pOverlap = nullptr);
	static bool Intersect(const LineSegment& segment, const AABB& box,
		Vector3* pHitPoint = nullptr);
	void AddObj(const CollisionBox* pObj);
	void RemoveObj(const CollisionBox* pObj);
	bool RayCast(const LineSegment& segment, Vector3*
		pHitPoint = nullptr) const;

	static bool UnitTest();
private:
	std::vector<const CollisionBox*> mBoxes;

};
