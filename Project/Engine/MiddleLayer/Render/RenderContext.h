#pragma once

class Nexus;
class BufferContextDiplomat;
class RootSignatureContextDiplomat;
class ModelContextDiplomat;
class PSO_ContextDiplomat;
class ShaderContextDiplomat;
class SwapChainContextDiplomat;
class RenderContextDiplomat;


class RenderContext
{
	class RenderPassContainer;
	class RenderPathContainer;
	class RenderPathAssembler;
	//PassDescから必要な情報だけまとめたもの
	struct RuntimePassInfo;
	//そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo;
	struct RenderPassState;
	//レンダーパス(Path)を設計し、描画コマンドを叩く強者
	class StaticRenderGraph;

public:
	//renderPass生成機
	class RenderPassCreator;
	//描画構成Passのビヘイビア
	class PassBehavior;
	//パスを作成するために必要
	struct PassDesc;
	class PathBehavior;
	//グラフィックス専用のpsoのプール、ランタイムでの配布
	class PSO_PoolDispatcher;
	//代行者
	class ExecutionAgent;

	//ネクサスフィールドの証
	struct NexusFieldProof;
	//代行者キー
	struct AgentKey;


	RenderContext
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_,
		RootSignatureContextDiplomat& rootSignatureContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_,
		PSO_ContextDiplomat& pso_ContextDiplomat_,
		ShaderContextDiplomat& shaderContextDiplomat_
	);

	~RenderContext();

	auto& AccessDiplomat() { return *diplomat; };

private:

	std::unique_ptr<RenderPassContainer> renderPassContainer;
	std::unique_ptr<RenderPathContainer> renderPathContainer;
	std::unique_ptr<StaticRenderGraph> staticRenderGraph;
	std::unique_ptr<PSO_PoolDispatcher> pso_PoolDispatcher;
	std::unique_ptr<RenderContextDiplomat> diplomat;

};


struct RenderContext::NexusFieldProof
{
private:
	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct RenderContext::AgentKey
{
private:
	friend class ExecutionAgent;
	explicit AgentKey() = default;
};




