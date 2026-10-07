#include "RootParamCreator.h"


//外部
#include "../../../../../../../../Assets/Shared/ConstantBuffers.h"

using namespace RootSignatureLayoutComponent;
using namespace ConstantBuffers;

std::vector<D3D12_ROOT_PARAMETER> RootSignatureContext::Assembler::RootParamCreator::CreateRootparamGloballyCommonCBV(const RootSignatureDesc::Graphics& srcDesc_)
{
	std::vector<D3D12_ROOT_PARAMETER> rootParams = {};
	rootParams.resize(size_t(RootConstantsBindSlots::kCount));

	//こっちは定数バッファ
	int i = 0;
	for (;i < (int)ConstantBufferBindSlots::kCount;++i)
	{
		rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParams[i].ShaderVisibility = Convert(ShaderStage::kAll);
		rootParams[i].Descriptor.ShaderRegister = i	;
	}

	//こっちはルートコンスタンツ
	for (;i < (int)RootConstantsBindSlots::kCount;++i)
	{
		rootParams[i].Constants.Num32BitValues = Num32BitValuesTable(RootConstantsBindSlots(i));
		rootParams[i].ShaderVisibility = Convert(ShaderStage::kAll);
		rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
		rootParams[i].Constants.ShaderRegister = i;
		rootParams[i].Constants.RegisterSpace = 0;
	}


	return rootParams;
}


