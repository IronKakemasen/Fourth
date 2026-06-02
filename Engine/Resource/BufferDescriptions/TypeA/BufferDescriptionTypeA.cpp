#include "PreCompileHedder.h"
#include "BufferDescriptionTypeA.h"

void BufferDescriptionTypeA::CheckRequirementsFilled()
{
	std::string errorMess{};

	if (sizeInByte > 0) errorMess += "[sizeInByte]";

	ErrorMessageOutput::Assert::DetectError((errorMess.length() > 0), errorMess + "の情報が未設定です","BufferDescriptionTypeA.cpp");

}