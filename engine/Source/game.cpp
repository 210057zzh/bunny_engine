#include "stdafx.h"
#include "Game.h"
#include "engineMath.h"
#include "Graphics.h"
#include "Shader.h"
#include "jsonUtil.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include <fstream>
#include <sstream>

#include "assetManager.h"
#include "Camera.h"
#include "CollisionBox.h"
#include "Job.h"
#include "JobManager.h"
#include "Material.h"
#include "mesh.h"
#include "OffScreenRenderTarget.h"
#include "physics.h"
#include "Profiler.h"
#include "RenderCube.h"
#include "RenderObj.h"
#include "SkinnedObj.h"
#include "texture.h"
#include "VertexBuffer.h"
#include "VertexFormat.h"
#include "Components/Character.h"
#include "components/followCam.h"
#include "Components/player.h"
#include "Components/PointLight.h"
#include "Components/SimpleRotate.h"
#include "texture.h"
#include "Components/flyingLight.h"

/*static*/ Game* Game::s_game_ = nullptr;

Game::Game() : mAssetManager(new AssetManager()), mPhysics(new Physics()), mLightingConstants()
{
	DbgAssert(nullptr == s_game_, "You can only have 1 game");
	s_game_ = this;
}

Game::~Game()
= default;

void Game::LoadShaders()
{
	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalColorTexCoord, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalColorTexCoord, normal),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexPosNormalColorTexCoord, color),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosNormalColorTexCoord, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/BasicMesh.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"BasicMesh", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTexCoord, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTexCoord, normal),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosNormalTexCoord, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Phong.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Phong", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTexCoord, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTexCoord, normal),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosNormalTexCoord, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Unlit.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Unlit", shader);
	}


	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosColor, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexPosColor, color),
				D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Mesh.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Mesh", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexSkinned, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexSkinned, normal),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEINDICES", 0,  DXGI_FORMAT_R8G8B8A8_UINT, 0, offsetof(VertexSkinned, boneIndices),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0,   DXGI_FORMAT_R8G8B8A8_UNORM, 0, offsetof(VertexSkinned, boneWeights),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexSkinned, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Skinned.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Skinned", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTangentTexCoord, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTangentTexCoord, normal),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosNormalTangentTexCoord, tangent),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosNormalTangentTexCoord, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Normal.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Normal", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexCopy, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexCopy, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Lighting.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Lighting", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexCopy, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexCopy, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/Copy.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"Copy", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexCopy, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexCopy, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/BloomMask.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"BloomMask", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexCopy, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexCopy, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/BloomHorizontal.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"BloomHorizontal", shader);
	}

	{
		const D3D11_INPUT_ELEMENT_DESC inputElem[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexCopy, pos),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexCopy, texcoord),
				D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const auto shader = new Shader();
		shader->Load(L"Shaders/BloomVertical.hlsl", inputElem, static_cast<uint32_t>(std::size(inputElem)));
		mAssetManager->SetShader(L"BloomVertical", shader);
	}
}

void Game::LoadLights()
{
	ZeroMemory(&mLightingConstants, sizeof(mLightingConstants));

	mLightsConstantsBuffer = Graphics::Get()->CreateGraphicsBuffer(nullptr, sizeof(mLightingConstants),
		D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE,
		D3D11_USAGE_DYNAMIC);
}

