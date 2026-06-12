#pragma once
#include "../IBufferDescription.h"


//DepthStencilBuffer
struct DepthStencilBufferDescription final : public IBufferDescription, IDSV_Assembler
{
	UINT width{};
	UINT height{};
	FLOAT clearColor = -1.0f;
	DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_Error_Detection;

	//要項チェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;

	//DSV生成
	virtual D3D12_DEPTH_STENCIL_VIEW_DESC CreateDSVDesc()const override;
	//クリアバリュー
	virtual D3D12_CLEAR_VALUE WatchClearValue() const override;

};


