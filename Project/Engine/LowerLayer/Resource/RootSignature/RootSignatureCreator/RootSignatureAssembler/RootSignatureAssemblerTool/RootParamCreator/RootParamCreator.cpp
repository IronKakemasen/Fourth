#include "RootParamCreator.h"
#include "../../../../../../../../Assets/Shared/ConstantBuffers.h"

std::vector<D3D12_ROOT_PARAMETER> RootSignatureContext::Assembler::RootParamCreator::CreateRootparamGloballyCommonCBV(const RootSignatureDesc::Graphics& srcDesc_)
{
	std::vector<D3D12_ROOT_PARAMETER> rootParams = {};
	rootParams.resize(size_t(ConstantBuffers::BindSlot::kCount));

	int i = 0;
	for (auto& rootparam : rootParams)
	{
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootparam.ShaderVisibility = RootSignatureLayoutComponent::Convert(RootSignatureLayoutComponent::ShaderStage::kAll);
		rootparam.Descriptor.ShaderRegister = i;
		++i;
	}

	return rootParams;
}


