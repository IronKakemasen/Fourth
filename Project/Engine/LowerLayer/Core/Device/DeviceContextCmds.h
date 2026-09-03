#pragma once

namespace DeviceContextCmds
{
	//リソースを生成するコマンドを返す関数(ConstantBufferDescription , ColorBufferDescription)
	using CreateResource = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_
	)>;

	//DescriptorHeapを生成するコマンドを返す関数
	using CreateDescriptorHeap = std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>;

	//リソースのViewを作成するコマンドを返す関数
	template<typename ViewType>
	using CreateView = std::function<void
	(
		ID3D12Resource* resource_,
		const ViewType* desc_,
		D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_
	)>;

	//UAV作成コマンドのみ引数が異なるため別途用意
	using CreateUAV =  std::function<void
	(
		ID3D12Resource* resource_, 
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_,
		D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, 
		ID3D12Resource* CounterResource_
	)>;

	//スワップチェーンを生成するためのコマンド
	using CreateSwapChain = std::function<void
	(
		ID3D12CommandQueue* commandQueue_,
		DXGI_SWAP_CHAIN_DESC1 desc_,
		IDXGISwapChain4** swapChainDoublePtr_,
		const HWND hWnd_
	)>;

	//PSOを生成するコマンド
	using CreateGraphicsPSO = std::function<void(ID3D12PipelineState** doublePtr_pipelineState_, D3D12_PIPELINE_STATE_STREAM_DESC* desc_)>;

	//PSOを生成するコマンド
	using CreateComputePSO = std::function<void(ID3D12PipelineState** doublePtr_pipelineState_, D3D12_COMPUTE_PIPELINE_STATE_DESC* desc_)>;

	//ルートシグネチャを生成するコマンド
	using CreateRootSig = std::function<void
	(
		UINT nodeMask_,
		Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_,
		ID3D12RootSignature** doublePtr_rootSignature_
	)>;

	//リソースのViewを作成するコマンドを返す関数
	template<typename ViewType>
	using CreateView = std::function<void
	(
		ID3D12Resource* resource_,
		const ViewType* desc_,
		D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_
	)>;

}

