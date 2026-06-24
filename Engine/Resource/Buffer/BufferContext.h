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
	//2面性バッファのリソースステートの追跡を行い、Swapも行う	
	class RWResourceStateTracker;
	//１面性バッファの制御を行う。
	class FrameBufferedResourceController;
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


	//自身のインスタンス化キー
	struct InstanceKey;
	//ResourceCreatorとViewCreatorでバッファを生成
	class BufferAssembler;

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

	//全バッファのユニークコンテナ
	std::vector<std::unique_ptr<GPUBufferBehavior>> bufferContainer;
	//ピンポンバッファのアドレスコンテナ
	std::vector<GPUBufferBehavior*> pingPongBufferPtrContainer;
	//１面性バッファのアドレスコンテナ
	std::vector<GPUBufferBehavior*> frameBufferPtrContainer;

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
