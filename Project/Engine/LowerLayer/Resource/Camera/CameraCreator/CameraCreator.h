#pragma once
#include "../CameraContext.h"
//エンジン備え付けのカメラ
#include "../PresetCameras/PresetCameraIncludes.h"
#include "../CameraContextRuntime/CameraSocket.h"

//アプリケーションの全カメラ
#include "../../../../../Application/AllCameraIncludes.h"

struct CameraDesc;

class CameraContext::CameraCreator
{
public:

	CameraCreator(NexusFieldProof proof_);

	template<CameraSocket dstSocket, typename CameraType>
	std::unique_ptr<CameraBehavior> Create
	(
		std::optional<CameraDesc> const& cameraDesc_
	)
	{
		return std::make_unique<CameraType>(cameraDesc_);
	}


};

