#include "RootParamCreator.h"
#include "../../../../../../../../Assets/Shared/ConstantBuffers.h"

using namespace RootSignatureLayoutComponent;

std::vector<D3D12_ROOT_PARAMETER> RootSignatureContext::Assembler::RootParamCreator::CreateRootparamGloballyCommonCBV(const RootSignatureDesc::Graphics& srcDesc_)
{
	std::vector<D3D12_ROOT_PARAMETER> rootParams = {};
	rootParams.resize(size_t(ConstantBuffers::RootConstantsBindSlots::kCount));

	//こっちは定数バッファ
	int i = 0;
	for (;i < (int)ConstantBuffers::ConstantBufferBindSlots::kCount;++i)
	{
		rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParams[i].ShaderVisibility = Convert(ShaderStage::kAll);
		rootParams[i].Descriptor.ShaderRegister = i	;
	}

	//こっちはルートコンスタンツ
	for (;i < (int)ConstantBuffers::RootConstantsBindSlots::kCount;++i)
	{
		switch (i)
		{
		case (int)ConstantBuffers::RootConstantsBindSlots::kPerDrawIndices:

			rootParams[i].ShaderVisibility = Convert(ShaderStage::kAll);

			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
			rootParams[i].Constants.ShaderRegister = i;
			rootParams[i].Constants.RegisterSpace = 0;
			rootParams[i].Constants.Num32BitValues = 2;

			break;

		case (int)ConstantBuffers::RootConstantsBindSlots::kPassBufferIndexRange:

			rootParams[i].ShaderVisibility = Convert(ShaderStage::kAll);

			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
			rootParams[i].Constants.ShaderRegister = i;
			rootParams[i].Constants.RegisterSpace = 0;
			rootParams[i].Constants.Num32BitValues = 2;

			break;

		default:

			ErrorMessageOutput::Assert::OutputError
			(
				"ここに到達するのはおかしい。ルート定数の設定が足りてないっしょ",
				"RootParamCreator.cpp"
			);

			break;
		}
	}


	return rootParams;
}


