#pragma once
#include "../IBufferDescription.h"


//CBバッファ
struct ConstantBufferDescription final : public IBufferDescription
{
	UINT sizeInByte{};

	//パラーメーターチェック
	virtual void CheckRequirementsFilled() const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
};


