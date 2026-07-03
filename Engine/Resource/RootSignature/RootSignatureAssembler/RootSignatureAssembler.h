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
	Microsoft::WRL::ComPtr<ID3D12RootSignature> Create(DescType descType_);

private:


	RootSignatureContext::CommandCreateRootSignature cmdCreaterootSignature;
};


template<>
Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignatureContext::Assembler::Create(const RootSignatureDesc::Graphics& srcDesc_);
