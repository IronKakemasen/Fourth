#pragma once
#include "../../../../../Math/Vector/Vector3.h"

struct CameraDesc
{
	Vector3 pos;
	Vector3 lookDir = { 0,0,1 };
	float rotationZ{};
	float rotationInterpolationCoe = 1.0f;

	float farClip = 0.1f;
	float nearClip = 1000.0f;
	float fovY = MathConstants::kPi * MathConstants::kHalf;
	float aspectRatio = (float)ProjectConfig::Window::kWidth / (float)ProjectConfig::Window::kHeight;
};

