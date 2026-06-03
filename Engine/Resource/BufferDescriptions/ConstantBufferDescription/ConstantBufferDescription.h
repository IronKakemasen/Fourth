#pragma once
#include "../BufferDescriptionBehavior.h"


//CBバッファ
struct ConstantBufferDescription final : public BufferDescriptionBehavior
{
	UINT sizeInByte{};

public: 
	virtual void CheckRequirementsFilled()override;

};


