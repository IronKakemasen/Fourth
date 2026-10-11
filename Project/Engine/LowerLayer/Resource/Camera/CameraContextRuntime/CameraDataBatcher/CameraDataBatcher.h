#pragma once
#include "../../CameraContext.h"
#include "../CameraSocket.h"


class CameraBehavior;

class CameraContext::CameraDataBatcher
{
public:

	CameraDataBatcher(NexusFieldProof proof_);

	//cameraDataのバッチングを行う。どれを行うかは、SceneControllerの所持する情報から判別
	//代行してもらう
	void Batch
	(
		AgentKey key_,
		std::unordered_map<CameraSocket, CameraBehavior*> const& usingCamera_,
		UINT const frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	void ImportCameraDataArrBufferID(NexusFieldProof prooof_, BufferUniqueID id_);

private:

	//カメラデータ配列のバッファID
	BufferUniqueID cameraDataArrBufferID;

};

