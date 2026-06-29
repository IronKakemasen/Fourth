#include "PreCompileHeader.h"
#include "ShaderLibrary.h"


ShaderLibrary::ShaderLibrary(ImportKey importKey_)
{

}


void ShaderLibrary::ImportMeshShaderData
(
	ImportKey key_,
	Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
	ShaderKey::MeshType meshType_,
	ShaderKey::Renderpath renderPath_
)
{
	meshShaderData[(int)meshType_][(int)renderPath_] = std::move(data_);
}

void ShaderLibrary::ImportPixelShaderData
(
	ImportKey key_,
	Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
	ShaderKey::MaterialType materialType_,
	ShaderKey::Renderpath renderPath_
)
{
	pixelShaderData[(int)materialType_][(int)renderPath_] = std::move(data_);
}


IDxcBlob* ShaderLibrary::GetMeshShaderData
(
	GetDataKey key_,
	ShaderKey::MeshType meshType_,
	ShaderKey::Renderpath renderPath_
)
{
	return meshShaderData[(int)meshType_][(int)renderPath_].Get();
}

IDxcBlob* ShaderLibrary::GetPixelShaderData
(
	GetDataKey key_,
	ShaderKey::MaterialType materialType_,
	ShaderKey::Renderpath renderPath_
)
{
	return pixelShaderData[(int)materialType_][(int)renderPath_].Get();
}