void Game::Init(HWND hWnd, float width, float height)
{
	mGraphics.InitD3D(hWnd, width, height);

	LoadShaders();
	LoadLights();

	LoadLevel(L"Assets/Levels/Final.itplevel");

	m_diffuseRenderTarget = new OffScreenRenderTarget(static_cast<int>(width), static_cast<int>(height), DXGI_FORMAT_R32G32B32A32_FLOAT, true);
	m_normalRenderTarget = new OffScreenRenderTarget(static_cast<int>(width), static_cast<int>(height), DXGI_FORMAT_R32G32B32A32_FLOAT, true);
	m_worldPosRenderTarget = new OffScreenRenderTarget(static_cast<int>(width), static_cast<int>(height), DXGI_FORMAT_R32G32B32A32_FLOAT, true);

	fullSizeRenderTarget = new OffScreenRenderTarget(static_cast<int>(width), static_cast<int>(height), DXGI_FORMAT_R32G32B32A32_FLOAT, true);
	halfSizeRenderTarget = new OffScreenRenderTarget(static_cast<int>(width * 0.5f), static_cast<int>(height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT);
	for (size_t i = 0; i < std::size(quaterSizeRenderTarget); i++)
	{
		quaterSizeRenderTarget[i] = new OffScreenRenderTarget(static_cast<int>(width * 0.25f), static_cast<int>(height * 0.25f), DXGI_FORMAT_R32G32B32A32_FLOAT);
	}
	{
		m_blend_state_[0] = mGraphics.CreateBlendState(false, D3D11_BLEND_ONE, D3D11_BLEND_ZERO);
		m_blend_state_[1] = mGraphics.CreateBlendState(true, D3D11_BLEND_ONE, D3D11_BLEND_ONE);
	}
}

void Game::Shutdown()
{

	for (const auto object : mRenderObjects)
	{
		delete object;
	}
	mRenderObjects.clear();


	delete mCamera;
	delete fullSizeRenderTarget;
	delete halfSizeRenderTarget;
	for (size_t i = 0; i < std::size(quaterSizeRenderTarget); i++)
	{
		delete quaterSizeRenderTarget[i];
	}

	delete m_diffuseRenderTarget;
	delete m_normalRenderTarget;
	delete m_worldPosRenderTarget;
	for (size_t i = 0; i < std::size(m_blend_state_); i++)
	{
		m_blend_state_[i]->Release();
	}
	mLightsConstantsBuffer->Release();
	mAssetManager->Clear();
	delete mAssetManager;
	delete mPhysics;

	mGraphics.CleanD3D();
}

void Game::Update(float deltaTime)
{
	PROFILE_SCOPE(GameUpdate);
	for (const auto obj : mRenderObjects)
	{
		obj->Update(deltaTime);
	}
	JobManager::Get().WaitForJobs();
}

void Game::Process(const VertexBuffer& screen, const Shader* shader, const OffScreenRenderTarget* input, const OffScreenRenderTarget* output)
{
	shader->SetActive();
	Graphics::Get()->UnbindActiveTexture();
	Graphics::Get()->UnbindActiveRenderTarget();
	input->SetAsInput(Graphics::TEXTURE_SLOT_DIFFUSE);
	output->SetActiveRenderTarget();
	screen.Draw();
}

void Game::RenderFrame()
{
	PROFILE_SCOPE(GameRenderFrame);

	ID3D11RenderTargetView* renderTargets[3] = { m_diffuseRenderTarget->MScreenTextureRenderView(), m_normalRenderTarget->MScreenTextureRenderView(), m_worldPosRenderTarget->MScreenTextureRenderView() };

	{
		mGraphics.SetBlendState(m_blend_state_[0]);
		mGraphics.UnbindActiveTexture();

		mGraphics.GetDeviceContext()->OMSetRenderTargets(3, renderTargets, mGraphics.GetDepthView());
	}

	{
		const Graphics::Color4 clearColor(0.0f, 0.2f, 0.4f, 0.0f);
		mGraphics.GetDeviceContext()->ClearRenderTargetView(m_diffuseRenderTarget->MScreenTextureRenderView(), reinterpret_cast<const float*>(&clearColor));
		mGraphics.GetDeviceContext()->ClearRenderTargetView(m_normalRenderTarget->MScreenTextureRenderView(), reinterpret_cast<const float*>(&Vector4::Zero));
		mGraphics.GetDeviceContext()->ClearRenderTargetView(m_worldPosRenderTarget->MScreenTextureRenderView(), reinterpret_cast<const float*>(&Vector4::Zero));
		mGraphics.ClearDepthBuffer(mGraphics.GetDepthView(), 1.0f);
	}

	{
		mCamera->SetActive();
	}

	{
		Graphics::Get()->UploadBuffer(mLightsConstantsBuffer,
			&mLightingConstants,
			sizeof(mLightingConstants));
		Graphics::Get()->GetDeviceContext()->PSSetConstantBuffers(
			Graphics::CONSTANT_BUFFER_LIGHTS,
			1,
			&mLightsConstantsBuffer);
	}

	{
		for (const auto object : mRenderObjects)
		{
			object->Draw();
		}
	}

	{
		const VertexCopy vertices[4] =
		{
			{ Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f) },
			{ Vector3(1.0f, -1.0f, 0.0f), Vector2(1.0f, 1.0f) },
			{ Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f) },
			{ Vector3(-1.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f) }

		};
		const uint16_t indices[6] =
		{
			0,1,2,0,2,3
		};

		const VertexBuffer screen = VertexBuffer(
			vertices, std::size(vertices), sizeof(vertices[0]),
			indices, std::size(indices), sizeof(indices[0]));

		{
			const auto lightingShader = mAssetManager->GetShader(L"Lighting");

			fullSizeRenderTarget->SetActiveRenderTarget();
			lightingShader->SetActive();
			m_diffuseRenderTarget->SetAsInput(Graphics::TEXTURE_SLOT_DIFFUSE);
			m_normalRenderTarget->SetAsInput(Graphics::TEXTURE_SLOT_NORMAL);
			m_worldPosRenderTarget->SetAsInput(Graphics::TEXTURE_SLOT_WORLDPOS);
			screen.Draw();
		}

		{
			const auto copyShader = mAssetManager->GetShader(L"Copy");
			const auto bloomMask = mAssetManager->GetShader(L"BloomMask");
			const auto bloomVertical = mAssetManager->GetShader(L"BloomVertical");
			const auto bloomHorizontal = mAssetManager->GetShader(L"BloomHorizontal");


			Process(screen, bloomMask, fullSizeRenderTarget, halfSizeRenderTarget);
			Process(screen, copyShader, halfSizeRenderTarget, quaterSizeRenderTarget[0]);
			Process(screen, bloomVertical, quaterSizeRenderTarget[0], quaterSizeRenderTarget[1]);
			Process(screen, bloomHorizontal, quaterSizeRenderTarget[1], quaterSizeRenderTarget[0]);

			mGraphics.SetBlendState(m_blend_state_[1]);
			Process(screen, copyShader, quaterSizeRenderTarget[0], fullSizeRenderTarget);

			mGraphics.SetBlendState(m_blend_state_[0]);
			mGraphics.UnbindActiveRenderTarget();
			mGraphics.UnbindActiveTexture();
			mGraphics.SetRenderTarget(mGraphics.GetBackBuffer(), nullptr);
			mGraphics.SetViewport(0.0f, 0.0f, mGraphics.GetScreenWidth(), mGraphics.GetScreenHeight());
			copyShader->SetActive();
			fullSizeRenderTarget->SetAsInput(Graphics::TEXTURE_SLOT_DIFFUSE);
			screen.Draw();
		}

	}

	{
		PROFILE_SCOPE(EndFrame);
		mGraphics.EndFrame();
	}
}

