#pragma once


struct Vector3
{
	//保管用
	DirectX::XMFLOAT3 data;


	Vector3();
	Vector3(float x_, float y_, float z_);
	Vector3(float entries_[3]);

};

