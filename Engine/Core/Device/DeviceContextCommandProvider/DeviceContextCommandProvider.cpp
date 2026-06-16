#include "PreCompileHeader.h"
#include "DeviceContextCommandProvider.h"


//コマンド群
#include "../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"
#include "../Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"
#include "../Commands/CreateView/CommandCreateView.h"
#include "../Commands/StructureSwapChain/CommandStructureSwapChain.h"


DeviceContext::CommandProvider::CommandProvider
(
	DeviceContext::InstanceKey instanceKey_,
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_,
	std::function< IDXGIFactory7* (DeviceContext::AccessKey)> dxgiFactoryGetter_
) : deviceGetter(deviceGetter_), dxgiFactoryGetter(dxgiFactoryGetter_)
{
	//コマンドの実体を生成
	CreateCommand<CommandCreateGPUResource>(CommandType::kCreateGPUBuffer);
	CreateCommand<CommandCreateDescriptorHeap>(CommandType::kCreateDescriptorHeap);
	CreateCommand<CommandCreateView>(CommandType::kCreateResourceView);
	CreateCommand<CommandStructureSwapChain>(CommandType::kStructureSwapChain);
}

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

using C_CreateSwapChain = std::function< HRESULT
(
	ID3D12CommandQueue* commandQueue_,
	DXGI_SWAP_CHAIN_DESC1 desc_,
	IDXGISwapChain4** swapChainDoublePtr_,
	const HWND hWnd_
)>;


//CreateViewCommand
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
[[nodiscard]] C_CreateRTV DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		auto* command = static_cast<CommandCreateView*>(commandContainer[DeviceContext::CommandType::kCreateResourceView][0].get());

		return command->CreateRTV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}
template<>
[[nodiscard]] C_CreateSRV DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		auto* command = static_cast<CommandCreateView*>(commandContainer[DeviceContext::CommandType::kCreateResourceView][0].get());

		return command->CreateSRV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}

template<>
[[nodiscard]] C_CreateDSV DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		auto* command = static_cast<CommandCreateView*>(commandContainer[DeviceContext::CommandType::kCreateResourceView][0].get());

		return command->CreateDSV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}

[[nodiscard]] C_CreateUAV DeviceContext::CommandProvider::ProvideCreateUAVCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* CounterResource_)
		{
			auto* device = deviceGetter(DeviceContext::AccessKey{});
			auto* command = static_cast<CommandCreateView*>(commandContainer[DeviceContext::CommandType::kCreateResourceView][0].get());

			return command->CreateUAV(device, resource_, desc_, descriptorHandleCPU_, CounterResource_);
		};

	return retFunc;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//StructureSwapChain
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		auto* command = static_cast<CommandStructureSwapChain*>(commandContainer[DeviceContext::CommandType::kStructureSwapChain][0].get());

		return command->CreateSwapChain(*dxgiFactory, commandQueue_,desc_, swapChainDoublePtr_, hWnd_);
	};

	return retFunc;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//CreateDescriptorHeapCommand
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] C_CreateDescriptorHeap DeviceContext::CommandProvider::ProvideCreateDescriptorHeapCommand()
{
	auto retFunc = [this](D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible_)
	{
		auto* device = deviceGetter(DeviceContext::AccessKey{});
		auto* command = static_cast<CommandCreateDescriptorHeap*>(commandContainer[DeviceContext::CommandType::kCreateDescriptorHeap][0].get());

		return command->Create(device, heapType_,numDescriptors_, shaderVisible_);
	};

	return retFunc;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






//リソース生成こまんど
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
			CommandCreateGPUResource* command = static_cast<CommandCreateGPUResource*>(commandContainer[DeviceContext::CommandType::kCreateGPUBuffer][0].get());

			return command->CreateResource
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






