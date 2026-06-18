#pragma once
#include "../BufferDescriptionBehavior.h"


//Colorバッファ
struct ColorBufferDescription final : public BufferDescriptionBehavior,IRTBufferAssembler, ISRV_Assembler
{
private:

	struct Param
	{
		float clearColor[4] = { 9,9,9,9 };
		UINT width{};
		UINT height{};
		D3D12_RESOURCE_FLAGS flag = D3D12_RESOURCE_FLAG_Error_Detection;
		DXGI_FORMAT format = DXGI_FORMAT_Error_Detection;

	}param;

public:

	ColorBufferDescription
	(
		float clearColors_[4],
		UINT width_,
		UINT height_,
		D3D12_RESOURCE_FLAGS flag_,
		DXGI_FORMAT format_,
		ResourceStates initialStates_
	);
	
	//要項チェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//RTV生成
	virtual D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc()const override;
	//SRV生成
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const override;
	//クリアバリュー
	virtual D3D12_CLEAR_VALUE WatchClearValue() const override;

	inline const Param& WatchParam()
	{
		return param;
	}

};


