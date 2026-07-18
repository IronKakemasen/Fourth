#pragma once


struct ModelDescription
{
	ModelDescription
	(
		MeshDetaID meshDataID_,
		uint32_t dispatchedTransformedMatrixID_,
		std::string name_
	) :meshDataID(meshDataID_), dispatchedTransformedMatrixID(dispatchedTransformedMatrixID_), name(name_){}

	MeshDetaID meshDataID{};
	uint32_t dispatchedTransformedMatrixID{};
	std::string name{};
};