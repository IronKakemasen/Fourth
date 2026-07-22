#include "RootSignatureLibrary.h"
//ツール
#include "../RootSignatureAssembler/RootSignatureAssembler.h"

//共有ヘッダ
#include "../../../../Assets/Shared/ConstantBuffers.h"

using namespace RootSignatureLayoutComponent;

namespace
{
	auto const fileName = "RootSignatureLibrary.cpp";

}


RootSignatureLibrary::RootSignatureLibrary(InstanceKey key_, RootSignatureContext::Assembler* assembler_)
{
    Logger::Entry("RootSignatureLibrary: Constructor");


    CreateAllRootSignatures(assembler_);


    Logger::End("RootSignatureLibrary: Constructor");

}

RootSignatureLibrary::~RootSignatureLibrary()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///シェーダーバイナリオブジェのポインタを渡す
ID3D12RootSignature* RootSignatureLibrary::Export(DataPtrAccesskey key_, Usage usage_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((int)usage_), "中身が空です", fileName);

	return data.at((int)usage_).Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RootSignatureLibrary::CreateAllRootSignatures(RootSignatureContext::Assembler* assembler_)
{
    ///グラフィックス用
    {
        RootSignatureDesc::Graphics srcGraphicsDesc;
        //コンスタントバッファの種類を計測
        srcGraphicsDesc.numConstantBuffers_ = kNumConstantBufferTypes;

        ///カラーテクスチャなど一般
        srcGraphicsDesc.pair_shaderStageSamplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState::kLinearWrap);
        Logger::Log("SamplerSlot0: kLinearWrap", fileName);
        ///法線テクスチャなど
        srcGraphicsDesc.pair_shaderStageSamplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState::kAnisotropicWrap);
        Logger::Log("SamplerSlot1: kAnisotropicWrap", fileName);

        ///輝度テクスチャなど
        srcGraphicsDesc.pair_shaderStageSamplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState::kPointWrap);
        Logger::Log("SamplerSlot2: kPointWrap", fileName);


        data.at((int)Usage::kGraphics) = assembler_->Assemble(srcGraphicsDesc);
    }

}

