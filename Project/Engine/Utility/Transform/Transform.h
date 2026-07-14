#pragma once
#include "../../Math/Vector/Vector3.h"
#include "../../Math/Quaternion/Quaternion.h"
#include "../../Math/Matrix/Matrix4x4.h"


class Transform
{
	static inline const Vector3 kRight = { 1.0f,0.0f,0.0f };
	static inline const Vector3 kUp = { 0.0f,1.0f,0.0f };
	static inline const Vector3 kBeyond = { 0.0f,0.0f,1.0f};

	Vector3 worldPos;					//ワールド座標
	Vector3 scale;						//スケール
	Vector3 rotation;					//ヨーピッチロール
	Vector3 lookDir;					//向いている方向
	Quaternion quaternion;				//回転用クォータニオン
	float rotationInterpolationCoe{};	//回転補完係数
	Matrix4x4 worldMatrix;				//キャッシュ用ワールド行列
	std::vector<Transform*> children;	//子孫
	Transform* parent = nullptr;		//親
	bool hasTransformChanged{};			//ワールド行列をアップデートするかどうかに関わる
	bool needRotationUpdate{};			//回転補完がまだなのかどうか
	bool updatedThisFrame{};			//1フレーム１きり更新ガード


	//回転更新処理
	inline void RotationUpdate()
	{
		//次の回転クォータニオン
		Quaternion nextQuaternion = Quaternion::CreateQuaternion(lookDir);

		//rotationに値が入って入れば
		if (rotation.LengthSq() > 0.0f)
		{
			nextQuaternion = nextQuaternion.Multiply
			(
				Quaternion::CreateQuaternion(kRight, rotation.data.x).Multiply
				(
					Quaternion::CreateQuaternion(kUp, rotation.data.y).Multiply
					(
						Quaternion::CreateQuaternion(kBeyond, rotation.data.z)
					)
				)
			);
		}
		
		//回転補完
		quaternion = quaternion.Slerp(nextQuaternion, rotationInterpolationCoe);
		
		//一致していなければ、ワールド行列を更新する必要がある
		needRotationUpdate = !quaternion.NearlyEquals(nextQuaternion);
		
		if (needRotationUpdate)
		{
			NotifyChanged();
		}
	}

	inline void BeChild(Transform* parent_)
	{
		parent = parent_;
	}

	inline void DeleteChild(Transform* dstChild_)
	{
		for (auto itr = children.begin();itr != children.end();++itr)
		{
			if ((*itr) && (*itr) == dstChild_)(*itr) = nullptr;
		}
	}

	inline void ResetFrameFlag()
	{
		updatedThisFrame = false;
	}

public:

	inline void TranslatePosition(const Vector3& dstWorldPos_)
	{
		worldPos = dstWorldPos_;
		NotifyChanged();
	}

	inline void LookAt(const Vector3& dstDirection_)
	{
		lookDir = dstDirection_;
		needRotationUpdate = true;
		NotifyChanged();
	}

	inline void Rotate(const Vector3& dstRotation_)
	{
		rotation = dstRotation_;
		needRotationUpdate = true;
		NotifyChanged();
	}

	inline void ChangeScale(const Vector3& scale_)
	{
		scale = scale_;
		NotifyChanged();
	}

	inline void ChangeRotationInterpolationCoe(float dstCoe_)
	{
		rotationInterpolationCoe = dstCoe_;
		needRotationUpdate = true;
		NotifyChanged();
	}

	inline void Clear()
	{
		worldPos = {};
		rotation = {};
		lookDir = kBeyond;
		scale = { 1.0f,1.0f,1.0f };
		quaternion.Identity();
		rotationInterpolationCoe = 1.0f;
		hasTransformChanged = true;
		needRotationUpdate = true;
		updatedThisFrame = false;
		worldMatrix = Matrix4x4{};
	}

	inline void NotifyChanged()
	{
		if (hasTransformChanged) return;

		hasTransformChanged = true;

		for (auto* child : children)
		{
			if(child) child->NotifyChanged();
		}
	}

	Transform()
	{
		Clear();
	}

	~Transform()
	{
		if(parent) parent->DeleteChild(this);
	}

	template<typename... Children>
	inline void BeParent(Children... children_)
	{
		uint8_t length = sizeof...(children_);
		Transform* ary[] = { children_... };
		for (int i = 0;i < length;++i)
		{
			auto* child = children.emplace_back(ary[i]);
			child->BeChild(this);
		}
	}


	void Update()
	{
		//既に更新処理をしていればリターン
		if (updatedThisFrame) return;
		updatedThisFrame = true;

		//親の更新処理を先に呼ぶ
		if (parent) parent->Update();

		//回転クォータニオンの更新
		if (needRotationUpdate) RotationUpdate();

		///変更なしなら更新しない
		if (!hasTransformChanged) return;

		//スケール行列
		Matrix4x4 scaleMat = Matrix4x4::CreateScale(scale);
		//位置行列
		Matrix4x4 translationMat = Matrix4x4::CreateTranslation(worldPos);
		//回転行列
		Matrix4x4 rotationMat = quaternion.GetRotateMatrix();

		//SRT
		worldMatrix = scaleMat.GetMultiply(rotationMat.GetMultiply(translationMat));

		//ペアレント化しているなら
		if (parent) worldMatrix = worldMatrix.GetMultiply(parent->WatchWorldMatrix());

		hasTransformChanged = false;
	}

	inline const Matrix4x4& WatchWorldMatrix()const
	{
		return worldMatrix;
	}

	inline Vector3 WatchWorldPos()const
	{
		return
		{
			worldMatrix.data.m[3][0],
			worldMatrix.data.m[3][1],
			worldMatrix.data.m[3][2],
		};
	}

};

