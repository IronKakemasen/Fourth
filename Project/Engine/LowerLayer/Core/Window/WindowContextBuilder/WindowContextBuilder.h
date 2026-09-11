#pragma once
#include "../WindowContext.h"

class WindowContext::Builder
{
	friend class WindowContext;

	static CoreParts Build(NexusFieldProof proof_);


	//以下ヘルパー
private:
	static CoreParts CreateCoreParts();

};

