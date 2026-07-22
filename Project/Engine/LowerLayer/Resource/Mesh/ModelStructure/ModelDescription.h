#pragma once


struct ModelDescription
{
	ModelDescription
	(
		MeshDataID meshDataID_,
		uint32_t dispatchedTransformedMatrixID_,
		std::string name_
	) :meshDataID(meshDataID_), dispatchedTransformedMatrixID(dispatchedTransformedMatrixID_), name(name_){}

	MeshDataID meshDataID{};
	uint32_t dispatchedTransformedMatrixID{};
	std::string name{};
};