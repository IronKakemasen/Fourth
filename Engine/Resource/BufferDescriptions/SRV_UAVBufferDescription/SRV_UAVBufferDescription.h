#pragma once
#include "../BufferDescriptionBehavior.h"


class SRV_UAVBufferDescription :public BufferDescriptionBehavior
{
	//そのデータ型のサイズ
	UINT structureByte{};
	//要素数
	UINT numElements{};
	UINT firstElement = -1;

	D3D12_BUFFER_SRV_FLAGS srvFlags = D3D12_BUFFER_SRV_FLAG_notDefined;
	//UAVのビューを作るのであれば
	D3D12_BUFFER_UAV_FLAGS uavFlags = D3D12_BUFFER_UAV_FLAG_notDefined;
	// カウンターバッファ用のオフセット
	uint64_t uavCounterOffsetInBytes = -1; 

public:

	virtual void CheckRequirementsFilled() const override;

};


