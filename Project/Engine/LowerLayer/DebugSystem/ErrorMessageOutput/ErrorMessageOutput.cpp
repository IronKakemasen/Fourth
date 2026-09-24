
#include "ErrorMessageOutput.h"
#include "../../../Utility/StringConverter/StringConverter.h"


void ErrorMessageOutput::Abort::OutputError(const std::string& message_ , const std::string& fileName_)
{
	Abort::DetectError(false, message_, fileName_);
}

void ErrorMessageOutput::Abort::DetectError(bool positiveResult_, const std::string& message_, const std::string& fileName_)
{
	if (!positiveResult_)
	{
		std::string outputMes = message_ + "\nFileName : " + fileName_;

		MessageBoxW(nullptr, StringConverter::ConvertString(outputMes).c_str(), L"Fatal Error", MB_OK | MB_ICONERROR);
		std::abort();
	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ErrorMessageOutput::Assert::DetectError(bool positiveResult_, const std::string& message_, const std::string& fileName_)
{
	if (!positiveResult_)
	{
		std::string outputMes = message_ + "\nFileName : " + fileName_;
		MessageBoxW(nullptr, StringConverter::ConvertString(outputMes).c_str(), L"Fatal Error", MB_OK | MB_ICONERROR);
		assert(false);
	}
}

void ErrorMessageOutput::Assert::OutputError(const std::string& message_, const std::string& fileName_)
{
	Assert::DetectError(false, message_, fileName_);
}

