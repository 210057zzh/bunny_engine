#pragma once
#include <vector>
#include "engineMath.h"

class Component;
class Mesh;
class Material;
class VertexBuffer;

class RenderObj
{
public:
	class PerObjectConstants
	{
	public:
		Matrix4 c_modelToWorld;
	};

	RenderObj(const Mesh* mesh);
	PerObjectConstants mPerObjectConstants;
	virtual  ~RenderObj();
	virtual void Draw();
	void AddComponent(Component* pComp);
	virtual void Update(float deltaTime);
	Vector3 GetPositionInWorld() const;

protected:
	const Mesh* mMesh;
	ID3D11Buffer* mObjectConstantsBuffer = nullptr;
	std::vector<Component*> mComponents;
};
