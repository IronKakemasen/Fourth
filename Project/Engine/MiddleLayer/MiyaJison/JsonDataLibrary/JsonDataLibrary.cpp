#include "PreCompileHeader.h"
#include "JsonDataLibrary.h"



void MiyaJison::DataLibrary::Import(HandleLicence licence_, std::string fileName_, nlohmann::json jsonData_)
{
	lib[fileName_] = jsonData_;
	Logger::Log("Import: " + fileName_, "JsonDataLibrary.h");
}


const nlohmann::json& MiyaJison::DataLibrary::Export(HandleLicence licence_, std::string fileName_)const
{
	ErrorMessageOutput::Assert::DetectError
	(
		lib.find(fileName_) != lib.end(),
		"んなファイル無いんだわ",
		"JsonDataLibrary.cpp"
	);

	return lib.at(fileName_);
}
