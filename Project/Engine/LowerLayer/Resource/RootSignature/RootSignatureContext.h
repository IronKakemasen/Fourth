#pragma once

class Nexus;
class DeviceContextDiplomat;
class RootSignatureContextDiplomat;

class RootSignatureContext
{
protected:

	using CommandCreateRootSignature = std::function<void(UINT nodeMask_, Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_, ID3D12RootSignature** doublePtr_rootSignature_)>;


public:

	enum class Usage
	{
		kGraphics,
		kCompute
		, kCount
	};

	class RootSignatureCreator;
	class ToolLender;

	struct NexusFieldProof;

	RootSignatureContext(NexusFieldProof proof_, DeviceContextDiplomat* deviceContextDiplomat_);
	~RootSignatureContext();


	std::unique_ptr<RootSignatureContextDiplomat> diplomat;

private:

	class RootSignatureLibrary;
	//rootSignatureを組み立てる
	class Assembler;

	std::unique_ptr<RootSignatureCreator> rootSignatureCreator;
	std::unique_ptr<RootSignatureLibrary> rootSignatureLibrary;

};

struct RootSignatureContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

