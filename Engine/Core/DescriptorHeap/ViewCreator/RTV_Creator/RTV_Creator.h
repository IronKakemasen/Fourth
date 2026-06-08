#pragma once
#include "../ViewCreatorBehavior.h"

class RTV_Creator : public ViewCreatorBehavior
{
public:
	RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

};

