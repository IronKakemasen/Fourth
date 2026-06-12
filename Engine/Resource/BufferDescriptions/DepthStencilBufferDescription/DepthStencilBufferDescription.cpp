#include "PreCompileHedder.h"
#include "DepthStencilBufferDescription.h"


void DepthStencilBufferDescription::CheckRequirementsFilled() const
{

}

D3D12_RESOURCE_DESC DepthStencilBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = width;
	resourceDesc.Height = height;
	resourceDesc.Alignment = 0;
	//mipmapの数
	resourceDesc.MipLevels = 1;
	//奥行or配列Textureの配列数
	resourceDesc.DepthOrArraySize = 1;
	//depthstencilとして利用可能なフォーマット
	resourceDesc.Format = format;
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
	dsvDesc.Format = format;
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

	clearValue.DepthStencil.Depth = clearColor;
	clearValue.Format = format;

	return clearValue;
}
