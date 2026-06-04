#include "PreCompileHedder.h"
#include "ConstantBufferDescription.h"

void ConstantBufferDescription::CheckRequirementsFilled() const
{
	std::string errorMess{};

	if (sizeInByte > 0) errorMess += "[sizeInByte]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() > 0), errorMess + "の情報が未設定です","ConstantBufferDescription.cpp");

}