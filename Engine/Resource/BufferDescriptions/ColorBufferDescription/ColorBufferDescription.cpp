#include "PreCompileHedder.h"
#include "ColorBufferDescription.h"

ColorBufferDescription::ColorBufferDescription
(
	float clearColors_[4],
	UINT width_,
	UINT height_,
	D3D12_RESOURCE_FLAGS flag_,
	DXGI_FORMAT format_,
	D3D12_RESOURCE_STATES initialState_
) : BufferDescriptionBehavior(initialState_)
{
	for (int i = 0;i < 4;++i) param.clearColor[i] = clearColors_[i];
	param.width = width_;
	param.height = height_;
	param.flag = flag_;
	param.format = format_;
}



void ColorBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	for (int i = 0;i < 4;++i)
	{
		if (param.clearColor[i] > 1)
		{
			errorMess += "[color]";
			break;
		}
	}

	if (param.width == 0)errorMess += "[width]";
	if (param.height == 0)errorMess += "[height]";
	if (param.format == DXGI_FORMAT_Error_Detection) errorMess += "[format]";
	if (param.flag == D3D12_RESOURCE_FLAG_Error_Detection) errorMess += "[flag]";
	if(initialState == D3D12_RESOURCE_STATE_Error_Detection) errorMess += "[initialState]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "ColorBufferDescription.cpp");

}

D3D12_HEAP_PROPERTIES ColorBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};
	//vramの奥
	properties.Type = D3D12_HEAP_TYPE_DEFAULT;

	return properties;
}

D3D12_RESOURCE_DESC ColorBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	//幅
	resourceDesc.Width = param.width;
	//高さ
	resourceDesc.Height = param.height;
	//mipmapの数
	resourceDesc.MipLevels = 1;
	//奥行orTextureの配列数
	resourceDesc.DepthOrArraySize = 1;
	//Textureのformat
	resourceDesc.Format = param.format;
	//サンプリングカウント。１固定
	resourceDesc.SampleDesc.Count = 1;
	//テクスチャの次元数。2
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = param.flag;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	return resourceDesc;
}

D3D12_CLEAR_VALUE ColorBufferDescription::WatchClearValue() const
{
	D3D12_CLEAR_VALUE clearValue = {};
	for (int i = 0; i < 4;++i) clearValue.Color[i] = param.clearColor[i];

	return clearValue;
}

D3D12_RENDER_TARGET_VIEW_DESC ColorBufferDescription::CreateRTV_Desc()const
{
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	//出力結果をSRGBに変換する
	rtvDesc.Format = param.format;
	//2Dテクスチャとして書き込む
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.PlaneSlice = 0;
	rtvDesc.Texture2D.MipSlice = 0;

	return rtvDesc;
}

D3D12_SHADER_RESOURCE_VIEW_DESC ColorBufferDescription::CreateSRV_Desc()const
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = param.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(1);

	return srvDesc;
}
