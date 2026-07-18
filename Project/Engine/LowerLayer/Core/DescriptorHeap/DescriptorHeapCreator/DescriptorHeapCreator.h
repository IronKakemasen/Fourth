#pragma once
#include "../DescriptorHeapContext.h"
#include "../DescriptorHeapPool/DescriptorHeapPool.h"


class DescriptorHeapContext::DescriptorHeapCreator
{
	template<D3D12_DESCRIPTOR_HEAP_TYPE heapType>
	inline std::string DescriptorName()const
	{
		std::string descriptorHeapString = "_descriptorHeap";

		if constexpr (heapType == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)	return "SRV_UAV" + descriptorHeapString;
		else if constexpr (heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV)		return "RTV" + descriptorHeapString;
		else if constexpr (heapType == D3D12_DESCRIPTOR_HEAP_TYPE_DSV)		return "DSV" + descriptorHeapString;

		ErrorMessageOutput::Assert::OutputError("用意してないDescriptorheapTypeです", "DescriptorHeapCreator.h");

		return descriptorHeapString;
	}


public:

	DescriptorHeapCreator(InstanceKey key_, CreateDescriptorHeapCommand cmd_) :createCmd(cmd_) {}


	template<D3D12_DESCRIPTOR_HEAP_TYPE heapType>
	inline std::unique_ptr<DescriptorHeapPool> Create(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_)const
	{
		return std::make_unique<DescriptorHeapPool>
		(
			std::move(createCmd(heapType, numDescriptors_, shaderVisible_)),
			handleIncSize_,
			numDescriptors_,
			shaderVisible_,
			DescriptorName<heapType>()
		);

	}


private:


	//DescriptorHeapを生成するコマンド
	CreateDescriptorHeapCommand createCmd;

};

