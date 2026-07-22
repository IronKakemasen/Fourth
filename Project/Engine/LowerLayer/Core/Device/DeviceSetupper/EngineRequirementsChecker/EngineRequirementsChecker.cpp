#include "PreCompileHeader.h"
#include "EngineRequirementsChecker.h"

namespace
{
	auto const fileName = "EngineRequiementsChecker.cpp";
}


void DeviceContext::Setupper::EngineRequiementsChecker::ShaderModelChack(ID3D12Device8* device_ , D3D_SHADER_MODEL shaderModel_)
{
	D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = { shaderModel_ };

	HRESULT hr = device_->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel));

	bool positiveResult = (SUCCEEDED(hr)) * (shaderModel.HighestShaderModel >= shaderModel_);
	ErrorMessageOutput::Abort::DetectError
	(
		positiveResult,
		"ShaderModelが必要値に対応していない",
		fileName
	);

	Logger::Log("ShaderModel Maximum Checked");
}

void DeviceContext::Setupper::EngineRequiementsChecker::IsMeshShaderSupported(ID3D12Device8* device_)
{
	//メッシュシェーダがサポートされているかどうか
	D3D12_FEATURE_DATA_D3D12_OPTIONS7 features = {};

	HRESULT hr = device_->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &features, sizeof(features));

	bool positiveResult = (SUCCEEDED(hr)) * (features.MeshShaderTier != D3D12_MESH_SHADER_TIER_NOT_SUPPORTED);
	ErrorMessageOutput::Abort::DetectError
	(
		positiveResult,
		"MeshShaderがサポートされていません。",
		fileName
	);
	Logger::Log("MeshShader is Supported");

}

void DeviceContext::Setupper::EngineRequiementsChecker::ResourceBindingTierCheck(ID3D12Device8* device_)
{
	//メッシュシェーダがサポートされているかどうか
	D3D12_FEATURE_DATA_D3D12_OPTIONS features = {};

	HRESULT hr = device_->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &features, sizeof(features));

	bool positiveResult = (SUCCEEDED(hr)) * (features.ResourceBindingTier >= D3D12_RESOURCE_BINDING_TIER_3);
	ErrorMessageOutput::Abort::DetectError
	(
		positiveResult,
		"RESOURCE_BINDING_TIERが3以上じゃない",
		fileName
	);
	Logger::Log("RESOURCE_BINDING_TIER is 3 or more");
}
