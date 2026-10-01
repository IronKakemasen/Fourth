#include "PreCompileHeader.h"
#include "JsonDataLibrary.h"



void Miyajison::DataLibrary::Import(HandleLicence licence_, std::string const& fileName_, nlohmann::json const& jsonData_)
{
	lib[fileName_] = jsonData_;
	Logger::Log("Import: " + fileName_, "JsonDataLibrary.h");
}


const nlohmann::json& Miyajison::DataLibrary::Export(HandleLicence licence_, std::string const& fileName_)const
{
	ErrorMessageOutput::Assert::DetectError
	(
		lib.find(fileName_) != lib.end(),
		fileName_ + "\nんなファイル無いんだわ",
		"JsonDataLibrary.cpp"
	);

	return lib.at(fileName_);
}
