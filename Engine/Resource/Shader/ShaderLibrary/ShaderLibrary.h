#pragma once
#include "ShaderKey.h"


class ShaderContext;


class ShaderLibrary
{
public:

	struct ImportKey;
	struct GetDataKey;

	ShaderLibrary(ImportKey importKey_);

	void ImportMeshShaderData
	(
		ImportKey key_,
		Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
		ShaderKey::MeshType meshType_,
		ShaderKey::Renderpath renderPath_
	);

	void ImportPixelShaderData
	(
		ImportKey key_,
		Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
		ShaderKey::MaterialType materialType_,
		ShaderKey::Renderpath renderPath_
	);

	IDxcBlob* GetMeshShaderData
	(
		GetDataKey key_,
		ShaderKey::MeshType meshType_,
		ShaderKey::Renderpath renderPath_
	);

	IDxcBlob* GetPixelShaderData
	(
		GetDataKey key_,
		ShaderKey::MaterialType materialType_,
		ShaderKey::Renderpath renderPath_
	);


private:
	Microsoft::WRL::ComPtr<IDxcBlob> meshShaderData[(int)ShaderKey::MeshType::kCount][(int)ShaderKey::Renderpath::kCount];
	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderData[(int)ShaderKey::MaterialType::kCount][(int)ShaderKey::Renderpath::kCount];

};


struct ShaderLibrary::ImportKey
{
private:

	friend class ShaderContext;
	explicit ImportKey() = default;
};

struct ShaderLibrary::GetDataKey
{
private:

	explicit GetDataKey() = default;
};


