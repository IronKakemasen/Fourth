#include "PreCompileHeader.h"
#include "StaticStructuredBufferDescription.h"

StaticStructuredBufferDescription::StaticStructuredBufferDescription
(
	UINT structureByte_,
	UINT numElements_,
	UINT firstElement_
) :BufferDescriptionBehavior(D3D12_RESOURCE_STATE_COPY_DEST, ProjectConfig::Render::NumBuffer::kSingleBuffer)
{
	param.structureByte = structureByte_;
	param.numElements = numElements_;
	param.firstElement = firstElement_;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//パラーメーターチェック
void StaticStructuredBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (param.structureByte == 0)errorMess += "[structureByte]";
	if (param.numElements == 0)errorMess += "[numElements]";
	if (param.firstElement == -1) errorMess += "[firstElement]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "StaticStructuredBufferDescription.cpp");
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//リソースディスクの生成
D3D12_RESOURCE_DESC StaticStructuredBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = param.numElements * param.structureByte;

	//以下固定
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	return resourceDesc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ヒーププロパティの生成
D3D12_HEAP_PROPERTIES StaticStructuredBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};

	//アップロード固定
	properties.Type = D3D12_HEAP_TYPE_DEFAULT;

	return properties;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SRV生成
D3D12_SHADER_RESOURCE_VIEW_DESC StaticStructuredBufferDescription::CreateSRV_Desc()const
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Buffer.NumElements = param.numElements;
	srvDesc.Buffer.StructureByteStride = param.structureByte;
	srvDesc.Buffer.FirstElement = param.firstElement;


	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;

	return srvDesc;

}
