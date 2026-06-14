#pragma once
#include "../BufferDescriptionBehavior.h"


//StructuredBuffer（読み込み専用やRWStructuredBuffer（読み書き汎用）のDescription
struct SRV_UAVBufferDescription final :public BufferDescriptionBehavior, ISRBufferAssembler, IUAV_Assembler
{
private:
	struct Param
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
	}param;

public:

	SRV_UAVBufferDescription
	(
		UINT structureByte_,
		UINT numElements_,
		UINT firstElement_,
		D3D12_RESOURCE_FLAGS resourceFlag_,
		D3D12_HEAP_TYPE heapType_,
		D3D12_BUFFER_SRV_FLAGS srvFlags_,
		D3D12_BUFFER_UAV_FLAGS uavFlags_,
		uint64_t uavCounterOffsetInBytes_,
		D3D12_RESOURCE_STATES initialState_
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


