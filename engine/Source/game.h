#pragma once
#include "Graphics.h"
#include "Lights.h"
#include <memory>


class OffScreenRenderTarget;
class Physics;
class Mesh;
class AssetManager;
class Material;
class Texture;
class Camera;
class RenderObj;
class VertexBuffer;
class Shader;

class Game
{
public:
	Game();
	~Game();
	void LoadShaders();
	void LoadLights();

	static Game* Get() { return s_game_; }

	void Init(HWND hWnd, float width, float height);
	void Shutdown();
	void Update(float deltaTime);
	static void Process(const VertexBuffer& screen, const Shader* shader, const OffScreenRenderTarget* input, const OffScreenRenderTarget* output);
	void RenderFrame();

	void OnKeyDown(uint32_t key);
	void OnKeyUp(uint32_t key);
	bool IsKeyHeld(uint32_t key) const;

	Lights::PointLightData* AllocateLight();
	void FreeLight(Lights::PointLightData* pLight);
	void SetAmbientLight(const Vector3& color);
	const Vector3& GetAmbientLight() const;

	AssetManager* mAssetManager = nullptr;
	Camera* mCamera{};
	Physics* mPhysics{};


private:
	std::unordered_map<uint32_t, bool> m_keyIsHeld;
	Graphics mGraphics;

	static Game* s_game_;

	std::vector<RenderObj*> mRenderObjects;

	Lights::LightingConstants mLightingConstants;
	ID3D11Buffer* mLightsConstantsBuffer = nullptr;

	bool LoadLevel(const WCHAR* fileName);
	OffScreenRenderTarget* m_diffuseRenderTarget;
	OffScreenRenderTarget* m_normalRenderTarget;
	OffScreenRenderTarget* m_worldPosRenderTarget;

	OffScreenRenderTarget* fullSizeRenderTarget;
	OffScreenRenderTarget* halfSizeRenderTarget;
	OffScreenRenderTarget* quaterSizeRenderTarget[2];

	ID3D11BlendState* m_blend_state_[2];
};