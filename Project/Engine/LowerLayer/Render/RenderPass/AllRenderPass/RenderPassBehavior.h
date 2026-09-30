#pragma once
#include "../../RenderContext.h"
#include "../../RenderContextRuntime/PSO_PoolDispatcher/GraphicsPSO_Key.h"

//外部
#include "../../../Buffer/BufferContext.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/BufferInterface.h"

#include "../../../Resource/Model/ModelContainer/RenderStateKey/RenderStateKey.h"

class RuntimeWrapper;
class Model;
class ColorBuffer;
class DepthStencilBuffer;
class GPUBufferBehavior;

///☆重要☆
///バッファのステート遷移は、使う人(Pass)が責任を持つことにします。
///自身の所持する描画用のバッファはもちろん、参照するバッファも
///そうすれば、自身のバッファを誰がどう使うとかは気にしなくてよくなるので
///銭湯でよく見る、座っていた人が次の人のためにお湯を掛けるのではなく、
///これから座る人がお湯をかけましょう

class RenderContext::PassBehavior
{
public:

	PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_);
	virtual ~PassBehavior() = default;

	virtual void Update
	(
		[[maybe_unused]] std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		[[maybe_unused]] RenderStateComponent::FillMode const modelFillMode_,
		PSO_PoolDispatcher& psoDispatcher_,
		RuntimeWrapper& cmdWrapper_,
		[[maybe_unused]] BufferContext::BufferDispatcher& bufDispatcher_
	) = 0;

	PassDesc const* WatchDesc() const;

	//初期化用のPassDescからランタイム用へ
	void CreatePassInfo
	(
		NexusFieldProof proof_,
		std::vector<BufferUniqueID> const& refColorBuffersID_,
		std::vector<BufferUniqueID> const& refDepthStencilBuffersID_,
		UINT const refOffset_
	);

	//レンダーターゲットのあれこれの描画コマンドをたたく
	//自身の所持するバッファを全てレンダーターゲットへステート遷移
	//Pass個人が呼ぶ必要はない
	void BeginPass(RuntimeWrapper& cmdWrapper_, BufferContext::BufferDispatcher& bufDispatcher_);

	
protected:

	//モデルを描画する
	void RenderModels
	(
		std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		RenderStateComponent::FillMode const fillMode_,
		PSO_PoolDispatcher& psoDispatcher_,
		RuntimeWrapper& cmdWrapper_
	);

	//オフスクにレンダリングをする
	void RenderOffScreen
	(
		PSO_PoolDispatcher& psoDispatcher_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	);


private:

	//Passの設計図
	std::unique_ptr<PassDesc> desc;
	//ランタイムで必要になるPassの情報をまとめたもの
	std::unique_ptr<RuntimePassInfo> runtimePassInfo;
	//バリアのキャッシュ
	std::vector<D3D12_RESOURCE_BARRIER> barrierCache;
	//とりあえず10確保しておこう
	static constexpr UINT kBarrierCacheCapacity = 10;

	//バッファのステートを切り替えのためのバリアを生成
	//中で張ってない
	template<BufferUsage usage>
	void CreateBarrier(IRenderTargetBuffer* buffer_);

	//溜めたステート遷移のバリアを張る
	void PitchBarrierCached(RuntimeWrapper& cmdWrapper_);

	//RenderStateKeyから、Passとフィルモード以外のPSOキーの入力をする
	//呼び出し回数が多いのでヘッダで定義しちゃいます
	void WritePsoKeyFromRenderStateKey(RenderStateKey const& renderStateKey_, GraphicsPSO_Key& dst_)
	{
		dst_.cull = renderStateKey_.Get<RenderStateKey::Sequence::kCullMode>();
		dst_.mesh = renderStateKey_.Get<RenderStateKey::Sequence::kMeshType>();
		dst_.material = renderStateKey_.Get<RenderStateKey::Sequence::kMaterialType>();
		//ブレンドモードキーはモデル依存
		dst_.blend = renderStateKey_.Get<RenderStateKey::Sequence::kBlendMode>();
	}

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

	//描画先の決定
	void SetRenderTargets
	(
		std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> const& rtHandles_,
		UINT const numRT_,
		D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle_,
		RuntimeWrapper& cmdWrapper_
	);

	//バッファのユニークIDからバッファを検索
	template<typename BufferType>
	BufferType* FindBufferWithID
	(
		BufferUniqueID const id_,
		BufferContext::BufferDispatcher& bufDispatcher_
	);

	//バッファからCPUハンドルを引っ張る
	template<typename BufferType>
	D3D12_CPU_DESCRIPTOR_HANDLE PullHandleCPU
	(
		BufferType* buffer_,
		BufferContext::BufferDispatcher& bufDispatcher_
	);

	//viewportやscissorRectsのセット
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


template<>
ColorBuffer* RenderContext::PassBehavior::FindBufferWithID
(
	BufferUniqueID const id_,
	BufferContext::BufferDispatcher& bufDispatcher_
);
template<>
DepthStencilBuffer* RenderContext::PassBehavior::FindBufferWithID
(
	BufferUniqueID const id_,
	BufferContext::BufferDispatcher& bufDispatcher_
);



template<>
D3D12_CPU_DESCRIPTOR_HANDLE RenderContext::PassBehavior::PullHandleCPU
(
	ColorBuffer* buffer_,
	BufferContext::BufferDispatcher& bufDispatcher_
);
template<>
D3D12_CPU_DESCRIPTOR_HANDLE RenderContext::PassBehavior::PullHandleCPU
(
	DepthStencilBuffer* buffer_,
	BufferContext::BufferDispatcher& bufDispatcher_
);

