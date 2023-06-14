#include "stdafx.h"
#include "Camera.h"

#include "Graphics.h"

Camera::Camera() : mCameraBuffer(Graphics::Get()->CreateGraphicsBuffer(nullptr, sizeof(mCameraConstants), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC))
{
	DbgAssert(sizeof(PerCameraConstants) % 16 == 0, "sizeof(PerCameraConstants)%16==0");
	mWorldToCameraMatrix = Matrix4::CreateTranslation(Vector3(500.0f, 0.0f, 0.0f));
	mProjectionMatrix =
		Matrix4::CreateRotationY(-Math::PiOver2)
		* Matrix4::CreateRotationZ(-Math::PiOver2)
		* Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
			Graphics::Get()->GetScreenWidth(), Graphics::Get()->GetScreenHeight(),
			25.0f, 10000.0f);


}

Camera::~Camera()
{
	mCameraBuffer->Release();
}

void Camera::SetActive()
{
	mCameraConstants.c_viewProj = mWorldToCameraMatrix * mProjectionMatrix;
	mCameraConstants.c_cameraPosition = mWorldToCameraMatrix.GetTranslation() * -1;
	Graphics::Get()->UploadBuffer(mCameraBuffer, &mCameraConstants, sizeof(mCameraConstants));
	Graphics::Get()->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_CAMERA, 1, &mCameraBuffer);
	Graphics::Get()->GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_CAMERA, 1, &mCameraBuffer);
}
