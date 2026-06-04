#pragma once
#include "../BufferDescriptionBehavior.h"


//ColorバッファやSRVバッファなどのちょい複雑なバッファ
struct ColorBufferDescription final : public BufferDescriptionBehavior
{
	float clearColor[4] = { 9,9,9,9 };
	float width{};
	float height{};
	D3D12_RESOURCE_STATES initialState =  D3D12_RESOURCE_STATE_Error_Detection;
	D3D12_RESOURCE_FLAGS flag = D3D12_RESOURCE_FLAG_Error_Detection;
	DXGI_FORMAT format = DXGI_FORMAT_Error_Detection;

public:
	virtual void CheckRequirementsFilled() const override;

};


