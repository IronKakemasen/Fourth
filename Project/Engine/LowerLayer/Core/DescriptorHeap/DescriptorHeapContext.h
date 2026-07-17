#pragma once
#include "../../Resource/Buffer/BufferContext.h"

class Nexus;
class DescriptorHeapPool;
class SwapChainContext;

class DescriptorHeapContext
{
public:

	//DescriptorHeapを生成するコマンド
	using DescriptorCreateCommand =
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

	//Nexusのみ生成可能
	struct InstanceKey;
	//ViewCreatorポインター取得を許可するキー
	struct ViewCreatorGetKey;
	//view生成
	class ViewCreator;

	DescriptorHeapContext
	(
		InstanceKey instanceKey_,
		DescriptorCreateCommand createDescriptor_,
		CreateRTVCommand createRtv_,
		CreateSRVCommand createSrv_,
		CreateDSVCommand createDsv_,
		CreateUAVCommand createUav_,
		std::array<UINT, 3> incrementSizeOfDH_
	);

	~DescriptorHeapContext();

	//ビュークリエイターをシェアする。
	ViewCreator* GetViewCreator(ViewCreatorGetKey key_);

private:

	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;
	std::unique_ptr<DescriptorHeapCreator> descriptorHeapCreator;

	//DescriptorHeapPoolのコンテナ
	std::unordered_map < D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeapPool>> descriptorHeapContainer;

	//ビュー生成機関
	std::unique_ptr<ViewCreator> viewCreator;

	//DescriptorHeapの作成
	template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
	void CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_);
	
	//各種ディスクリプターヒープの作成
	void CreateDescriptorHeaps(UINT rtvDH_, UINT srvDH_, UINT dsvDH_);

	//DescriptorHeapの名前を取得（初期化用）
	std::string GetDescriptorName(D3D12_DESCRIPTOR_HEAP_TYPE heapType_)const;

	//コマンドのセット
	void SetCreateDescriptorHeapCommand(DescriptorCreateCommand createDescriptor);
	
	//コマンドのセット2
	void SetCreateViewCommand
	(
		InstanceKey key_,
		CreateRTVCommand createRtv_,
		CreateSRVCommand createSrv_,
		CreateDSVCommand createDsv_,
		CreateUAVCommand createUav_
	);

};





//生成できるのはNexusのみ
struct DescriptorHeapContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};

struct DescriptorHeapContext::ViewCreatorGetKey
{
private:

	friend class SwapChainContext;
	friend class BufferContext::BufferAssembler;
	explicit ViewCreatorGetKey() = default;

};



