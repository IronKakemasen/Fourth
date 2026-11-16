#pragma once

class Materials;

struct MaterialBatchFormat
{
	UINT materialID = kInvalid;
	Materials* materialsPtr;
};