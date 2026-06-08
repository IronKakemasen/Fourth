#pragma once
#include "../DescriptorHeapContext.h"

class DescriptorHeapClass;

class ViewCreatorBehavior
{
public:

	ViewCreatorBehavior(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

protected:

	//DescriptorHeapClassのアドレス
	DescriptorHeapClass* descriptorHeapClass = nullptr;

	//現在のviewの生成数
	uint32_t currentCreateNum{};

};

