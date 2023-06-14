#pragma once
#include "engineMath.h"

class Camera
{
public:
	class PerCameraConstants
	{
	public:
		Matrix4  c_viewProj;
		Vector3 c_cameraPosition;
		int8_t padding[4];
	};
	Camera();
	virtual ~Camera();
	void SetActive();

	Matrix4 mWorldToCameraMatrix;
	Matrix4 mProjectionMatrix;
	PerCameraConstants mCameraConstants;
protected:
	ID3D11Buffer* mCameraBuffer = nullptr;
};
