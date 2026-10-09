#pragma once

class CameraContext;
struct CameraDesc;

class CameraBehavior
{
	friend class CameraContext;

	//カメラ専用のトランスフォーム
	struct CameraTransform;

public:

	//行列アップデート許可証
	struct Local_UpdateMatricesLicence;

	CameraBehavior(std::optional<CameraDesc> const& desc_);
	virtual ~CameraBehavior() = default;

	//お好きにどうぞな更新処理
	virtual void Update() = 0;

	CameraTransform& AccssTransform() { return *trans; }

	//行列更新処理は、一括で誰かが呼びます
	void UpdateMatrices(Local_UpdateMatricesLicence licence_);

protected:

	std::unique_ptr<CameraTransform> trans;


};


struct CameraBehavior::Local_UpdateMatricesLicence
{
private:
	friend class CameraContext;
	explicit Local_UpdateMatricesLicence() = default;

};
