#pragma once
#include "../../CameraContext.h"


class CameraContext::CameraDataBatcher
{
public:

	CameraDataBatcher(NexusFieldProof proof_);


	void ImportCameraDataArrBufferID(NexusFieldProof prooof_, BufferUniqueID id_);

private:

	//カメラデータ配列のバッファID
	BufferUniqueID cameraDataArrBufferID;

};

