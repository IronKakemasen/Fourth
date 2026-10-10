#include "PreCompileHeader.h"
#include "CameraDataBatcher.h"


CameraContext::CameraDataBatcher::CameraDataBatcher(NexusFieldProof proof_)
{

}


void CameraContext::CameraDataBatcher::ImportCameraDataArrBufferID(NexusFieldProof prooof_, BufferUniqueID id_)
{
	cameraDataArrBufferID = id_;
	Logger::Log("Catched ID!" + std::to_string(id_), "CameraDataBatcher.cpp");
}
