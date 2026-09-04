#pragma once

class Nexus;
class DeviceContextDiplomat;
class PSO_ContextDiplomat;

class PSO_Context
{
	//PSOを構築するもの
	class Assembler;
	//PSOのユニークを所持するだけ
	class PSO_Container;

public:

	class PSO_Creator;
	class ToolLender;

	//自身のインスタンスキー
	struct NexusFieldProof;

	PSO_Context
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_
	);

	~PSO_Context();

	std::unique_ptr<PSO_ContextDiplomat> diplomat;

private:

	std::unique_ptr<PSO_Creator> psoCreator;
	std::unique_ptr<PSO_Container> psoContainer;

};


struct PSO_Context::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};
