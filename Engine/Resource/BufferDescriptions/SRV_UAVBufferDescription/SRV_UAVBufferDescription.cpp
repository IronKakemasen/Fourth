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
	
	//uav生成フラグがあるときはほかのもチェック
	if (resourceFlag & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS)
	{
		if (uavFlags == D3D12_BUFFER_UAV_FLAG_notDefined) errorMess += "[uavFlags]";
		if (uavCounterOffsetInBytes == -1) errorMess += "[uavCounterOffsetInBytes]";
	}

	ErrorMessageOutput::Assert::DetectError((errorMess.length() == 0), errorMess + "の情報が未設定です", "SRV_UAVBufferDescription.cpp");
}