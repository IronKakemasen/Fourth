#pragma once

class Nexus;
class RootSignatureLibrary;


class RootSignatureContext
{
protected:

	using CommandCreateRootSignature = std::function<void(UINT nodeMask_, Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_, ID3D12RootSignature** doublePtr_rootSignature_)>;


public:

	//rootSignatureを組み立てる
	class Assembler;
	struct InstanceKey;

	RootSignatureContext(InstanceKey key_, CommandCreateRootSignature cmdCreateRootSignature_);
	~RootSignatureContext();

private:

	std::unique_ptr<Assembler> assembler;
	std::unique_ptr<RootSignatureLibrary> rootSignatureLibrary;

};

struct RootSignatureContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};

