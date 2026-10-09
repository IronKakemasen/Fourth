#pragma once
#include "../../../../Math/Matrix/Matrix4x4.h"

class CameraContext;
struct CameraDesc;
class Transform;

class CameraBehavior
{
	//描画のための行列群
	struct Matrices
	{
		Matrix4x4 view;
		Matrix4x4 proj;
		Matrix4x4 viewProj;
	};

	//カメラ専用のトランスフォーム
	struct CameraTransform;

public:

	//アップデート許可証
	struct Local_UpdateLicence;

	CameraBehavior(std::optional<CameraDesc> const& desc_);
	virtual ~CameraBehavior() = default;

	//お好きにどうぞな更新処理。一括で誰かが呼びます
	virtual void Update(Local_UpdateLicence licence_) = 0;

	//一括で誰かが呼びます
	void UpdateMatrices(Local_UpdateLicence licence_);
	
	//クリア
	void Clear();
	//ペアレント化
	void BeChild(Transform* parent_);
	//フォロー
	void Follow(Transform* followTarget_);

	//おもにバッチング処理のため
	Matrices const& WatchMatrices()const;

protected:

	std::unique_ptr<CameraTransform> trans;
};


struct CameraBehavior::Local_UpdateLicence
{
private:
	friend class CameraContext;
	explicit Local_UpdateLicence() = default;

};
