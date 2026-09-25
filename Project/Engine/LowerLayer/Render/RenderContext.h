#pragma once

class Nexus;
class BufferContextDiplomat;
class RootSignatureContextDiplomat;
class ModelContextDiplomat;
class PSO_ContextDiplomat;
class ShaderContextDiplomat;

class RenderContext
{
	class RenderPassContainer;
	class RenderPathContainer;
	class RenderPathAssembler;
	//グラフィックス専用のpsoのプール、配布
	class PSO_PoolDispatcher;

public:
	//renderPass生成機
	class RenderPassCreator;
	//描画構成Passのビヘイビア
	class PassBehavior;
	//パスを作成するために必要
	struct PassDesc;
	//PassDescから必要な情報だけまとめたもの
	struct RuntimePassInfo;
	//そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo;
	class PathBehavior;
	struct RenderPassState;
	//レンダーパス(Path)を設計し、描画コマンドを叩く強者
	class StaticRenderGraph;

	//ネクサスフィールドの証
	struct NexusFieldProof;

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

private:

	std::unique_ptr<RenderPassContainer> renderPassContainer;
	std::unique_ptr<RenderPathContainer> renderPathContainer;
	std::unique_ptr<StaticRenderGraph> staticRenderGraph;
	std::unique_ptr<PSO_PoolDispatcher> pso_PoolDispatcher;


};


struct RenderContext::NexusFieldProof
{
private:
	friend class Nexus;
	explicit NexusFieldProof() = default;
};




