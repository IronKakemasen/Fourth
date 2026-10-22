#pragma once
#include "../CameraContext.h"
#include "../CameraContextRuntime/CameraSocket.h"


struct CameraDesc;
class CameraBehavior;

class CameraContext::CameraCreator
{
public:

	CameraCreator(NexusFieldProof proof_);

	template<CameraSocket dstSocket, typename CameraType>
	std::unique_ptr<CameraType> Create
	(
		std::optional<CameraDesc> const& cameraDesc_
	)
	{
		return std::make_unique<CameraType>(cameraDesc_);
	}


};

