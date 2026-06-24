#pragma once
#include "../BufferDescriptionBehavior.h"


//DepthStencilBuffer
struct DepthStencilBufferDescription final : public BufferDescriptionBehavior, IDSV_Assembler, ISRV_Assembler
{
private:

	//フォーマットは基本これかな
	//DXGI_FORMAT_D24_UNORM_S8_UINT
	//DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	struct Param
	{
		UINT width{};
		UINT height{};
		FLOAT clearColor = -1.0f;
		DXGI_FORMAT dsvFormat = DXGI_FORMAT::DXGI_FORMAT_Error_Detection;
		DXGI_FORMAT srvFormat = DXGI_FORMAT::DXGI_FORMAT_Error_Detection;

	}param;

public:

	DepthStencilBufferDescription
	(
		UINT width_,
		UINT height_,
		FLOAT clearColor_,
		DXGI_FORMAT dsvFormat_,
		DXGI_FORMAT srvFormat_
	);

	//要項チェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;

	//DSVDesc生成
	virtual D3D12_DEPTH_STENCIL_VIEW_DESC CreateDSVDesc()const override;
	//SRVDesc生成
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const override;
	//クリアバリュー
	virtual D3D12_CLEAR_VALUE WatchClearValue() const override;

	inline const Param& WatchParam()
	{
		return param;
	}

private:

	DXGI_FORMAT ConductTypelessFormat()const;

};


