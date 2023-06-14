#pragma once
#include "engineMath.h"

class BoneTransform
{
public:
	Quaternion mRotation;
	Vector3 mTranslation;

	static BoneTransform Interpolate(
		const BoneTransform& a, const BoneTransform& b, float f);

	Matrix4 ToMatrix() const
	{
		return Matrix4::CreateFromQuaternion(mRotation) * Matrix4::CreateTranslation(mTranslation);
	}
};
