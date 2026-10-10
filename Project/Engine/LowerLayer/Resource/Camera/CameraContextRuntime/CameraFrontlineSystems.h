#pragma once
#include "../CameraContext.h"
#include "CameraSocket.h"

class CameraBehavior;

class CameraContext::CameraFrontlineSystems
{
	//そのシーンに存在するカメラのライブラリ
	class CameraLibrary;
	//カメラのアップデートを読んだり、デバッグ操作などを行う
	class CameraController;

public:

	CameraFrontlineSystems(NexusFieldProof proof_);
	~CameraFrontlineSystems();

	//カメラの登録
	template<CameraSocket dstSocket>
	void RegisterCamera
	(
		std::unique_ptr<CameraBehavior>&& camera_,
		std::string const& name_
	)
	{
		ImportCamera(std::move(camera_), name_);
		Connect<dstSocket>(name_);
	}

	//カメラ接続の変更
	void ChangeCamera(std::string const& to_, CameraSocket dstSocket_);

	//カメラのアップデート
	//socketMapにあるカメラのアップデートを呼ぶ。バッチングは別機関で行う
	void RunCameraUpdate();

private:

	void ImportCamera(std::unique_ptr<CameraBehavior>&& camera_, std::string const& name_);
	
	//明示的実体化必要
	template<CameraSocket to>
	void Connect(std::string const& name_);


	std::unique_ptr<CameraLibrary> cameraLibrary;
	std::unique_ptr<CameraController> cameraController;


};

