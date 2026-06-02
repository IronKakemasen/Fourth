#pragma once
#include "../BufferDescriptionBehavior.h"


//CBやVB、IBなどの単純なバッファ
struct BufferDescriptionTypeA final : public BufferDescriptionBehavior
{
	UINT sizeInByte{};

public: 
	virtual void CheckRequirementsFilled()override;

};


