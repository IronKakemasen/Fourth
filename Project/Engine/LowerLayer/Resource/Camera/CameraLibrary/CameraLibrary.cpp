#include "PreCompileHeader.h"
#include "CameraLibrary.h"
#include "../CameraStructrue/CameraBehavior.h"


namespace
{
	auto const fileName = "CameraLibrary.cpp";
}

CameraContext::CameraFrontlineSystems::CameraLibrary::CameraLibrary(NexusFieldProof proof_)
{

}


CameraContext::CameraFrontlineSystems::CameraLibrary::~CameraLibrary()
{

}

void CameraContext::CameraFrontlineSystems::CameraLibrary::Import
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

CameraBehavior* CameraContext::CameraFrontlineSystems::CameraLibrary::Export(std::string const& name_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		cameraLib.find(name_) != cameraLib.end(),
		name_ + "こんな名前のカメラは登録されていません",
		fileName
	);

	return cameraLib[name_].get();

}


