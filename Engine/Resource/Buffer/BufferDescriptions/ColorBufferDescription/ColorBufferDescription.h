#pragma once
#include "../BufferDescriptionBehavior.h"


//Colorバッファ
struct ColorBufferDescription final : public BufferDescriptionBehavior,IRTBufferAssembler, ISRV_Assembler
{
private:

	struct Param
	{
		std::array<float, 4> clearColor = { 9,9,9,9 };
		UINT width{};
		UINT height{};
		DXGI_FORMAT format = DXGI_FORMAT_Error_Detection;

	}param;

public:

	ColorBufferDescription
	(
		std::array<float, 4> clearColor_,
		UINT width_,
		UINT height_,
		DXGI_FORMAT format_
	);
	
	//要項チェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//RTVDesc生成
	virtual D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc()const override;
	//SRVDesc生成
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const override;
	//クリアバリュー
	virtual D3D12_CLEAR_VALUE WatchClearValue() const override;

	inline const Param& WatchParam()
	{
		return param;
	}

};


