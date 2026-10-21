#pragma once
#include "../DeviceContextSetupper.h"


class DeviceContext::Setupper::EngineRequirementsChecker
{
private:

	friend class DeviceContext::Setupper;

	static void ShaderModelCheck(ID3D12Device8* device_ , D3D_SHADER_MODEL shaderModel_);
	static void IsMeshShaderSupported(ID3D12Device8* device_);
	static void ResourceBindingTierCheck(ID3D12Device8* device_);

};

