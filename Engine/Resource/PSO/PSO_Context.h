#pragma once

class Nexus;
class ShaderContext;

class PSO_Context
{

public:

	//PSOを構築するもの
	class Assembler;

	//自身のインスタンスキー
	struct InstanceKey;

	PSO_Context(InstanceKey key_, ShaderContext& shaderContext_);
	~PSO_Context();


private:

	std::unique_ptr<Assembler> assembler;


	void InstantiatePSO_Assembler(InstanceKey key_, ShaderContext& shaderContext_);
};


struct PSO_Context::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
