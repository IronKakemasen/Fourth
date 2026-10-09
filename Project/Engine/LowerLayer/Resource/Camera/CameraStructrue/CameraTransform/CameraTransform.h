#pragma once
#include "../CameraBehavior.h"
#include "../../../../../Math/Vector/Vector2.h"
#include "../../../../../Math/Vector/Vector3.h"
#include "../../../../../Math/Quaternion/Quaternion.h"
#include "../../../../../Math/Matrix/Matrix4x4.h"

class Transform;

struct CameraBehavior::CameraTransform
{
private:
	//投影方法関連
	struct Projection
	{
		float farClip = 0.1f;
		float nearClip = 1000.0f;
		float fovY = MathConstants::kPi * MathConstants::kHalf;
		float aspectRatio = (float)ProjectConfig::Window::kWidth / (float)ProjectConfig::Window::kHeight;
	};

	//カメラ専用のトランスフォームパラメータ
	struct Base
	{
		Vector3 pos;
		Vector3 lookDir{};
		float rotationZ{};
		Quaternion quaternion;
		float rotationInterpolationCoe{};
		//ポジションのみを追跡したい場合
		Transform* followTarget = nullptr;
		Transform* parent = nullptr;
	};


public:
	CameraTransform(std::optional<CameraDesc> const& desc_);

	//描画用の行列更新
	void UpdateMatrices(CameraBehavior::Local_UpdateLicence licence_);
	void Clear();
	//ペアレント化
	void BeChild(Transform* parent_);
	//フォロー
	void Follow(Transform* followTarget_);

	//パラメータ変動
	void TranslatePosition(const Vector3& dstPos_);
	void LookAt(const Vector3& dstDirection_);
	void RotateZ(float dstRotation_);
	void ChangeRotationInterpolationCoe(float dst_);
	void ChangeFovY(float dst_);


	//バッチング処理で使用
	auto const& WatchMatrices()const { return matrices; }

private:

	Base base;
	Projection projection;
	Matrices matrices;

	//初期値でクリアするために所持できるようにする
	std::unique_ptr<CameraDesc> cameraDesc;

	//回転更新処理
	void RotationUpdate();
	//透視投影作成(リバースZ対応)
	void UpdateProjectionMatrixReverseZ();
};

