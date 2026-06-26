#pragma once

class Nexus;
class DescriptorHeapContext;
class GPUBufferBehavior;

class BufferContext
{
	//生成したバッファを回収し分別する
	class BufferCollector;
	//生成したバッファの削除を担当
	class BufferDeferredReleaser;
	//レンダーターゲット系バッファの描画パス構築に必要な情報の抽出とそのリソースのSwapを行う
	class RenderTargetBufferInfoExtractor;
	//フレームバッファ系バッファの描画パス構築に必要な情報の抽出を行う
	class FrameBufferedBufferInfoExtractor;
	//コンピュートバッファ系のパス構築に必要な情報の抽出とそのリソースのSwapを行う
	class ComputeBufferInfoExtractor;
	//生リソース生成
	class ResourceCreator;
	//BufferAssemblerとBufferCollectorをつかってバッファを作成する
	class BufferCreator;

	//リソース生成コマンド
	using CreateResourceCommand = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_
	)>;

public:

	//バッファのユニークID
	using BufferUniqueID = uint32_t;

	//自身のインスタンス化キー
	struct InstanceKey;
	//ResourceCreatorとViewCreatorでバッファを生成
	class BufferAssembler;

	//登録先識別用
	enum class RegisterType
	{
		kRenderTarget,
		kFrameBuffer,
		kComputeBuffer,
		kCount
	};

	BufferContext
	(
		InstanceKey instanceKey_,
		CreateResourceCommand createResourceCommand_,
		DescriptorHeapContext* descriptorHeapContext_
	);

	~BufferContext();

	///+/バッファ生成クラス（本丸）
	std::unique_ptr<BufferCreator> bufferCreator;

private:

	//ColorBufferやDepthStencilBufferなどレンダーターゲットなバッファのコンテナ
	std::vector<std::unique_ptr<GPUBufferBehavior>> renderTargetBufferContainer;
	//computeBufferのような、コンピュートシェーダをかませるバッファのコンテナ
	std::vector<std::unique_ptr<GPUBufferBehavior>> computeBufferContainer;
	//ConstantBufferやUploadStructuredBufferのようなフレームバッファのコンテナ
	std::vector<std::unique_ptr<GPUBufferBehavior>> frameBufferContainer;

	//ユニークIDがどこのバッファコンテナの何番目のバッファを指しているのか示すマップコンテナ
	std::unordered_map<BufferContext::BufferUniqueID, std::pair<RegisterType, uint32_t>> bufferLocationMap;

	void InstantiateBufferCreator
	(
		InstanceKey instanceKey_,
		CreateResourceCommand createResourceCommand_,
		DescriptorHeapContext* descriptorHeapContext_
	);

};


struct BufferContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
