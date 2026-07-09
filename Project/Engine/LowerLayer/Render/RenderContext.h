#pragma once

class Nexus;
class ShaderContext;



class RenderContext
{
public:

	struct InstanceKey;

	RenderContext(InstanceKey key_);
	~RenderContext();

	//モデルの描画情報を収集して整理する
	class ModelRenderingInfoOrganizer;


private:

	//グラフィックス専用のpsoのプール、配布
	class PSO_PoolDispatcher;
	//PSO_Assemblerを使ってグラフィックス用のPSOを生成
	class PSO_Creator;


	std::unique_ptr<PSO_PoolDispatcher> pso_PoolDispatcher;
};


struct RenderContext::InstanceKey
{
private:
	friend class Nexus;
	explicit InstanceKey() = default;
};
