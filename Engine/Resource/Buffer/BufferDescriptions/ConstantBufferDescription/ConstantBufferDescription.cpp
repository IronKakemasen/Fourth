#include "PreCompileHeader.h"
#include "ConstantBufferDescription.h"

ConstantBufferDescription::ConstantBufferDescription
(
	UINT sizeInByte_
) :BufferDescriptionBehavior({ D3D12_RESOURCE_STATE_GENERIC_READ,D3D12_RESOURCE_STATE_GENERIC_READ })
{
	param.sizeInByte = (sizeInByte_ + 255) & ~255;
}


void ConstantBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (param.sizeInByte == 0) errorMess += "[sizeInByte]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です","ConstantBufferDescription.cpp");

}

D3D12_RESOURCE_DESC ConstantBufferDescription::CreateResourceDesc()const
{
	D3D12_RESOURCE_DESC resourceDesc = {};

	resourceDesc.Width = param.sizeInByte;

	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	return resourceDesc;
}

D3D12_HEAP_PROPERTIES ConstantBufferDescription::CreateHeapProperties()const
{
	D3D12_HEAP_PROPERTIES properties = {};
	properties.Type = D3D12_HEAP_TYPE_UPLOAD;

	return properties;

}

