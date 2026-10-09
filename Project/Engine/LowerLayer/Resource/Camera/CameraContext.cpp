#include "PreCompileHeader.h"
#include "CameraContext.h"
#include "CameraLibrary/CameraLibrary.h"
#include "CameraRegister/CameraRegister.h"

namespace
{
	std::string const fileName = "CameraContext.cpp";
}

CameraContext::CameraContext
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	Logger::Entry("CameraContext: Constructor");

	cameraLibrary = std::make_unique<CameraLibrary>(proof_);
	Logger::Log("Instantiate: CameraLibrary", fileName);

	cameraRegister = std::make_unique<CameraRegister>(proof_,*cameraLibrary);
	Logger::Log("Instantiate: CameraRegister", fileName);


	Logger::End("CameraContext: Constructor");
}

CameraContext::~CameraContext()
{

}
