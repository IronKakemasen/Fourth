#pragma once
#include "../../Resource/BufferDescriptions/BufferDescriptionBehavior.h"

class WinApp;

class GPUBufferCreator
{
public:

	struct InstanceKey;

	GPUBufferCreator(InstanceKey instanceKey_);

private:

	//引数のDescriptionに不備がないかチェックしてエラーを吐く
	void CheckDescription(BufferDescriptionBehavior* srcDesc_);

};



struct GPUBufferCreator::InstanceKey
{

private:

	friend class WinApp;
	explicit InstanceKey() = default;
};
