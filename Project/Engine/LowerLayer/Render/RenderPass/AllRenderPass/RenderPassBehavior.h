#pragma once
#include "../../RenderContext.h"


//外部
#include "../../../Buffer/BufferContext.h"

class RuntimeWrapper;
class Model;
struct RenderStateKey;
class ColorBuffer;
class DepthStencilBuffer;


class RenderContext::PassBehavior
{
public:

	PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_);
	virtual ~PassBehavior() = default;

	virtual void Update
	(
		[[maybe_unused]] std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	) = 0;

	PassDesc const* WatchDesc() const;

	//初期化用のPassDescからランタイム用へ
	void CreatePassInfo
	(
		NexusFieldProof proof_,
		std::unordered_map<std::string, BufferUniqueID> const& idMap_,
		UINT const refOffset_
	);


	//レンダーターゲットのあれこれの描画コマンドをたたく
	void BeginPass(RuntimeWrapper& cmdWrapper_, BufferContext::BufferDispatcher& bufDispatcher_);


protected:

	//Passの設計図
	std::unique_ptr<PassDesc> desc;
	//ランタイムで必要になるPassの情報をまとめたもの
	std::unique_ptr<RuntimePassInfo> runtimePassInfo;


private:

	//Passのルートコンスタンツを転送
	void TransferRootConstants(RuntimeWrapper& cmdWrapper_);

	//カラーバッファのビューをクリアする
	void ClearColorBufferView
	(
		D3D12_CPU_DESCRIPTOR_HANDLE const handleCPU_,
		const FLOAT* clearColorPtr_,
		RuntimeWrapper& cmdWrapper_
	);

	//深度ステンシルバッファのビューをクリアする
	void ClearDepthStencilBufferView
	(
		D3D12_CPU_DESCRIPTOR_HANDLE const handleCPU_,
		RuntimeWrapper& cmdWrapper_
	);

	//深度ステンシルバッファからCPUハンドルを引っ張る
	D3D12_CPU_DESCRIPTOR_HANDLE PullDepthStencilBufferHandle
	(
		BufferUniqueID const id_,
		BufferContext::BufferDispatcher& bufDispatcher_
	);

	//そのカラーバッファバージョン
	D3D12_CPU_DESCRIPTOR_HANDLE PullColorBufferHandle
	(
		BufferUniqueID const id_,
		BufferContext::BufferDispatcher& bufDispatcher_
	);

	//描画先の決定
	void SetrenderTargets
	(
		std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> const& rtHandles_,
		UINT const numRT_,
		D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle_,
		RuntimeWrapper& cmdWrapper_
	);

	template<typename MatrixType>
	void SetMatrix
	(
		UINT const num_,
		const MatrixType* matrix_,
		RuntimeWrapper& cmdWrapper_
	);



};


template<>
void RenderContext::PassBehavior::SetMatrix<D3D12_VIEWPORT>
(
	UINT const num_,
	const D3D12_VIEWPORT* matrix_,
	RuntimeWrapper& cmdWrapper_
);

template<>
void RenderContext::PassBehavior::SetMatrix<D3D12_RECT>
(
	UINT const num_,
	const D3D12_RECT* matrix_,
	RuntimeWrapper& cmdWrapper_
);

