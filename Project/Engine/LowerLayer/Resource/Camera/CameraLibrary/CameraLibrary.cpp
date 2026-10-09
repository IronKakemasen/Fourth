#include "PreCompileHeader.h"
#include "CameraLibrary.h"
#include "../CameraStructrue/CameraBehavior.h"


CameraContext::CameraLibrary::CameraLibrary(NexusFieldProof proof_)
{

}


CameraContext::CameraLibrary::~CameraLibrary()
{

}

void CameraContext::CameraLibrary::Import
(
	Local_ImportLicence const& licence_,
	std::unique_ptr<CameraBehavior>&& cameraUnique_,
	std::string const& name_
)
{
	ErrorMessageOutput::Assert::DetectError
	(
		cameraLib.find(name_) == cameraLib.end(),
		name_ + "このカメラ名は重複してるからだめ",
		"CameraLibrary.h"
	);

	Logger::Log("Import: " + name_, "CameraLibrary.cpp");

	allCameraPtr.emplace_back(cameraUnique_.get());
	cameraLib[name_] = std::move(cameraUnique_);
}

std::vector<CameraBehavior*> const& CameraContext::CameraLibrary::WatchLibrary()const
{
	return allCameraPtr;
}

