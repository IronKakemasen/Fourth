#pragma once
#include "../CameraFrontlineSystems.h"


class CameraContext::CameraFrontlineSystems::CameraLibrary
{
public:


	CameraLibrary(NexusFieldProof proof_);
	~CameraLibrary();

	void Import
	(
		std::unique_ptr<CameraBehavior>&& cameraUnique_,
		std::string const& name_
	);

	CameraBehavior* Export(std::string const& name_);

private:

	//同じ型で複数制作することになるので、しぶしぶ文字列をキーにします
	std::unordered_map<std::string, std::unique_ptr<CameraBehavior>> cameraLib;
};

