#pragma once

class Nexus;

class RootSignatureContext
{
protected:

	using CommandCreateRootSignature = std::function<void(UINT nodeMask_, Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_, ID3D12RootSignature** doublePtr_rootSignature_)>;


public:

	struct InstanceKey;

	RootSignatureContext(InstanceKey key_, CommandCreateRootSignature cmdCreateRootSignature_);
	~RootSignatureContext();

private:

	//rootSignatureを組み立てる
	class Assembler;

	std::unique_ptr<Assembler> assembler;
	
};

struct RootSignatureContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};

