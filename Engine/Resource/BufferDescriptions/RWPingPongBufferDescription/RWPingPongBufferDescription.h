#pragma once
#include "../BufferDescriptionBehavior.h"


//読み書き
struct RWPingPongBufferDescription final :public BufferDescriptionBehavior, ISRV_Assembler, IUAV_Assembler
{
private:

	struct Param
	{
		UINT structureByte{};
		UINT numElements{};
		UINT firstElement = -1;
		uint64_t uavCounterOffsetInBytes = -1;
	}param;

public:

	RWPingPongBufferDescription
	(
		UINT structureByte_,
		UINT numElements_,
		UINT firstElement_,
		uint64_t uavCounterOffsetInBytes_
	);

	//パラーメーターチェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;

	//View生成
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const override;
	virtual D3D12_UNORDERED_ACCESS_VIEW_DESC CreateUAV_Desc()const override;

};


