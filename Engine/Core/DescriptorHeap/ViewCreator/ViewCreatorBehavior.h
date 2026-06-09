#pragma once
#include "../DescriptorHeapContext.h"
#include <type_traits> 
#include "../DescriptorHeapClass/DescriptorHeapClass.h"

class GPUBufferBehavior;

//ViewCreatorBehaviorの共通インターフェースクラス
class IViewCreatorBehavior 
{
public:
	virtual ~IViewCreatorBehavior() = default;
	virtual void CreateView(GPUBufferBehavior& buffer_) = 0;

};


//こちらが中身のビュー生成テンプレ基底クラス
template<typename ViewDescType>
class ViewCreatorBehavior :public IViewCreatorBehavior
{
public:

	ViewCreatorBehavior(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
		: descriptorHeapClass(descriptorHeapClass_), currentCreateNum(0){ }
	
	virtual ~ViewCreatorBehavior() = default;

	//Viewを生成する。
	virtual void CreateView(GPUBufferBehavior& buffer_) = 0;

	//ビュー生成コマンドをセットする
	inline void SetCommand(std::function<void(ID3D12Resource*, const ViewDescType*, D3D12_CPU_DESCRIPTOR_HANDLE) > command_)
	{
		createViewCommand = command_;
	}

protected:

	//DescriptorHeapClassのアドレス
	DescriptorHeapClass* descriptorHeapClass = nullptr;

	//現在のviewの生成数
	uint32_t currentCreateNum{};

	//ビュー生成コマンド
	std::function<void(ID3D12Resource*, const ViewDescType*, D3D12_CPU_DESCRIPTOR_HANDLE)> createViewCommand;

	//ViewDescの生成関数
	virtual ViewDescType CreateViewDesc() = 0;

	//次のDescriptorHeapの空き空間を計算
	template<typename HandleType>
	[[nodiscard]] inline HandleType CalculateNextHandle()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			(currentCreateNum < descriptorHeapClass->kMaxDescriptor),
			"もうこれ以上Viewを作れません", "ViewCreatorBehavior.h"
		);

		if constexpr (std::is_same_v<HandleType, D3D12_CPU_DESCRIPTOR_HANDLE>)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handleStartCPU = descriptorHeapClass->descriptorHeap->GetCPUDescriptorHandleForHeapStart();
			D3D12_CPU_DESCRIPTOR_HANDLE next;
			next.ptr = handleStartCPU.ptr + descriptorHeapClass->handleIncrementSize * currentCreateNum;
			return next;
		}
		else if constexpr (std::is_same_v<HandleType, D3D12_GPU_DESCRIPTOR_HANDLE>)
		{
			D3D12_GPU_DESCRIPTOR_HANDLE handleStartGPU = descriptorHeapClass->descriptorHeap->GetGPUDescriptorHandleForHeapStart();
			D3D12_GPU_DESCRIPTOR_HANDLE next;
			next.ptr = handleStartGPU.ptr + descriptorHeapClass->handleIncrementSize * currentCreateNum;
			return next;
		}
	}
};

