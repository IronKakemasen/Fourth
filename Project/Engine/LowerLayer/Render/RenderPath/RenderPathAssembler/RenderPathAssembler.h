#pragma once
#include "../../RenderContext.h"

class RenderContext::RenderPathAssembler
{
public:

	RenderPathAssembler(NexusFieldProof proof_, RenderPassCreator* passCreator_);



private:

	RenderPassCreator* passCreator;
};

