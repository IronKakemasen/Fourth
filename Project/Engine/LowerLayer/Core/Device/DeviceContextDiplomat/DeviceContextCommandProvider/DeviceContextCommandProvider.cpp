
#include "DeviceContextCommandProvider.h"

//コマンド群
#include "../../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"
#include "../../Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"
#include "../../Commands/CreateView/CommandCreateView.h"
#include "../../Commands/StructureSwapChain/CommandStructureSwapChain.h"
#include "../../Commands/CreatePSO/CommandCreatePSO.h"
#include "../../Commands/CreateRootSignature/CommandCreateRootSignature.h"


namespace
{
	auto const fileName = "CommandProvider.cpp";
}

///+/ C_ = Command
using C_CreateRTV = std::function<void(ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>;
using C_CreateSRV = std::function<void(ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>;
using C_CreateUAV = std::function<void(ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* CounterResource_)>;
using C_CreateDSV = std::function<void(ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>;

using C_CreateDescriptorHeap = std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>;

using C_CreateResource = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>
(
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValue_,
	D3D12_RESOURCE_STATES initialState_,
	const std::string& name_
)>;

using C_CreateSwapChain = std::function< void
(
	ID3D12CommandQueue* commandQueue_,
	DXGI_SWAP_CHAIN_DESC1 desc_,
	IDXGISwapChain4** swapChainDoublePtr_,
	const HWND hWnd_
)>;

DeviceContext::CommandProvider::CommandProvider
(
	DeviceContext::InstanceKey instanceKey_,
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_,
	std::function< IDXGIFactory7* (DeviceContext::AccessKey)> dxgiFactoryGetter_
) : deviceGetter(deviceGetter_), dxgiFactoryGetter(dxgiFactoryGetter_)
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
[[nodiscard]] C_CreateRTV DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreateView command(DeviceContext::GenerateKey{});

		return command.CreateRTV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}
template<>
[[nodiscard]] C_CreateSRV DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreateView command(DeviceContext::GenerateKey{});

		return command.CreateSRV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}

template<>
[[nodiscard]] C_CreateDSV DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreateView command(DeviceContext::GenerateKey{});

		return command.CreateDSV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}

[[nodiscard]] C_CreateUAV DeviceContext::CommandProvider::ProvideCreateUAVCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* CounterResource_)
		{
			auto* device = deviceGetter(DeviceContext::AccessKey{});
			CommandCreateView command(DeviceContext::GenerateKey{});

			return command.CreateUAV(device, resource_, desc_, descriptorHandleCPU_, CounterResource_);
		};

	return retFunc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] C_CreateSwapChain DeviceContext::CommandProvider::ProvideCreateSwapChainCommand()
{
	auto retFunc = [this]
	(
		ID3D12CommandQueue* commandQueue_,
		DXGI_SWAP_CHAIN_DESC1 desc_,
		IDXGISwapChain4** swapChainDoublePtr_,
		const HWND hWnd_
	)
	{
		auto* dxgiFactory = dxgiFactoryGetter(DeviceContext::AccessKey{});
		CommandStructureSwapChain command(DeviceContext::GenerateKey{});

		command.CreateSwapChain(*dxgiFactory, commandQueue_,desc_, swapChainDoublePtr_, hWnd_);
	};

	return retFunc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] C_CreateDescriptorHeap DeviceContext::CommandProvider::ProvideCreateDescriptorHeapCommand()
{
	auto retFunc = [this](D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreateDescriptorHeap command(DeviceContext::GenerateKey{});

		return command.Create(device, heapType_,numDescriptors_, shaderVisible_);
	};

	return retFunc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] C_CreateResource DeviceContext::CommandProvider::ProvideCreateResourceCommand()
{
	auto retFunc = [this]
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_
	)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreateGPUResource command(DeviceContext::GenerateKey{});

		return command.CreateResource
		(
			device, 
			resourceDesc_,
			heapProperties_,
			clearValue_,
			initialState_,
			name_
		);
	};

	return retFunc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::function<void(ID3D12PipelineState** doublePtr_pipelineState_, D3D12_COMPUTE_PIPELINE_STATE_DESC* descType_)>
DeviceContext::CommandProvider::ProvideCreatePSOCommand()
{
	auto retFunc = [this](ID3D12PipelineState** doublePtr_pipelineState_, D3D12_COMPUTE_PIPELINE_STATE_DESC* descType_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreatePSO command(DeviceContext::GenerateKey{});

		command.CreateComputePipelineState(device, doublePtr_pipelineState_, descType_);
	};

	return retFunc;
}

template<>
std::function<void(ID3D12PipelineState** doublePtr_pipelineState_, D3D12_PIPELINE_STATE_STREAM_DESC* descType_)>
DeviceContext::CommandProvider::ProvideCreatePSOCommand()
{
	auto retFunc = [this](ID3D12PipelineState** doublePtr_pipelineState_, D3D12_PIPELINE_STATE_STREAM_DESC* descType_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreatePSO command(DeviceContext::GenerateKey{});

		command.CreateGraphicsPipelineState(device, doublePtr_pipelineState_, descType_);
	};

	return retFunc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::function<void
(
	UINT nodeMask_,
	Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_,
	ID3D12RootSignature** doublePtr_rootSignature_
)>
DeviceContext::CommandProvider::ProvideCommandCreateRootSignature()
{
	auto retFunc = [this](UINT nodeMask_,Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_,ID3D12RootSignature** doublePtr_rootSignature_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		CommandCreateRootSignature command(DeviceContext::GenerateKey{});

		command.CreateRootSignature(device, nodeMask_, signatureBlob_, doublePtr_rootSignature_);
	};

	return retFunc;

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


