#include "stdafx.h"
#include "Physics.h"

#include "CollisionBox.h"

Physics::AABB::AABB(Vector3 minCorner, Vector3 maxCorner) : mMinCorner(minCorner), mMaxCorner(maxCorner)
{

}

Physics::LineSegment::LineSegment(Vector3 start, Vector3 end) :mStartingPoint(start), mEndingPoint(end)
{

}

bool Physics::Intersect(const AABB& a, const AABB& b, AABB* pOverlap)
{
	bool intersect = (a.mMaxCorner.x > b.mMinCorner.x &&
		a.mMinCorner.x < b.mMaxCorner.x&&
		a.mMaxCorner.y > b.mMinCorner.y &&
		a.mMinCorner.y < b.mMaxCorner.y&&
		a.mMaxCorner.z > b.mMinCorner.z &&
		a.mMinCorner.z < b.mMaxCorner.z);
	if (!intersect)
	{
		return false;
	}
	if (pOverlap)
	{
		pOverlap->mMinCorner.x = std::max(a.mMinCorner.x, b.mMinCorner.x);
		pOverlap->mMinCorner.y = std::max(a.mMinCorner.y, b.mMinCorner.y);
		pOverlap->mMinCorner.z = std::max(a.mMinCorner.z, b.mMinCorner.z);

		pOverlap->mMaxCorner.x = std::min(a.mMaxCorner.x, b.mMaxCorner.x);
		pOverlap->mMaxCorner.y = std::min(a.mMaxCorner.y, b.mMaxCorner.y);
		pOverlap->mMaxCorner.z = std::min(a.mMaxCorner.z, b.mMaxCorner.z);
	}
	return intersect;
}

bool Physics::Intersect(const LineSegment& segment, const AABB& box, Vector3* pHitPoint)
{
	auto tmin = 0.0f;
	auto tmax = 1.0f;
	const auto d = segment.mEndingPoint - segment.mStartingPoint;
	const auto& p = segment.mStartingPoint;
	const auto& a = box;
	for (int i = 0; i < 3; i++)
	{
		if (Math::IsCloseEnuf(d[i], 0.0f))
		{
			if (p[i] < a.mMinCorner[i] || p[i] > a.mMaxCorner[i])
			{
				return false;
			}
		}
		else
		{
			auto ood = 1.0f / d[i];
			auto t1 = (a.mMinCorner[i] - p[i]) * ood;
			auto t2 = (a.mMaxCorner[i] - p[i]) * ood;

			if (t1 > t2)
			{
				std::swap(t1, t2);
			}

			tmin = Math::Max(tmin, t1); // Rather than: if (t1 > tmin) tmin = t1;
			tmax = Math::Min(tmax, t2); // Rather than: if (t2 < tmax) tmax = t2;

			if (tmin > tmax)
			{
				return false;
			}
		}
	}
	if (pHitPoint)
	{
		*pHitPoint = p + d * tmin;
	}
	return true;

}

