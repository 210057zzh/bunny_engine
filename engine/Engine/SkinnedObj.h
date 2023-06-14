#pragma once
#include "RenderObj.h"

class SkinnedObj : public RenderObj
{
public:
	static constexpr int MAX_BONES = 80;

	struct SkinConstants
	{
		Matrix4 c_skinMatrix[MAX_BONES];
	};

	SkinConstants mSkinConstants;

	SkinnedObj(const Mesh* mesh);
	~SkinnedObj() override;
	void Draw() override;
private:
	ID3D11Buffer* mSkinBuffer = nullptr;
};
