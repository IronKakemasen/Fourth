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
//void IColorBuffer::AssembleMatrix(UINT width_, UINT height_)
//{
//	//クライアント領域と一緒のサイズにして画面全体に表示
//	viewport.Width = static_cast<FLOAT>(width_);
//	viewport.Height = static_cast<FLOAT>(height_);
//	viewport.TopLeftX = 0.0f;
//	viewport.TopLeftY = 0.0f;
//	viewport.MinDepth = 0.0f;
//	viewport.MaxDepth = 1.0f;
//
//	//シザー矩形
//	scissorRect.right = static_cast<LONG>(width_);
//	scissorRect.bottom = static_cast<LONG>(height_);
//	scissorRect.left = static_cast<LONG>(0.0f);
//	scissorRect.top = static_cast<LONG>(0.0f);
//
//	Logger::Log("Structure:  Matrix", "BufferInterface.cpp");
//}
