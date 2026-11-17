#pragma once

class Materials;

struct MaterialBatchFormat
{
	MaterialBatchFormat
	(
		UINT materialID_,
		Materials* materialsPtr_
	) :materialID(materialID_), materialsPtr(materialsPtr_) {}

	UINT materialID = kInvalid;
	Materials* materialsPtr;
};