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
		: descriptorHeapClass(descriptorHeapClass_){ }
	
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

	//ビュー生成コマンド
	std::function<void(ID3D12Resource*, const ViewDescType*, D3D12_CPU_DESCRIPTOR_HANDLE)> createViewCommand;

	//ViewDescの生成関数
	virtual ViewDescType CreateViewDesc() = 0;

	//次のDescriptorHeapの空き空間を計算
	//この中ではView生成数は上昇しない
	template<typename HandleType>
	[[nodiscard]] inline HandleType CalculateHandle()
	{
		//CPU
		if constexpr (std::is_same_v<HandleType, D3D12_CPU_DESCRIPTOR_HANDLE>)
		{
			return descriptorHeapClass->CalculateHandle<D3D12_CPU_DESCRIPTOR_HANDLE>(DescriptorHeapClass::AccessKey{});
		}
		//GPU
		else if constexpr (std::is_same_v<HandleType, D3D12_GPU_DESCRIPTOR_HANDLE>)
		{
			return descriptorHeapClass->CalculateHandle<D3D12_GPU_DESCRIPTOR_HANDLE>(DescriptorHeapClass::AccessKey{});
		}
	}
};

