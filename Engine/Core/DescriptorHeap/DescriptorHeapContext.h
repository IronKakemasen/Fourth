#pragma once

class WinApp;
class DescriptorHeapClass;
class ViewCreator;


class DescriptorHeapContext
{

public:

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
	//UAVを生成するコマンド
	using CreateUAVCommand =
		std::function<void(ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* CounterResource_)>;


private:
	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;
	std::unique_ptr<DescriptorHeapCreator> descriptorHeapCreator;

	//DescriptorHeapClassのコンテナ
	std::unordered_map < D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeapClass>> descriptorHeapContainer;

	//ビュー生成機関
	std::unique_ptr<ViewCreator> viewCreator;

public:

	//WinAppのみ生成可能
	struct InstanceKey;
	//ViewCreator生成キー
	struct CreateKey;

	DescriptorHeapContext(InstanceKey instanceKey_);
	~DescriptorHeapContext();

	//DescriptorHeapの作成
	template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
	void CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_);

	//コマンドのセット
	void SetCreateDescroptorHeapCommand(DescroptorCreateCommand createDescriptor);
	//コマンドのセット2
	void SetCreateViewCommand
	(
		CreateRTVCommand createRtv_,
		CreateSRVCommand createSrv_,
		CreateDSVCommand createDsv_,
		CreateUAVCommand createUav_
	);

private:

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



