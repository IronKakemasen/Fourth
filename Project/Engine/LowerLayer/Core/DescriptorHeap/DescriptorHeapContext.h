#pragma once

class Nexus;
class DescriptorHeapPool;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;

class DescriptorHeapContext
{
	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;

protected:

	//DescriptorHeapを生成するコマンド
	using CreateDescriptorHeapCommand =
		std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>;
	//ディスクリプタヒープコンテナ
	using DescriptorHeapContainer = std::unordered_map < D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeapPool>>;
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
public:

	//Nexusフィールドである証
	struct NexusFieldProof;
	//view生成
	class ViewCreator;
	//ツール貸し出しクラス
	class ToolLender;

	DescriptorHeapContext
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_
	);

	~DescriptorHeapContext();

	std::unique_ptr<DescriptorHeapContextDiplomat> diplomat;

private:

	//DescriptorHeapPoolのコンテナ
	DescriptorHeapContainer descriptorHeapContainer;
	//ビュー生成機関
	std::unique_ptr<ViewCreator> viewCreator;
	

	//各種ディスクリプターヒープの作成
	void CreateDescriptorHeaps(DescriptorHeapContext::NexusFieldProof proof_, DeviceContextDiplomat* deviceContextDiplomat_);

	//ビュークリエイターの使用するコマンドをセット
	void SetCreateViewCommand(DescriptorHeapContext::NexusFieldProof proof_ , DeviceContextDiplomat* deviceContextDiplomat_);

};





//生成できるのはNexusのみ
struct DescriptorHeapContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