void Game::OnKeyDown(uint32_t key)
{
	m_keyIsHeld[key] = true;
}

void Game::OnKeyUp(uint32_t key)
{
	m_keyIsHeld[key] = false;
}

bool Game::IsKeyHeld(uint32_t key) const
{
	const auto find = m_keyIsHeld.find(key);
	if (find != m_keyIsHeld.end())
		return find->second;
	return false;
}

bool Game::LoadLevel(const WCHAR* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itplevel" ||
		ver != 2)
	{
		return false;
	}

	{
		mCamera = new Camera();
		const auto& cameraData = doc["camera"];

		Vector3 v;
		Quaternion q;

		if (!GetVectorFromJSON(cameraData, "position", v))
		{
			return false;
		}

		if (!GetQuaternionFromJSON(cameraData, "rotation", q))
		{
			return false;
		}

		mCamera->mWorldToCameraMatrix =
			Matrix4::CreateFromQuaternion(q) *
			Matrix4::CreateTranslation(v);
		mCamera->mWorldToCameraMatrix.Invert();
	}

	{
		const auto& lightingData = doc["lightingData"];

		Vector3 v;
		if (!GetVectorFromJSON(lightingData, "ambient", v))
		{
			return false;
		}
		SetAmbientLight(v);
	}

	{
		const auto& objects = doc["renderObjects"];
		if (!objects.IsArray())
		{
			return false;
		}
		for (rapidjson::SizeType i = 0; i < objects.Size(); i++)
		{
			const auto& obj = objects[i];

			Vector3 pos;
			Quaternion rot;
			float scale;
			std::wstring meshName;

			if (!GetVectorFromJSON(obj, "position", pos) ||
				!GetQuaternionFromJSON(obj, "rotation", rot) ||
				!GetFloatFromJSON(obj, "scale", scale) ||
				!GetWStringFromJSON(obj, "mesh", meshName))
			{
				return false;
			}

			auto mesh = mAssetManager->LoadMesh(meshName);

			auto renderObj = mesh->IsSkinned() ? new SkinnedObj(mesh) : new RenderObj(mesh);
			renderObj->mPerObjectConstants.c_modelToWorld =
				Matrix4::CreateScale(scale) *
				Matrix4::CreateFromQuaternion(rot) *
				Matrix4::CreateTranslation(pos);

			mRenderObjects.emplace_back(renderObj);

			const auto& components = obj["components"];

			for (rapidjson::SizeType i = 0; i < components.Size(); i++)
			{
				const auto& component = components[i];
				if (strcmp(component["type"].GetString(), "PointLight") == 0)
				{
					auto light = new PointLight(this, renderObj);
					light->LoadProperties(component);
					renderObj->AddComponent(light);
				}
				else if (strcmp(component["type"].GetString(), "Character") == 0)
				{
					auto character = new Character(this, dynamic_cast<SkinnedObj*>(renderObj));
					character->LoadProperties(component);
					renderObj->AddComponent(character);
				}
				else if (strcmp(component["type"].GetString(), "Player") == 0)
				{
					auto player = new Player(this, dynamic_cast<SkinnedObj*>(renderObj));
					player->LoadProperties(component);
					renderObj->AddComponent(player);
				}
				else if (strcmp(component["type"].GetString(), "FollowCam") == 0)
				{
					auto cam = new FollowCam(this, dynamic_cast<SkinnedObj*>(renderObj));
					cam->LoadProperties(component);
					renderObj->AddComponent(cam);
				}
				else if (strcmp(component["type"].GetString(), "CollisionBox") == 0)
				{
					auto box = new CollisionBox(renderObj, mPhysics);
					box->LoadProperties(component);
					renderObj->AddComponent(box);
				}
				else if (strcmp(component["type"].GetString(), "SimpleRotate") == 0)
				{
					auto rot = new SimpleRotate(renderObj);
					rot->LoadProperties(component);
					renderObj->AddComponent(rot);
				}
				else if (strcmp(component["type"].GetString(), "FlyingLight") == 0)
				{
					auto cam = new FlyingLight(renderObj, this);
					cam->LoadProperties(component, mAssetManager);
					renderObj->AddComponent(cam);
				}
			}
		}
	}


	return true;
}

Lights::PointLightData* Game::AllocateLight()
{
	for (int i = 0; i < Lights::MAX_POINT_LIGHTS; i++)
	{
		if (!mLightingConstants.c_pointLight[i].isEnabled)
		{
			mLightingConstants.c_pointLight[i].isEnabled = true;
			return mLightingConstants.c_pointLight + i;
		}
	}
	return nullptr;

}

void Game::FreeLight(Lights::PointLightData* pLight)
{
	pLight->isEnabled = false;
}

void Game::SetAmbientLight(const Vector3& color)
{
	mLightingConstants.c_ambient = color;
}

const Vector3& Game::GetAmbientLight() const
{
	return mLightingConstants.c_ambient;
}
