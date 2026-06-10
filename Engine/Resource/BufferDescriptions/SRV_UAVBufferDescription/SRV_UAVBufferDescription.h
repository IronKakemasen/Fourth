#pragma once
#include "../BufferDescriptionBehavior.h"


//StructuredBuffer（読み込み専用やRWStructuredBuffer（読み書き汎用）のDescription
struct SRV_UAVBufferDescription :public BufferDescriptionBehavior
{
	//そのデータ型のサイズ
	UINT structureByte{};
	//要素数
	UINT numElements{};
	UINT firstElement = -1;

	D3D12_RESOURCE_FLAGS resourceFlag = D3D12_RESOURCE_FLAG_Error_Detection;

	D3D12_HEAP_TYPE heapType = D3D12_HEAP_TYPE_notDefined;

	D3D12_BUFFER_SRV_FLAGS srvFlags = D3D12_BUFFER_SRV_FLAG_notDefined;
	//UAVのビューを作るのであれば
	D3D12_BUFFER_UAV_FLAGS uavFlags = D3D12_BUFFER_UAV_FLAG_notDefined;
	// カウンターバッファ用のオフセット
	uint64_t uavCounterOffsetInBytes = -1; 

	virtual void CheckRequirementsFilled() const override;

};


