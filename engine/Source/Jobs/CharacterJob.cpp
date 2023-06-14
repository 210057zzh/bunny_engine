#include "stdafx.h"
#include "CharacterJob.h"

#include "Animation.h"
#include "engineMath.h"
#include "Skeleton.h"
#include "SkinnedObj.h"
#include "Components/Character.h"

CharacterJob::CharacterJob(Character* c) : m_character_(c)
{

}

void CharacterJob::DoIt()
{
	std::vector<Matrix4> currentPose;
	m_character_->mCurrentAnim->GetGlobalPoseAtTime(currentPose, m_character_->mSkeleton, m_character_->mTime);
	for (size_t i = 0; i < currentPose.size(); i++)
	{
		m_character_->mSkinnedParent->mSkinConstants.c_skinMatrix[i] = m_character_->mSkeleton->GetGlobalInvBindPoses()[i] * currentPose[i];
	}
}
