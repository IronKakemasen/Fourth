#pragma once

class WinApp;
class ViewCreatorBehavior;
class DescriptorHeapClass;
class ViewCreatorBehavior;

class DescriptorHeapContext
{
	//View生成クラスの識別タグ
	enum ViewCreatorType
	{
		kSRV,
		kSampler,
		kRTV,
		kDSV,

		kCount
	};

private:

	using DescroptorCreateCommand = 
		std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>;

	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;
	std::unique_ptr<DescriptorHeapCreator> descriptorHeapCreator;

	//DescriptorHeapClassのコンテナ
	std::unordered_map < D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeapClass>> descriptorHeapContainer;

	//Viewを生成するクラスのコンテナ
	std::unordered_map<ViewCreatorType, std::unique_ptr<ViewCreatorBehavior>> viewCreatorContainer;

	//DepthStencilViewのCPU_DescriptorHandleのコンテナ
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DSV_descriptorHandleCPUContainer;

	//RenderTargetViewのCPU_DescriptorHandleのコンテナ
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RTV_descriptorHandleCPUContainer;


public:

	//WinAppのみ生成可能
	struct InstanceKey;
	//ViewCreator生成キー
	struct CreateKey;

	DescriptorHeapContext(InstanceKey instanceKey_);
	~DescriptorHeapContext();

	//コマンドのセット
	void SetCommand(DescroptorCreateCommand createFunc_);

	//DescriptorHeapの作成
	template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
	void CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_);

private:

	template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
	void CreateViewCreator(DescriptorHeapClass* srcPtr_);

};

//生成できるのはWinAppのみ
struct DescriptorHeapContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};

//ViewCreatorを生成するためのキー
struct DescriptorHeapContext::CreateKey
{
private:

	friend class DescriptorHeapContext;
	explicit CreateKey() = default;
};


template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(DescriptorHeapClass* srcPtr_);

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(DescriptorHeapClass* srcPtr_);

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(DescriptorHeapClass* srcPtr_);



