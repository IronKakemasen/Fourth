#include "PreCompileHedder.h"
#include "ColorBufferDescription.h"

void ColorBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	for (int i = 0;i < 4;++i)
	{
		if (clearColor[1] > 1)
		{
			errorMess += "[sizeInByte]";
			break;
		}
	}

	if (width == 0.0f)errorMess += "[width]";
	if (height == 0.0f)errorMess += "[height]";
	if(format == DXGI_FORMAT_Error_Detection) errorMess += "[format]";
	if (flag == D3D12_RESOURCE_FLAG_Error_Detection) errorMess += "[flag]";
	if(initialState == D3D12_RESOURCE_STATE_Error_Detection) errorMess += "[initialState]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() > 0), errorMess + "の情報が未設定です", "BufferDescriptionTypeB.cpp");

}