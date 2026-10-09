#pragma once
#include "../CameraContext.h"

class CameraBehavior;


class CameraContext::CameraLibrary
{
public:

	struct Local_ImportLicence;

	CameraLibrary(NexusFieldProof proof_);
	~CameraLibrary();

	void Import
	(
		Local_ImportLicence const& licence_,
		std::unique_ptr<CameraBehavior>&& cameraUnique_,
		std::string const& name_
	);

	//バッチング処理、一括アップデート呼び出しのため
	std::vector<CameraBehavior*> const& WatchLibrary()const;

private:

	//同じ型で複数制作することになるので、しぶしぶ文字列をキーにします
	std::unordered_map<std::string, std::unique_ptr<CameraBehavior>> cameraLib;
	//ランタイム用
	std::vector<CameraBehavior*> allCameraPtr;
};


struct CameraContext::CameraLibrary::Local_ImportLicence
{
private:
	friend class CameraRegister;
	explicit Local_ImportLicence() = default;

};
