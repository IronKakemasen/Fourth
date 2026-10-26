#pragma once
#include "../CameraCreator/CameraCreator.h"

class CameraBehavior;

class CameraContext::FrontlineSystems
{
	//そのシーンに存在するカメラのライブラリ
	class CameraLibrary;
	//カメラのアップデートを読んだり、デバッグ操作などを行う
	class CameraController;


public:

	template<CameraSocket dstSocket_>
	using CmdConnectCamera = std::function<void(std::string const&)>;

	FrontlineSystems(NexusFieldProof proof_, CameraCreator& cameraCreator_);
	~FrontlineSystems();

	//カメラの作成
	template<CameraSocket dstSocket,typename CameraType>
	CameraType* CreateCamera
	(
		std::optional<CameraDesc> const& cameraDesc_,
		std::string const& name_
	)
	{
		std::unique_ptr<CameraType> cameraUnique = cameraCreator.Create<dstSocket, CameraType>(cameraDesc_);
		CameraType* cameraPtr = cameraUnique.get();

		ImportCamera(std::move(cameraUnique), name_);
		Connect<dstSocket>(name_);

		return cameraPtr;
	}

	//カメラ接続の変更するコマンドを返す
	template<CameraSocket dstSocket_>
	CmdConnectCamera<dstSocket_> GetCmdConnectCamera()
	{
		return [this](std::string const& dstCamera_)
		{
			Connect<dstSocket_>(dstCamera_);
		};
	}

	//カメラのアップデート
	//socketMapにあるカメラのアップデートを呼ぶ。バッチングは別機関で行う
	std::unordered_map<CameraSocket, CameraBehavior*> const& CameraUpdate();

private:

	void ImportCamera(std::unique_ptr<CameraBehavior>&& camera_, std::string const& name_);
	
	//明示的実体化必要
	template<CameraSocket to>
	void Connect(std::string const& name_);


	std::unique_ptr<CameraLibrary> cameraLibrary;
	std::unique_ptr<CameraController> cameraController;
	CameraCreator& cameraCreator;

};

