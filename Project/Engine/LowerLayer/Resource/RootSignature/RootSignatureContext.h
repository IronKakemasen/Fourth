#pragma once

class Nexus;
class DeviceContextDiplomat;
class RootSignatureContextDiplomat;

class RootSignatureContext
{

public:

	enum class PsoType
	{
		kGraphics,
		kCompute
		, kCount
	};

	class RootSignatureCreator;
	class ToolLender;
	class CmdProvider;

	struct NexusFieldProof;
	struct CmdProviderKey;

	RootSignatureContext(NexusFieldProof proof_, DeviceContextDiplomat& deviceContextDiplomat_);
	~RootSignatureContext();
	auto& AccessDiplomat() { return *diplomat; }



private:

	class RootSignatureLibrary;
	//rootSignatureを組み立てる
	class Assembler;

	std::unique_ptr<RootSignatureCreator> rootSignatureCreator;
	std::unique_ptr<RootSignatureLibrary> rootSignatureLibrary;
	std::unique_ptr<RootSignatureContextDiplomat> diplomat;

};

struct RootSignatureContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};


struct RootSignatureContext::CmdProviderKey
{
private:

	friend class CmdProvider;
	explicit CmdProviderKey() = default;
};

