#pragma once
#include "../ViewCreatorBehavior.h"


class DSV_Creator : public ViewCreatorBehavior
{
public:
	DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

};

