#pragma once
#include "../../../../../../Math/Vector/Vector2.h"
#include "../../../../../../Math/Vector/Vector3.h"

struct StandardVertex
{
	StandardVertex() {};

	StandardVertex
	(
		Vector3 localPos_,
		Vector3 normal_,
		Vector3 tangent_,
		Vector2 texcoord_
	) :localPos(localPos_), normal(normal_), tangent(tangent_), texcoord(texcoord_) {}

	Vector3 localPos;
	Vector3 normal;
	Vector3 tangent;
	Vector2 texcoord;
};