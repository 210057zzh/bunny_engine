﻿#include "stdafx.h"
#include "BoneTransform.h"

BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform result;
	result.mRotation = Slerp(a.mRotation, b.mRotation, f);
	result.mTranslation = Lerp(a.mTranslation, b.mTranslation, f);
	return result;
}
