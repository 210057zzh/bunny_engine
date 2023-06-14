#pragma once
#include "RenderObj.h"
#include "VertexFormat.h"

class RenderCube : public RenderObj
{
public:
	explicit RenderCube(Material* material);
	~RenderCube() override;
};
