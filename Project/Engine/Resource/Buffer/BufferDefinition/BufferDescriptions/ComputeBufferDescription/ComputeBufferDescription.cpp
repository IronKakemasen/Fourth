#include "PreCompileHeader.h"
#include "ComputeBufferDescription.h"


ComputeBufferDescription::ComputeBufferDescription
(
	UINT structureByte_,
	UINT numElements_,
	UINT firstElement_,
	uint64_t uavCounterOffsetInBytes_
) :BufferDescriptionBehavior(D3D12_RESOURCE_STATE_COPY_DEST, ProjectConfig::Render::NumBuffer::kDoubleBuffer)
{
	param.structureByte = structureByte_;
	param.numElements = numElements_;
	param.firstElement = firstElement_;
	param.uavCounterOffsetInBytes = uavCounterOffsetInBytes_;
}


void ComputeBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (param.structureByte == 0)errorMess += "[structureByte]";
	if (param.numElements == 0)errorMess += "[numElements]";
	if (param.firstElement == -1) errorMess += "[firstElement]";
	if (param.uavCounterOffsetInBytes == -1) errorMess += "[uavCounterOffsetInBytes]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "ComputeBufferDescription.cpp");
}

D3D12_RESOURCE_DESC ComputeBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = param.numElements * param.structureByte;

	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	return resourceDesc;
}

D3D12_SHADER_RESOURCE_VIEW_DESC ComputeBufferDescription::CreateSRV_Desc()const
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

D3D12_HEAP_PROPERTIES ComputeBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};

	properties.Type = D3D12_HEAP_TYPE_DEFAULT;

	return properties;
}


D3D12_UNORDERED_ACCESS_VIEW_DESC ComputeBufferDescription::CreateUAV_Desc()const
{
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};

	uavDesc.Buffer.NumElements = param.numElements;
	uavDesc.Buffer.StructureByteStride = param.structureByte;
	uavDesc.Buffer.FirstElement = param.firstElement;
	uavDesc.Buffer.CounterOffsetInBytes = param.uavCounterOffsetInBytes;

	uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE; 
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;               
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;

	return uavDesc;
}

