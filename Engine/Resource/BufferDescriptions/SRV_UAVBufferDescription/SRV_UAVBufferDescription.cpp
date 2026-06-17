#include "PreCompileHeader.h"
#include "SRV_UAVBufferDescription.h"


SRV_UAVBufferDescription::SRV_UAVBufferDescription
(
	UINT structureByte_,
	UINT numElements_,
	UINT firstElement_,
	D3D12_RESOURCE_FLAGS resourceFlag_,
	D3D12_HEAP_TYPE heapType_,
	D3D12_BUFFER_SRV_FLAGS srvFlags_,
	D3D12_BUFFER_UAV_FLAGS uavFlags_,
	uint64_t uavCounterOffsetInBytes_,
	ResourceStates initialStates_
) :BufferDescriptionBehavior(initialStates_)
{
	param.structureByte = structureByte_;
	param.numElements = numElements_;
	param.firstElement = firstElement_;
	param.resourceFlag = resourceFlag_;
	param.heapType = heapType_;
	param.srvFlags = srvFlags_;
	param.uavFlags = uavFlags_;
	param.uavCounterOffsetInBytes = uavCounterOffsetInBytes_;
}


void SRV_UAVBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (param.structureByte == 0)errorMess += "[structureByte]";
	if (param.numElements == 0)errorMess += "[numElements]";
	if (param.firstElement == -1) errorMess += "[firstElement]";
	if (param.srvFlags == D3D12_BUFFER_SRV_FLAG_notDefined) errorMess += "[srvFlags]";
	if (param.resourceFlag == D3D12_RESOURCE_FLAG_Error_Detection) errorMess += "[resourceFlag]";
	if (param.heapType == D3D12_HEAP_TYPE_notDefined) errorMess += "[heapType]";

	//uav生成フラグがあるときはチェック
	if ((param.resourceFlag & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS) > 0 )
	{
		if (param.uavFlags == D3D12_BUFFER_UAV_FLAG_notDefined) errorMess += "[uavFlags]";
		if (param.uavCounterOffsetInBytes == -1) errorMess += "[uavCounterOffsetInBytes]";
	}

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "SRV_UAVBufferDescription.cpp");
}

D3D12_RESOURCE_DESC SRV_UAVBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = param.numElements * param.structureByte;
	resourceDesc.Flags = param.resourceFlag;

	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	return resourceDesc;
}

D3D12_SHADER_RESOURCE_VIEW_DESC SRV_UAVBufferDescription::CreateSRV_Desc()const
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Buffer.NumElements = param.numElements;
	srvDesc.Buffer.StructureByteStride = param.structureByte;
	srvDesc.Buffer.Flags = param.srvFlags;
	srvDesc.Buffer.FirstElement = param.firstElement;

	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;

	return srvDesc;
}

D3D12_HEAP_PROPERTIES SRV_UAVBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};

	properties.Type = param.heapType;

	return properties;

}


D3D12_UNORDERED_ACCESS_VIEW_DESC SRV_UAVBufferDescription::CreateUAV_Desc()const
{
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};

	return uavDesc;
}

