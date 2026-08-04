#pragma once
#include "../RootSignatureContext.h"
#include "RootSignatureAssembler/RootSignatureDesc.h"

class RootSignatureContext::RootSignatureCreator
{
public:

	RootSignatureCreator
	(
		NexusFieldProof proof_,
		std::unique_ptr<Assembler>&& assembler_,
		RootSignatureLibrary* library_
	);

	template<typename DescType>
	ID3D12RootSignature* Create(const DescType& desc_);



private:

	std::unique_ptr<Assembler> assembler;
	RootSignatureLibrary* library;
};


template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureCreator::Create(const RootSignatureDesc::Graphics& desc_);




//
//RootSignatureDesc::Graphics srcGraphicsDesc;
////コンスタントバッファの種類を計測
//srcGraphicsDesc.numConstantBuffers_ = kNumConstantBufferTypes;
//
/////カラーテクスチャなど一般
//srcGraphicsDesc.pair_shaderStageSamplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState::kLinearWrap);
//Logger::Log("SamplerSlot0: kLinearWrap", fileName);
/////法線テクスチャなど
//srcGraphicsDesc.pair_shaderStageSamplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState::kAnisotropicWrap);
//Logger::Log("SamplerSlot1: kAnisotropicWrap", fileName);
//
/////輝度テクスチャなど
//srcGraphicsDesc.pair_shaderStageSamplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState::kPointWrap);
//Logger::Log("SamplerSlot2: kPointWrap", fileName);
//
//
//data.at((int)Usage::kGraphics) = assembler_->Assemble(srcGraphicsDesc);
