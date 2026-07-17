	#pragma once
	#include "../Matrix/Matrix4x4.h"


	struct Quaternion
	{
		DirectX::XMFLOAT4 data;
		
		inline Quaternion()
		{
			DirectX::XMStoreFloat4(&data, DirectX::XMQuaternionIdentity());
		}

		inline Quaternion(float x_, float y_, float z_, float w_) : data(x_, y_, z_, w_) {};

		inline void Identity()
		{
			DirectX::XMStoreFloat4(&data, DirectX::XMQuaternionIdentity());
		}

		inline Matrix4x4 GetRotateMatrix() const
		{
			DirectX::XMVECTOR q = DirectX::XMLoadFloat4(&data);

			Matrix4x4 result;

			DirectX::XMStoreFloat4x4(&result.data, DirectX::XMMatrixRotationQuaternion(q));
			return result;
		}

		inline static Quaternion CreateQuaternion(const Vector3 axis_, const float radian_)
		{
			DirectX::XMVECTOR axisVec = DirectX::XMVectorSet(axis_.data.x, axis_.data.y, axis_.data.z, 0.0f);
			axisVec = DirectX::XMVector3Normalize(axisVec);

			Quaternion result;
			DirectX::XMStoreFloat4(&result.data, DirectX::XMQuaternionRotationAxis(axisVec, radian_));

			return result;
		}

		inline static Quaternion CreateQuaternion(const Vector3 lookDir_)
		{
			DirectX::XMVECTOR xAxis;
			DirectX::XMVECTOR yAxis;
			DirectX::XMVECTOR zAxis;
			DirectX::XMVECTOR vertical;

			zAxis = DirectX::XMVectorSet(lookDir_.data.x, lookDir_.data.y, lookDir_.data.z, 0.0f);
			zAxis = DirectX::XMVector3Normalize(zAxis);

			DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			float dot = DirectX::XMVectorGetX(DirectX::XMVector3Dot(zAxis, up));

			//真下か真上を向いている場合を回避
			if (fabsf(dot) > 0.99f)
			{
				//代わりの上方向として前を垂直軸として作る
				vertical = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			}
			else
			{
				vertical = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			}

			xAxis = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(vertical, zAxis));

			yAxis = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(zAxis, xAxis));

			DirectX::XMMATRIX roatationMatrix = DirectX::XMMatrixIdentity();
			roatationMatrix.r[0] = xAxis;
			roatationMatrix.r[1] = yAxis;
			roatationMatrix.r[2] = zAxis;

			Quaternion result;
			DirectX::XMStoreFloat4(&result.data, DirectX::XMQuaternionRotationMatrix(roatationMatrix));

			return result;
		}

		inline Quaternion Multiply(const Quaternion& rQuaternion_)const
		{
			DirectX::XMVECTOR q1 = DirectX::XMLoadFloat4(&data);
			DirectX::XMVECTOR q2 = DirectX::XMLoadFloat4(&rQuaternion_.data);

			Quaternion result;
			DirectX::XMStoreFloat4(&result.data, DirectX::XMQuaternionMultiply(q1, q2));

			return result;
		}

		inline Quaternion Slerp(const Quaternion& rQuaternion_, float t_) const
		{
			DirectX::XMVECTOR startQ = DirectX::XMLoadFloat4(&data);
			DirectX::XMVECTOR endQ = DirectX::XMLoadFloat4(&rQuaternion_.data);

			Quaternion result;
			DirectX::XMStoreFloat4(&result.data, DirectX::XMQuaternionSlerp(startQ, endQ, t_));

			return result;
		}

		inline bool NearlyEquals(const Quaternion& rQuaternion_, float epsilon_ = 1e-6f) const
		{
			return
			fabsf(data.x - rQuaternion_.data.x) <= epsilon_		&&
			fabsf(data.y - rQuaternion_.data.y) <= epsilon_		&&
			fabsf(data.z - rQuaternion_.data.z) <= epsilon_		&&
			fabsf(data.w - rQuaternion_.data.w) <= epsilon_;
		}

	};

