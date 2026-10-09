#pragma once
#include "../CameraContext.h"

class CameraBehavior;

class CameraContext::CameraRegister
{
public:

	CameraRegister
	(
		NexusFieldProof proof_,
		CameraLibrary& cameraLibrary_
	);

	void Register(std::unique_ptr<CameraBehavior>&& camera_, std::string const& name_);


private:

	CameraLibrary& cameraLibrary;
};

