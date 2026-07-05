#pragma once
#include "../RootSignatureContext.h"
#include "RootSignatureDesc.h"



class RootSignatureContext::Assembler
{
public:
	Assembler(RootSignatureContext::InstanceKey key_, RootSignatureContext::CommandCreateRootSignature cmd_);
	~Assembler();

	//生成関数
	template<typename DescType>
	Microsoft::WRL::ComPtr<ID3D12RootSignature> Create(const DescType& descType_);

private:

	RootSignatureContext::CommandCreateRootSignature cmdCreaterootSignature;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> CreateRootSignature(D3D12_ROOT_SIGNATURE_DESC* desc_);
};


template<>
Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignatureContext::Assembler::Create(const RootSignatureDesc::Graphics& srcDesc_);
