#pragma once
#include "../../Resource/BufferDescriptions/BufferDescriptionBehavior.h"

class WinApp;

class GPUBufferCreator
{
public:

	struct CreateKey;

	GPUBufferCreator(CreateKey createKey_);

private:

	//引数のDescriptionに不備がないかチェックしてエラーを吐く
	void CheckDescription(BufferDescriptionBehavior* srcDesc_);

};



struct GPUBufferCreator::CreateKey
{

private:

	friend class WinApp;
	explicit CreateKey() = default;
};
