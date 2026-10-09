#pragma once
#include "../../CameraContext.h"
#include "../CameraSocket.h"

class CameraBehavior;

class CameraContext::CameraController
{
public:
	CameraController(NexusFieldProof proof_);



private:

	//現在の接続しているカメラ
	std::unordered_map<CameraSocket, CameraBehavior*> socketMap;

};

