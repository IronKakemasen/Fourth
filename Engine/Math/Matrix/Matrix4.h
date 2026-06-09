#pragma once
#include "../Vector/Vector3.h"

struct Matrix4
{
	DirectX::XMFLOAT4X4 data;

	inline Matrix4()
	{
		DirectX::XMStoreFloat4x4(&data, DirectX::XMMatrixIdentity());
	}

	inline Matrix4
	(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	)
	{
		data = DirectX::XMFLOAT4X4
		(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		);
	}


	inline static Matrix4 CreateScale(float x_, float y_ , float z_)
	{
		Matrix4 scaleMat;
		DirectX::XMStoreFloat4x4(&scaleMat.data, DirectX::XMMatrixScaling(x_, y_, z_));
		
		return scaleMat;
	}

	inline static Matrix4 CreateScale(const Vector3 scale_ )
	{
		Matrix4 scaleMat;
		DirectX::XMStoreFloat4x4(&scaleMat.data, DirectX::XMMatrixScaling(scale_.data.x, scale_.data.y, scale_.data.z));

		return scaleMat;
	}

	inline static Matrix4 CreateTranslation(float x_, float y_, float z_)
	{
		Matrix4 translationMat;
		DirectX::XMStoreFloat4x4(&translationMat.data, DirectX::XMMatrixTranslation(x_, y_, z_));

		return translationMat;
	}

	inline static Matrix4 CreateTranslation(const Vector3 translation_)
	{
		Matrix4 translationMat;
		DirectX::XMStoreFloat4x4(&translationMat.data, DirectX::XMMatrixTranslation(translation_.data.x, translation_.data.y, translation_.data.z));

		return translationMat;
	}

	Matrix4 GetMultiply(Matrix4 const& other) const
	{
		DirectX::XMMATRIX m1 = DirectX::XMLoadFloat4x4(&data);
		DirectX::XMMATRIX m2 = DirectX::XMLoadFloat4x4(&other.data);

		Matrix4 result;
		DirectX::XMStoreFloat4x4(&result.data, DirectX::XMMatrixMultiply(m1, m2));

		return result;
	}

	inline float GetDeterminant()const
	{
		DirectX::XMMATRIX m = DirectX::XMLoadFloat4x4(&data);

		return DirectX::XMVectorGetX(DirectX::XMMatrixDeterminant(m));
	}

	inline Matrix4 GetInversed() const
	{
		DirectX::XMMATRIX m = DirectX::XMLoadFloat4x4(&data);
		DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(m);

		if (DirectX::XMVector4Equal(determinant, DirectX::XMVectorZero()))
		{
			return Matrix4(); 
		}

		Matrix4 result;

		DirectX::XMStoreFloat4x4(&result.data, DirectX::XMMatrixInverse(&determinant, m));
		return result;
	}

	inline Matrix4 Transpose() const
	{
		DirectX::XMMATRIX m = DirectX::XMLoadFloat4x4(&data);

		Matrix4 result;
		
		DirectX::XMStoreFloat4x4(&result.data, DirectX::XMMatrixTranspose(m));
		return result;
	}

};
