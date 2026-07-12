#pragma once

struct Model
{
private:

	static constexpr MeshUniqueID kInvalidID = -1;

public:

	MeshUniqueID meshID = kInvalidID;
	MaterialUniqueID materialID = kInvalidID;
};

