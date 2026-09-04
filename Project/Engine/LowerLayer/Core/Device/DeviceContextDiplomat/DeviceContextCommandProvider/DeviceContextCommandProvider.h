#pragma once
#include "../../DeviceContext.h"
#include "../../DeviceContextCmds.h"

class DeviceContextCommandBehavior;

//Deviceを使用する処理を、使用しない形にコマンド化して提供するクラス
//初期化生成しか使用しないかつ引数がほぼない場合は、CommandExecutorが行う
class DeviceContext::CommandProvider
{
	template<typename CmdType>
	struct CmdTypeTraits;

	struct CreateResourceLicence;
	struct CreateViewLicence;
	struct CreateDescriptorHeapLicence;
	struct CommandContextProof;
	struct CreateSwapChainLicence;
	struct CreateRootSigLicence;
	struct CreatePSO_Licence;


public:

	CommandProvider
	(
		NexusFieldProof licence_,
		std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_,
		std::function< IDXGIFactory7* (DeviceContext::AccessKey)> dxgiFactoryGetter_
	);

	template<typename CmdType>
	using LicenceType = typename CmdTypeTraits<CmdType>::Type;

	template<typename CmdType>
	[[nodiscard]] CmdType Provide(typename CmdTypeTraits<CmdType>::Type licence_);

	


private:

	//デバイスコンテキストのコアパーツにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter;
	std::function< IDXGIFactory7* (DeviceContext::AccessKey)> dxgiFactoryGetter;

};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateResource>
{
	using Type = CreateResourceLicence;
};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateDescriptorHeap>
{
	using Type = CreateDescriptorHeapLicence;
};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC>>
{
	using Type = CreateViewLicence;
};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC>>
{
	using Type = CreateViewLicence;
};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC>>
{
	using Type = CreateViewLicence;
};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateUAV>
{
	using Type = CreateViewLicence;
};


template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateSwapChain>
{
	using Type = CreateSwapChainLicence;
};


template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreatePSO<D3D12_COMPUTE_PIPELINE_STATE_DESC>>
{
	using Type = CreatePSO_Licence;
};

template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreatePSO<D3D12_PIPELINE_STATE_STREAM_DESC>>
{
	using Type = CreatePSO_Licence;
};

 
template<>
struct DeviceContext::CommandProvider::CmdTypeTraits<DeviceContextCmds::CreateRootSig>
{
	using Type = CreateRootSigLicence;
};


template<>
[[nodiscard]] DeviceContextCmds::CreateResource DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateResource>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateDescriptorHeap DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateDescriptorHeap>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateSwapChain DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateSwapChain>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC> DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC>>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC> DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC>>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC> DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC>>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateUAV DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateUAV>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreatePSO<D3D12_COMPUTE_PIPELINE_STATE_DESC> DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreatePSO<D3D12_COMPUTE_PIPELINE_STATE_DESC>>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreatePSO<D3D12_PIPELINE_STATE_STREAM_DESC> DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreatePSO<D3D12_PIPELINE_STATE_STREAM_DESC>>::Type licence_);

template<>
[[nodiscard]] DeviceContextCmds::CreateRootSig DeviceContext::CommandProvider::Provide
(typename CmdTypeTraits<DeviceContextCmds::CreateRootSig>::Type licence_);


