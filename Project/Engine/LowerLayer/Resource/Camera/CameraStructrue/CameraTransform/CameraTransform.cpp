#include "PreCompileHeader.h"
#include "CameraTransform.h"
#include "../../../../../MiddleLayer/Transform/Transform.h"
#include "../CameraDesc/CameraDesc.h"

namespace
{
	auto const fileName = "CameraTransform.cpp";
}

CameraBehavior::CameraTransform::CameraTransform(std::optional<CameraDesc> const& desc_)
{
	if (desc_.has_value())
	{
		cameraDesc = std::make_unique<CameraDesc>(*desc_);
	}

	Clear();
}


void CameraBehavior::CameraTransform::Clear()
{
	if (!cameraDesc)
	{
		base.pos = {};
		base.rotationZ = {};
		base.lookDir = { 0,0,1 };
		base.rotationInterpolationCoe = 1.0f;

		projection.farClip = 0.1f;
		projection.nearClip = 1000.0f;
		projection.fovY = MathConstants::kPi * MathConstants::kHalf;
		projection.aspectRatio = (float)ProjectConfig::Window::kWidth / (float)ProjectConfig::Window::kHeight;
	}
	else
	{
		base.pos = cameraDesc->pos;
		base.rotationZ = cameraDesc->rotationZ;
		base.lookDir = cameraDesc->lookDir;
		base.rotationInterpolationCoe = cameraDesc->rotationInterpolationCoe;

		projection.farClip = cameraDesc->farClip;
		projection.nearClip = cameraDesc->nearClip;
		projection.fovY = cameraDesc->fovY;
		projection.aspectRatio = cameraDesc->aspectRatio;
	}

	base.quaternion.Identity();

	matrices.view = Matrix4x4{};
	matrices.proj = Matrix4x4{};
	matrices.viewProj = Matrix4x4{};
}


void CameraBehavior::CameraTransform::UpdateMatrices(CameraBehavior::Local_UpdateLicence licence_)
{
	//回転クォータニオンの更新
	RotationUpdate();

	//位置行列
	Matrix4x4 translationMat;
	if (base.followTarget)
	{
		Vector3 worldPos = base.followTarget->WatchWorldPos() + base.pos;
		translationMat = Matrix4x4::CreateTranslation(worldPos);
	}
	else
	{
		translationMat = Matrix4x4::CreateTranslation(base.pos);
	}

	//回転行列
	Matrix4x4 rotationMat = base.quaternion.GetRotateMatrix();

	//ペアレント化しているなら
	if (base.parent) rotationMat = rotationMat.GetMultiply(base.parent->WatchWorldMatrix());

	//view
	matrices.view = rotationMat.GetMultiply(translationMat).GetInversed();
	
	//proj
	UpdateProjectionMatrixReverseZ();

	//viewProj
	matrices.viewProj = matrices.view.GetMultiply(matrices.proj);
}

void CameraBehavior::CameraTransform::UpdateProjectionMatrixReverseZ()
{
	const float cotTheta{ 1.0f / tanf(projection.fovY * MathConstants::kHalf) };
	const float inv_frustumHeight{ 1.0f / (projection.farClip - projection.nearClip) };

	matrices.proj = Matrix4x4
	{
		cotTheta / projection.aspectRatio, 0.0f, 0.0f, 0.0f,
		0.0f, cotTheta, 0.0f, 0.0f,
		0.0f, 0.0f, projection.farClip * inv_frustumHeight, 1.0f,
		0.0f, 0.0f, -projection.nearClip * projection.farClip * inv_frustumHeight, 0.0f,
	};

}

//回転更新処理
void CameraBehavior::CameraTransform::RotationUpdate()
{
	//次の回転クォータニオン
	Quaternion nextQuaternion = Quaternion::CreateQuaternion(base.lookDir);

	//rotationに値が入って入れば
	if (std::fabsf(base.rotationZ) > 0.0f)
	{
		nextQuaternion = nextQuaternion.Multiply
		(
			Quaternion::CreateQuaternion({ 0.0f,0.0f,1.0f }, base.rotationZ)
		);
	}

	//回転補完
	base.quaternion = base.quaternion.Slerp(nextQuaternion, base.rotationInterpolationCoe);

}

void CameraBehavior::CameraTransform::BeChild(Transform* parent_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		!base.followTarget,
		"ペアレント化とポジションフォローは同時に設定できないぜ",
		fileName
	);

	base.parent = parent_;
}

void CameraBehavior::CameraTransform::Follow(Transform* followTarget_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		!base.parent,
		"ペアレント化とポジションフォローは同時に設定できないぜ",
		fileName
	);

	base.followTarget = followTarget_;
}

void CameraBehavior::CameraTransform::TranslatePosition(const Vector3& dstPos_)
{
	base.pos = dstPos_;
}

void CameraBehavior::CameraTransform::LookAt(const Vector3& dstDirection_)
{
	base.lookDir = dstDirection_;
}

void CameraBehavior::CameraTransform::RotateZ(float dstRotation_)
{
	base.rotationZ = dstRotation_;
}

void CameraBehavior::CameraTransform::ChangeRotationInterpolationCoe(float dst_)
{
	base.rotationInterpolationCoe = dst_;
}

void CameraBehavior::CameraTransform::ChangeFovY(float dst_)
{
	projection.fovY = dst_;
}
