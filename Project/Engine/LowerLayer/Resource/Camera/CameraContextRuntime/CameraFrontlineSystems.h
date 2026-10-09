#pragma once
#include "../CameraContext.h"
#include "CameraSocket.h"

class CameraBehavior;

class CameraContext::CameraFrontlineSystems
{
	//カメラの登録を行う
	class CameraRegister;
	//そのシーンに存在するカメラのライブラリ
	class CameraLibrary;

public:

	CameraFrontlineSystems(NexusFieldProof proof_);
	~CameraFrontlineSystems();

	//カメラの登録
	void RegisterCamera
	(
		std::unique_ptr<CameraBehavior>&& camera_,
		CameraSocket dstCameraSocket_,
		std::string const& name_
	);

	//カメラ接続の変更
	void ChangeCamera(std::string const& to_, CameraSocket dstSocket_);

	//カメラのアップデート
	//socketMapにあるカメラのアップデートを呼ぶ。バッチングは別機関で行う
	void RunCameraUpdate();

private:

	std::unique_ptr<CameraLibrary> cameraLibrary;
	std::unordered_map<CameraSocket, CameraBehavior*> socketMap;
};

