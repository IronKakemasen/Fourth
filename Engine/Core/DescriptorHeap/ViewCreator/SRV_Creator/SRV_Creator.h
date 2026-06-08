#pragma once
#include "../ViewCreatorBehavior.h"

class SRV_Creator : public ViewCreatorBehavior
{
public:
	SRV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

};

