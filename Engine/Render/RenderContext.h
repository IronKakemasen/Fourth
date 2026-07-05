#pragma once

class Nexus;
class ShaderContext;

class RenderContext
{
public:

	struct InstacnceKey;

	RenderContext(InstacnceKey key_);
	~RenderContext();

	//モデルの描画情報を収集して整理する
	class ModelRenderingInfoOrganizer;


private:

	//適切なpsoを渡す
	class PSO_PoolDispatcher;



	std::unique_ptr<PSO_PoolDispatcher> pso_PoolDispatcher;
	//PSOのプール
	std::vector<ID3D12PipelineState*> graphicsPSO_pool;

};


struct RenderContext::InstacnceKey
{
private:
	friend class Nexus;
	explicit InstacnceKey() = default;
};
