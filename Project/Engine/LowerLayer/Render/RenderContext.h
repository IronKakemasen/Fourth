#pragma once

class Nexus;

class RenderContext
{
public:
	//描画構成Passのビヘイビア
	class PassBehavior;
	class PassDescBehavior;
	//そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo;

	//ネクサスフィールドの証
	struct NexusFieldProof;

	RenderContext(NexusFieldProof proof_);
	~RenderContext();

private:

	//グラフィックス専用のpsoのプール、配布
	class PSO_PoolDispatcher;



	std::unique_ptr<PSO_PoolDispatcher> pso_PoolDispatcher;
};


struct RenderContext::NexusFieldProof
{
private:
	friend class Nexus;
	explicit NexusFieldProof() = default;
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
