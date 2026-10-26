#include "PreCompileHeader.h"
#include "CameraLibrary.h"
#include "../../CameraStructure/CameraBehavior.h"


namespace
{
	auto const fileName = "CameraLibrary.cpp";
}

CameraContext::FrontlineSystems::CameraLibrary::CameraLibrary(NexusFieldProof proof_)
{

}


CameraContext::FrontlineSystems::CameraLibrary::~CameraLibrary()
{

}

void CameraContext::FrontlineSystems::CameraLibrary::Import
(
	std::unique_ptr<CameraBehavior>&& cameraUnique_,
	std::string const& name_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		cameraLib.find(name_) == cameraLib.end(),
		name_ + "このカメラ名は同じシーンの中で重複してるからだめ",
		fileName
	);

	Logger::Log("Import: " + name_, fileName);

	cameraLib[name_] = std::move(cameraUnique_);
}

CameraBehavior* CameraContext::FrontlineSystems::CameraLibrary::Export(std::string const& name_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		cameraLib.find(name_) != cameraLib.end(),
		name_ + "こんな名前のカメラは登録されていません",
		fileName
	);

	return cameraLib[name_].get();

}


