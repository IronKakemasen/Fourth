#pragma once
#include "../DescriptorHeapContext.h"

class DescriptorHeapClass;
class GPUBufferBehavior;

class ViewCreatorBehavior
{
public:

	ViewCreatorBehavior(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	//Viewを生成する。
	virtual [[nodiscard]] uint32_t CreateView(const GPUBufferBehavior& buffer_) = 0;

protected:

	//次のDescriptorHeapの空き空間を計算
	template<typename HandleType>
	[[nodiscard]] HandleType CalculateNextHandle();

	//DescriptorHeapClassのアドレス
	DescriptorHeapClass* descriptorHeapClass = nullptr;

	//現在のviewの生成数
	uint32_t currentCreateNum{};

};

