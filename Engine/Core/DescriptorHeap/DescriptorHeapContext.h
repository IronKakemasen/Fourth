#pragma once

class WinApp;
class IViewCreatorBehavior;
class DescriptorHeapClass;
template<typename ViewDescType> class ViewCreatorBehavior;



class DescriptorHeapContext
{
	//View生成クラスの識別タグ
	enum ViewCreatorType
	{
		kSRV_UAV,
		kSampler,
		kRTV,
		kDSV,

		kCount
	};

private:

	//DescriptorHeapを生成するコマンド
	using DescroptorCreateCommand = 
		std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>;
	//RTVを生成するコマンド
	using CreateRTVCommand =
		std::function<void(ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>;
	//SRVを生成するコマンド
	using CreateSRVCommand =
		std::function<void(ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>;
	//DSVを生成するコマンド
	using CreateDSVCommand =
		std::function<void(ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>;

	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;
	std::unique_ptr<DescriptorHeapCreator> descriptorHeapCreator;

	//DescriptorHeapClassのコンテナ
	std::unordered_map < D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeapClass>> descriptorHeapContainer;

	//Viewを生成するクラスのコンテナ
	std::unordered_map<ViewCreatorType, std::unique_ptr<IViewCreatorBehavior>> viewCreatorContainer;

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
	void SetCommand
	(
		DescroptorCreateCommand descriptorCreate, 
		CreateRTVCommand rtvCreate_ , 
		CreateSRVCommand srvCreate_,
		CreateDSVCommand dsvCreate_
	);

	//DescriptorHeapの作成
	template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
	void CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_);

private:

	//ビュークリエイターの生成
	template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
	void CreateViewCreator(DescriptorHeapClass* srcPtr_);

	//DescriptorHeapの名前を取得（初期化用）
	std::string GetDescriptorName(D3D12_DESCRIPTOR_HEAP_TYPE heapType_);
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



