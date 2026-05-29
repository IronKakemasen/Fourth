#include "Vector3.h"
#include "../Matrix/Matrix4.h"

Vector3 Vector3::GetMultiply(Matrix4 const& other) const
{
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&data);
	DirectX::XMMATRIX m = DirectX::XMLoadFloat4x4(&other.data);

	DirectX::XMVECTOR resultVector = DirectX::XMVector3TransformCoord(v, m);

	Vector3 result;
	DirectX::XMStoreFloat3(&result.data, resultVector);

	return result;
}
