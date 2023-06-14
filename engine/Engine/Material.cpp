#include "stdafx.h"
#include "Material.h"

#include <rapidjson/include/rapidjson/document.h>
#include <rapidjson/include/rapidjson/rapidjson.h>

#include "assetManager.h"
#include "jsonUtil.h"
#include "Shader.h"
#include "texture.h"
#include "stringUtil.h"

Material::Material()
	: m_material_constants(),
	mMaterialConstantsBuffer(Graphics::Get()->CreateGraphicsBuffer(nullptr, sizeof(m_material_constants),
		D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE,
		D3D11_USAGE_DYNAMIC))
{
}

Material::~Material()
{
	mMaterialConstantsBuffer->Release();
}

Material* Material::StaticLoad(const WCHAR* fileName, AssetManager* pManager)
{
	Material* material = new Material();
	if (false == material->Load(fileName, pManager))
	{
		delete material;
		return new Material();
	}
	return material;
}

bool Material::Load(const WCHAR* fileName, AssetManager* pAssetManager)
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
		DbgAssert(false, "Unable to open Mesh file");
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	std::wstring buffer;
	GetWStringFromJSON(doc, "shader", buffer);
	SetShader(pAssetManager->GetShader(buffer));

	const auto& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		DbgAssert(false, "Material File Invalid texture list");
		return false;
	}


	for (rapidjson::SizeType i = 0; i < textures.Size() && i < Graphics::TEXTURE_SLOT_TOTAL; i++)
	{
		StringUtil::String2WString(buffer, textures[i].GetString());
		SetTexture(i, pAssetManager->LoadTexture(buffer));
	}

	{
		Vector3 v;
		if (GetVectorFromJSON(doc, "diffuseColor", v))
		{
			SetDiffuseColor(v);
		}
		if (GetVectorFromJSON(doc, "specularColor", v))
		{
			SetSpecularColor(v);
		}
	}
	{
		float f;
		if (GetFloatFromJSON(doc, "specularPower", f))
		{
			SetSpecularPower(f);
		}
	}

	return true;
}

void Material::SetActive()
{
	if (mShader)
	{
		mShader->SetActive();
	}
	for (int i = 0; i < Graphics::TEXTURE_SLOT_TOTAL; i++)
	{
		if (mTextures[i])
		{
			mTextures[i]->SetActive(i);
		}
	}
	Graphics::Get()->UploadBuffer(mMaterialConstantsBuffer, &m_material_constants, sizeof(m_material_constants));
	Graphics::Get()->GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_MATERIAL, 1, &mMaterialConstantsBuffer);
}

void Material::SetShader(const Shader* shader)
{
	mShader = shader;
}

void Material::SetTexture(int slot, const Texture* texture)
{
	mTextures[slot] = texture;
}

void Material::SetDiffuseColor(const Vector3& color)
{
	m_material_constants.diffuseColor = color;
}

void Material::SetSpecularColor(const Vector3& color)
{
	m_material_constants.specularColor = color;
}

void Material::SetSpecularPower(float power)
{
	m_material_constants.specularPower = power;
}

