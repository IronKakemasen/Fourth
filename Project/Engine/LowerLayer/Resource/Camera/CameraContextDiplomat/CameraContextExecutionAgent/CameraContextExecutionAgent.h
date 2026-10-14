#pragma once
#include "../../CameraContext.h"
#include "../../CameraContextRuntime/CameraSocket.h"

class CameraBehavior;

class CameraContext::ExecutionAgent
{

public:

	struct SceneContextProof;

	ExecutionAgent
	(
		NexusFieldProof proof_,
		FrontlineSystemsDispatcher& frontlineSystemsDispatcher_,
		CameraDataBatcher& cameraDataBatcher_

	);

	//シーンにカメラのシステムを渡す
	CameraFrontlineSystems& DispatchFrontlineSystems(SceneContextProof proof_);

	//カメラデータのバッチングを行う
	void BatchCameraData
	(
		SceneContextProof proof_,
		std::unordered_map<CameraSocket, CameraBehavior*> const& usingCamera_,
		UINT const frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	FrontlineSystemsDispatcher& frontlineSystemsDispatcher;
	CameraDataBatcher& cameraDataBatcher;

};

