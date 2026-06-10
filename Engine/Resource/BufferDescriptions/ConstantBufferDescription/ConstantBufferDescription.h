#pragma once
#include "../BufferDescriptionBehavior.h"


//CBバッファ
struct ConstantBufferDescription final : public BufferDescriptionBehavior
{
	UINT sizeInByte{};

	virtual void CheckRequirementsFilled() const override;
};


