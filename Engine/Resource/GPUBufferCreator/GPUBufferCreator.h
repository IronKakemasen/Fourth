#pragma once
#include "../BufferDescriptions/IBufferDescription.h"
#include "../BufferContext.h"
#include <type_traits> 
#include "../GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../GPUBuffer//SRV_UAVBuffer/SRV_UAVBuffer.h"
#include "../GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"

class WinApp;

class GPUBufferCreator
{

public:

	GPUBufferCreator(BufferContext::InstanceKey instanceKey_, BufferContext::CreateResourceCommand createResourceCommand_)
		: createResourceCommand(createResourceCommand_) {}

	~GPUBufferCreator() = default;

	//バッファ生成
	template<typename BufferType, typename DescType>
	[[nodiscard]] std::unique_ptr<BufferType> CreateBuffer(DescType descType_, const std::string& name_)
	{
		//要項チェック
		descType_.CheckRequirementsFilled();
		//名前変換
		std::string convName = NameConverter<BufferType>(name_);

		auto resource1 = CreateResource<BufferType>(descType_, convName);
		auto resource2 = CreateResource<BufferType>(descType_, convName);

		auto descPtr = std::make_unique<DescType>(std::move(descType_));

		return std::make_unique<BufferType>
		(
			GPUBufferBehavior::InstanceKey{},
			convName,
			std::move(resource1),
			std::move(resource2),
			std::move(descPtr)
		);
	}

private:

	//リソース生成コマンド
	BufferContext::CreateResourceCommand createResourceCommand;

	//リソースをコマンドから生成する
	template<typename BufferType, typename DescType>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateResource(DescType descType_, const std::string& name_)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> resource;

		D3D12_RESOURCE_DESC resourceDesc = descType_.CreateResourceDesc();
		D3D12_HEAP_PROPERTIES heapProperties = descType_.CreateHeapProperties();

		if constexpr (std::is_same_v<BufferType, ColorBuffer> || std::is_same_v<BufferType, DepthStencilBuffer>)
		{
			D3D12_CLEAR_VALUE clearValue = descType_.WatchClearValue();
			resource = createResourceCommand(resourceDesc, heapProperties, &clearValue, name_);
		}
		else
		{
			resource = createResourceCommand(resourceDesc, heapProperties, nullptr, name_);
		}

		return resource;
	}

	//名前変換
	template<typename BufferType>
	std::string NameConverter(const std::string& name_)
	{
		std::string conName;

		if constexpr (std::is_same_v<BufferType, ColorBuffer>)
		{
			conName += "ColorBuffer [ " + name_ + " ] ";
		}
		else if constexpr (std::is_same_v<BufferType, ConstantBuffer>)	 
		{
			conName += "ConstantBuffer [ " + name_ + " ] ";
		}
		else if constexpr (std::is_same_v<BufferType, SRV_UAVBuffer>)
		{
			conName += "SRV_Creator [ " + name_ + " ] ";
		}
		else if constexpr (std::is_same_v<BufferType, DepthStencilBuffer>)
		{
			conName += "DepthStencilBuffer [ " + name_ + " ] ";
		}

		return conName;
	}
};