bool Physics::UnitTest()
{
	bool ok = true;
	struct TestAABB
	{
		AABB a;
		AABB b;
		AABB overlap;
	};
	const TestAABB testAABB[] =
	{
	{
	AABB(Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f)),
	AABB(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-110.0f, -10.0f, -10.0f), Vector3(-90.0f, 10.0f, 10.0f)),
	AABB(Vector3(-100.0f, -10.0f, -10.0f), Vector3(-90.0f, 10.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(90.0f, -10.0f, -10.0f), Vector3(110.0f, 10.0f, 10.0f)),
	AABB(Vector3(90.0f, -10.0f, -10.0f), Vector3(100.0f, 10.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -110.0f, -10.0f), Vector3(10.0f, -90.0f, 10.0f)),
	AABB(Vector3(-10.0f, -100.0f, -10.0f), Vector3(10.0f, -90.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, 90.0f, -10.0f), Vector3(10.0f, 110.0f, 10.0f)),
	AABB(Vector3(-10.0f, 90.0f, -10.0f), Vector3(10.0f, 100.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -10.0f, -110.0f), Vector3(10.0f, 10.0f, -90.0f)),
	AABB(Vector3(-10.0f, -10.0f, -100.0f), Vector3(10.0f, 10.0f, -90.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -10.0f, 90.0f), Vector3(10.0f, 10.0f, 110.0f)),
	AABB(Vector3(-10.0f, -10.0f, 90.0f), Vector3(10.0f, 10.0f, 100.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-120.0f, -10.0f, -10.0f), Vector3(-110.0f, 10.0f, 10.0f)),
	AABB(Vector3::One, Vector3::Zero)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(110.0f, -10.0f, -10.0f), Vector3(120.0f, 10.0f, 10.0f)),
	AABB(Vector3::One, Vector3::Zero)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -120.0f, -10.0f), Vector3(10.0f, -110.0f, 10.0f)),
	AABB(Vector3::One, Vector3::Zero)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, 110.0f, -10.0f), Vector3(10.0f, 120.0f, 10.0f)),
	AABB(Vector3::One, Vector3::Zero)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -10.0f, -120.0f), Vector3(10.0f, 10.0f, -110.0f)),
	AABB(Vector3::One, Vector3::Zero)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -10.0f, 110.0f), Vector3(10.0f, 10.0f, 120.0f)),
	AABB(Vector3::One, Vector3::Zero)
	},
	};

	AABB overlap;
	for (int i = 0; i < 7; i++)
	{
		const auto& testCase = testAABB[i];
		ok &= Intersect(testCase.a, testCase.b, &overlap) == true;
		DbgAssert(ok, "fail");
		ok &= IsCloseEnuf(overlap.mMinCorner, testCase.overlap.mMinCorner) && IsCloseEnuf(overlap.mMaxCorner, testCase.overlap.mMaxCorner);
		DbgAssert(ok, "fail");
	}

	for (int i = 7; i < std::size(testAABB); i++)
	{
		const auto& testCase = testAABB[i];
		ok &= Intersect(testCase.a, testCase.b, &overlap) == false;
		DbgAssert(ok, "fail");
	}

	struct TestSegment
	{
		AABB box;
		LineSegment segment;
		bool hit;
		Vector3 point;
	};
	const TestSegment testSegment[] =
	{
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(-110.0f, 0.0f, 0.0f), Vector3(-90.0f, 0.0f, 0.0f)),
	true, Vector3(-100.0f, 0.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, -110.0f, 0.0f), Vector3(0.0f, -90.0f, 0.0f)),
	true, Vector3(0.0f, -100.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, -110.0f), Vector3(0.0f, 0.0f, -90.0f)),
	true, Vector3(0.0f, 0.0f, -100.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(110.0f, 0.0f, 0.0f), Vector3(90.0f, 0.0f, 0.0f)),
	true, Vector3(100.0f, 0.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 110.0f, 0.0f), Vector3(0.0f, 90.0f, 0.0f)),
	true, Vector3(0.0f, 100.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, 110.0f), Vector3(0.0f, 0.0f, 90.0f)),
	true, Vector3(0.0f, 0.0f, 100.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(-120.0f, 0.0f, 0.0f), Vector3(-110.0f, 0.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, -120.0f, 0.0f), Vector3(0.0f, -110.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, -120.0f), Vector3(0.0f, 0.0f, -110.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(120.0f, 0.0f, 0.0f), Vector3(110.0f, 0.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 120.0f, 0.0f), Vector3(0.0f, 110.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, 120.0f), Vector3(0.0f, 0.0f, 110.0f)),
	false, Vector3::Zero
	},
	};

	Vector3 point;
	int i = 0;
	for (const auto& testCase : testSegment)
	{
		i++;
		ok &= Intersect(testCase.segment, testCase.box, &point) == testCase.hit;
		DbgAssert(ok, "fail");
		if (testCase.hit)
		{
			ok &= IsCloseEnuf(testCase.point, point);
			DbgAssert(ok, "fail");
		}
	}

	return ok;
}

void Physics::AddObj(const CollisionBox* pObj)
{
	mBoxes.emplace_back(pObj);
}

void Physics::RemoveObj(const CollisionBox* pObj)
{
	auto itr = std::find(mBoxes.begin(), mBoxes.end(), pObj);
	if (itr != mBoxes.end())
	{
		mBoxes.erase(itr);
	}
}

bool Physics::RayCast(const LineSegment& segment, Vector3* pHitPoint) const
{
	float distance = INFINITY;
	bool hit = false;
	for (auto& box : mBoxes)
	{
		Vector3 hitpointForThisBox;
		auto AABB = box->GetAABB();
		if (Intersect(segment, AABB, &hitpointForThisBox))
		{
			const auto d = (hitpointForThisBox - segment.mStartingPoint).LengthSq();
			if (d < distance)
			{
				hit = true;
				*pHitPoint = hitpointForThisBox;
				distance = d;
			}
		}
	}
	return hit;
}
