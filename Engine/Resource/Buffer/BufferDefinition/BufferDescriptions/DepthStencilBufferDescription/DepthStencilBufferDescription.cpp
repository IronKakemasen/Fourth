#include "PreCompileHeader.h"
#include "DepthStencilBufferDescription.h"


DepthStencilBufferDescription::DepthStencilBufferDescription
(
	UINT width_,
	UINT height_,
	FLOAT clearColor_,
	DXGI_FORMAT dsvFormat_,
	DXGI_FORMAT srvFormat_,
	ProjectConfig::Render::NumBuffer numBuffer_
):BufferDescriptionBehavior(D3D12_RESOURCE_STATE_DEPTH_WRITE, numBuffer_)
{
	param.width = width_;
	param.height = height_;
	param.clearColor = clearColor_;
	param.dsvFormat = dsvFormat_;
	param.srvFormat = srvFormat_;

}

void DepthStencilBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (param.width == 0)errorMess += "[width]";
	if (param.height == 0)errorMess += "[height]";
	if (param.srvFormat == DXGI_FORMAT_Error_Detection) errorMess += "[SRVformat]";
	if (param.dsvFormat == DXGI_FORMAT_Error_Detection) errorMess += "[DSVformat]";
	if (param.clearColor == -1 ) errorMess += "[clearColor]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "DepthStencilBufferDescription.cpp");
}

D3D12_SHADER_RESOURCE_VIEW_DESC DepthStencilBufferDescription::CreateSRV_Desc()const
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = param.srvFormat;

	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(1);

	return srvDesc;
}


D3D12_RESOURCE_DESC DepthStencilBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = param.width;
	resourceDesc.Height = param.height;
	
	resourceDesc.Alignment = 0;
	//mipmapの数
	resourceDesc.MipLevels = 1;
	//奥行or配列Textureの配列数
	resourceDesc.DepthOrArraySize = 1;
	//SRV併用の可能性もある
	resourceDesc.Format = ConductTypelessFormat();
	//サンプリングカウント1固定
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	//DepthStencilとして使う通知
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	return resourceDesc;
}


D3D12_DEPTH_STENCIL_VIEW_DESC DepthStencilBufferDescription::CreateDSVDesc()const
{
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

	//format。基本的にはリソースに合わせる
	dsvDesc.Format = param.dsvFormat;
	
	//2DTexture
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

	return dsvDesc;
}

D3D12_HEAP_PROPERTIES DepthStencilBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};

	properties.Type = D3D12_HEAP_TYPE_DEFAULT;
	properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	properties.CreationNodeMask = 1;
	properties.VisibleNodeMask = 1;

	return properties;
}

D3D12_CLEAR_VALUE DepthStencilBufferDescription::WatchClearValue() const
{
	D3D12_CLEAR_VALUE clearValue = {};

	clearValue.DepthStencil.Depth = param.clearColor;
	clearValue.Format = param.dsvFormat;
	clearValue.DepthStencil.Stencil = 0;

	return clearValue;
}


DXGI_FORMAT DepthStencilBufferDescription::ConductTypelessFormat()const
{
	DXGI_FORMAT typelessFormat{};

	if (param.dsvFormat == DXGI_FORMAT_D32_FLOAT) typelessFormat = DXGI_FORMAT_R32_TYPELESS;

	else if (param.dsvFormat == DXGI_FORMAT_D24_UNORM_S8_UINT) typelessFormat = DXGI_FORMAT_R24G8_TYPELESS;

	else if (param.dsvFormat == DXGI_FORMAT_D32_FLOAT_S8X24_UINT) typelessFormat = DXGI_FORMAT_R32G8X24_TYPELESS;

	else typelessFormat = param.dsvFormat;

	return typelessFormat;
}

