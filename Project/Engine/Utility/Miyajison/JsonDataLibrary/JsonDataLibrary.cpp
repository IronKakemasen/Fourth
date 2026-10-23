#include "PreCompileHeader.h"
#include "JsonDataLibrary.h"



void Miyajison::DataLibrary::Import
(
	HandleLicence licence_,
	std::string const& fileName_,
	nlohmann::json const& jsonData_,
	std::string const& filePath_
) 
{
#ifdef _DEBUG
	ErrorMessageOutput::Assert::DetectError
	(
		lib.find(fileName_) == lib.end(),
		fileName_ + "ファイル名被ってる",
		"DataLibrary.cpp"
	);
#endif // DEBUG

	lib[fileName_] = jsonData_;
	fileName_Path[fileName_] = filePath_;

	Logger::Log("Import: " + fileName_, "JsonDataLibrary.cpp");
}

std::string const& Miyajison::DataLibrary::ToPath(std::string const& fileName_)
{
#ifdef _DEBUG

	ErrorMessageOutput::Assert::DetectError
	(
		lib.find(fileName_) != lib.end(),
		fileName_ + "\nんなファイル無いんだわ",
		"JsonDataLibrary.cpp"
	);

#endif // DEBUG

	return fileName_Path[fileName_];
}


nlohmann::json& Miyajison::DataLibrary::Export(HandleLicence licence_, std::string const& fileName_)
{
	//さすがにジェーソンファイルが無いのはデバッグで確認するべきなので
#ifdef _DEBUG
	
	ErrorMessageOutput::Assert::DetectError
	(
		lib.find(fileName_) != lib.end(),
		fileName_ + "\nんなファイル無いんだわ",
		"JsonDataLibrary.cpp"
	);

#endif // DEBUG

	return lib[fileName_];
}
