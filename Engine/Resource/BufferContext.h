#pragma once

class WinApp;
class DescriptorHeapContext;

class BufferContext
{
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

	class ResourceCreator;
	class BufferAssembler;

	//自身のインスタンス化キー
	struct InstanceKey;

	BufferContext
	(
		InstanceKey instanceKey_, 
		CreateResourceCommand createResourceCommand_, 
		DescriptorHeapContext* descriptorHeapContext_
	);

	~BufferContext();

private:

	//バッファ生成クラス
	std::unique_ptr<BufferAssembler> bufferAssembler;

};


struct BufferContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};
