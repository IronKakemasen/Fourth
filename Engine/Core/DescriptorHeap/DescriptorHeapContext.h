#pragma once

class WinApp;
class ViewCreatorBehavior;


class DescriptorHeapContext
{
private:

	using DescroptorCreateCommand = 
		std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>;

public:

	struct InstanceKey;
	
	DescriptorHeapContext(InstanceKey instanceKey_);
	~DescriptorHeapContext();

	//コマンドのセット
	void SetCommand(DescroptorCreateCommand createFunc_);
	//DescriptorHeapの作成
	void CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible_);

private:

	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;
	std::unique_ptr<DescriptorHeapCreator> descriptorHeapCreator;

	//DescriptorHeapのコンテナ
	std::unordered_map<D3D12_DESCRIPTOR_HEAP_TYPE,Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>> descriptorHeaps;
};


//生成できるのはWinAppのみ
struct DescriptorHeapContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};


[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ID3D12Device* device_,
	D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible);