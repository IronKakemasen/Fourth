#pragma once
#include "../IBufferDescription.h"


//ColorバッファやSRVバッファなどのちょい複雑なバッファ
struct ColorBufferDescription final : public IBufferDescription,IRTBufferAssembler
{
	float clearColor[4] = { 9,9,9,9 };
	UINT width{};
	UINT height{};
	D3D12_RESOURCE_STATES initialState =  D3D12_RESOURCE_STATE_Error_Detection;
	D3D12_RESOURCE_FLAGS flag = D3D12_RESOURCE_FLAG_Error_Detection;
	DXGI_FORMAT format = DXGI_FORMAT_Error_Detection;

	//要項チェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//RTV生成
	virtual D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc()const override;
	//クリアバリュー
	virtual D3D12_CLEAR_VALUE WatchClearValue() const override;

};


