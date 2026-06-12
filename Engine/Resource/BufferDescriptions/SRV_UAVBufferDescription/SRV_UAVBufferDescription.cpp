#include "PreCompileHedder.h"
#include "SRV_UAVBufferDescription.h"

void SRV_UAVBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (structureByte == 0)errorMess += "[structureByte]";
	if (numElements == 0)errorMess += "[numElements]";
	if (firstElement == -1) errorMess += "[firstElement]";
	if (srvFlags == D3D12_BUFFER_SRV_FLAG_notDefined) errorMess += "[srvFlags]";
	if (resourceFlag == D3D12_RESOURCE_FLAG_Error_Detection) errorMess += "[resourceFlag]";
	if (heapType == D3D12_HEAP_TYPE_notDefined) errorMess += "[heapType]";
	//if (initialState == D3D12_RESOURCE_STATE_Error_Detection) errorMess += "[initialState]";

	//uav生成フラグがあるときはほかのもチェック
	if ((resourceFlag & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS) > 0 )
	{
		if (uavFlags == D3D12_BUFFER_UAV_FLAG_notDefined) errorMess += "[uavFlags]";
		if (uavCounterOffsetInBytes == -1) errorMess += "[uavCounterOffsetInBytes]";
	}

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "SRV_UAVBufferDescription.cpp");
}

D3D12_RESOURCE_DESC SRV_UAVBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = numElements * structureByte;
	resourceDesc.Flags = resourceFlag;

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

	srvDesc.Buffer.NumElements = numElements;
	srvDesc.Buffer.StructureByteStride = structureByte;
	srvDesc.Buffer.Flags = srvFlags;
	srvDesc.Buffer.FirstElement = firstElement;

	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;

	return srvDesc;
}

D3D12_HEAP_PROPERTIES SRV_UAVBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};

	properties.Type = heapType;

	return properties;

}


D3D12_UNORDERED_ACCESS_VIEW_DESC SRV_UAVBufferDescription::CreateUAV_Desc()const
{
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};

	return uavDesc;
}

