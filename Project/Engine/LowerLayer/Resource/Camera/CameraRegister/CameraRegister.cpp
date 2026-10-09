#include "PreCompileHeader.h"
#include "CameraRegister.h"
#include "../CameraLibrary/CameraLibrary.h"


CameraContext::CameraRegister::CameraRegister
(
	NexusFieldProof proof_,
	CameraLibrary& cameraLibrary_
):cameraLibrary(cameraLibrary_)
{

}

void CameraContext::CameraRegister::Register(std::unique_ptr<CameraBehavior>&& camera_,std::string const& name_)
{
	cameraLibrary.Import(CameraLibrary::Local_ImportLicence{}, std::move(camera_), name_);
}

