#pragma once
#include "../CameraFrontlineSystems.h"

class CameraBehavior;

class CameraContext::CameraFrontlineSystems::CameraController
{
public:

	CameraController(NexusFieldProof proof_);

	std::unordered_map<CameraSocket, CameraBehavior*> const& Update();

	//ソケットに接続するカメラを接続する
	template<CameraSocket dstSocket_>
	void Connect(CameraBehavior* dstCamera_)
	{
		socketMap[dstSocket_] = dstCamera_;
	}


private:

	//ソケットに接続されているカメラ(描画のために使用しているカメラ)の更新処理を呼ぶ
	std::unordered_map<CameraSocket, CameraBehavior*> const& RunCamera();

	//現在の接続しているカメラ
	std::unordered_map<CameraSocket, CameraBehavior*> socketMap;

};

