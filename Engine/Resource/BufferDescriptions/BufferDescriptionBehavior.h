#pragma once

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//GPUバッファ生成、view生成に必要な情報をまとめてある。
//CB
//Colorバッファ
//sr_uaバッファ
//depthBuffer

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//バッファのディスクリプション共通
struct BufferDescriptionBehavior
{
protected :
	using ResourceStates = std::array<D3D12_RESOURCE_STATES, ProjectConfig::Render::kRequiredGPUBufferSum>;

public:
	BufferDescriptionBehavior(ResourceStates initialStates_);

	BufferDescriptionBehavior() = default;

	virtual void CheckRequirementsFilled() const = 0;
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const = 0;
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const = 0;

	std::array<D3D12_RESOURCE_STATES, ProjectConfig::Render::kRequiredGPUBufferSum> initialStates =
	{ D3D12_RESOURCE_STATE_Error_Detection };
};


//それぞれの固有のビュー生成インターフェース
struct ISRBufferAssembler 
{
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const = 0; 
};

struct IUAV_Assembler 
{
	virtual D3D12_UNORDERED_ACCESS_VIEW_DESC CreateUAV_Desc()const = 0; 

};

struct IRTBufferAssembler 
{
	virtual D3D12_RENDER_TARGET_VIEW_DESC CreateRTV_Desc()const = 0; 
	virtual D3D12_CLEAR_VALUE WatchClearValue() const = 0;
};

struct IDSV_Assembler 
{
	virtual D3D12_DEPTH_STENCIL_VIEW_DESC CreateDSVDesc()const = 0; 
	virtual D3D12_CLEAR_VALUE WatchClearValue() const = 0;

};

