#pragma once
#include "../BufferDescriptionBehavior.h"


//CBバッファ
struct ConstantBufferDescription final : public BufferDescriptionBehavior
{
private:

	struct Param
	{
		UINT sizeInByte{};
	}param;

public:

	ConstantBufferDescription
	(
		UINT sizeInByte_, 
		ResourceStates initialStates_ = { D3D12_RESOURCE_STATE_GENERIC_READ,D3D12_RESOURCE_STATE_GENERIC_READ }
	);

	//パラーメーターチェック
	virtual void CheckRequirementsFilled() const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;

	inline const Param& WatchParam()
	{
		return param;
	}

};


