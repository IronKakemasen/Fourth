#pragma once
#include "../CameraFrontlineSystems.h"

class CameraBehavior;

class CameraContext::CameraFrontlineSystems::CameraController
{
public:

	CameraController(NexusFieldProof proof_);

	void Update();

	//ソケットに接続するカメラを変える
	template<CameraSocket dstSocket_>
	void Connect(CameraBehavior* dstCamera_)
	{
		socketMap[dstSocket_] = dstCamera_;
	}

	//ソケットに接続されているカメラ(描画のために使用しているカメラ)の更新処理を呼ぶ
	void RunCamera();

private:

	//現在の接続しているカメラ
	std::unordered_map<CameraSocket, CameraBehavior*> socketMap;

};

