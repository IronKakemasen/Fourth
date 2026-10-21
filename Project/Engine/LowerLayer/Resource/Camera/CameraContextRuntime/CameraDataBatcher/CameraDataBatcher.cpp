#include "PreCompileHeader.h"
#include "CameraDataBatcher.h"


//外部
#include "../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include "../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"

#include "../../CameraStructure/CameraBehavior.h"

CameraContext::CameraDataBatcher::CameraDataBatcher(NexusFieldProof proof_)
{

}


void CameraContext::CameraDataBatcher::ImportCameraDataArrBufferID(NexusFieldProof prooof_, BufferUniqueID id_)
{
	cameraDataArrBufferID = id_;
	Logger::Log("Catched ID!" + std::to_string(id_), "CameraDataBatcher.cpp");
}

void CameraContext::CameraDataBatcher::Batch
(
	AgentKey key_,
	std::unordered_map<CameraSocket, CameraBehavior*> const& usingCamera_,
	UINT const frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//bufferDispatcherを借りる
	auto toolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence{};
	auto& bufferDispacher = *toolLender->Lend<BufferContext::BufferDispatcher>(licence);

	auto* dstBuffer = static_cast<UploadStructuredBuffer*>(bufferDispacher.Dispatch(cameraDataArrBufferID));
	for (auto const& [socket, camera] : usingCamera_)
	{
		dstBuffer->WriteElement(frameIndex_, camera->OutCameraData(), UINT(socket));
	}

}
