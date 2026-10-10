#include "PreCompileHeader.h"
#include "CameraContext.h"
#include "CameraContextRuntime/CameraDataBatcher/CameraDataBatcher.h"
#include "CameraFSDispatcher/CameraFSDispatcher.h"
#include "CameraContextDiplomat/CameraContextDiplomat.h"
#include "CameraContextDiplomat/CameraContextExecutionAgent/CameraContextExecutionAgent.h"
#include "CameraBufferCreator/CameraBufferCreator.h"


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


	frontlineSystemsDispatcher = std::make_unique<FrontlineSystemsDispatcher>(proof_);
	Logger::Log("Instantiate: FrontlineSystemsDispatcher", fileName);

	cameraDataBatcher = std::make_unique<CameraDataBatcher>(proof_);
	Logger::Log("Instantiate: FrontlineSystemsDispatcher", fileName);

	CameraBufferCreator::Create(proof_, *cameraDataBatcher, bufferContextDiplomat_);

	diplomat = std::make_unique<CameraContextDiplomat>
	(
		proof_,
		std::make_unique<ExecutionAgent>(proof_, *frontlineSystemsDispatcher)
	);
	Logger::Log("Instantiate: CameraContextDiplomat", fileName);
	Logger::Log("Instantiate: CmdProvider", fileName);


	Logger::End("CameraContext: Constructor");
}

CameraContext::~CameraContext()
{

}
