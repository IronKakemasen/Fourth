#pragma once
#include "../BufferDescriptionBehavior.h"


//DepthStencilBuffer
struct DepthStencilBufferDescription final : public BufferDescriptionBehavior, IDSV_Assembler
{
private:

	struct Param
	{
		UINT width{};
		UINT height{};
		FLOAT clearColor = -1.0f;
		DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_Error_Detection;

	}param;

public:

	DepthStencilBufferDescription
	(
		UINT width_,
		UINT height_,
		FLOAT clearColor_,
		DXGI_FORMAT format_,
		ResourceStates initialStates_
	);

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

	inline const Param& WatchParam()
	{
		return param;
	}

};


