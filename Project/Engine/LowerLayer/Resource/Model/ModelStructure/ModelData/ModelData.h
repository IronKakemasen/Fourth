#pragma once
#include "../../ModelContext.h"

//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"

struct ModelContext::ModelData
{
	template<typename DataType>
	struct DataTypeTraits;

	std::vector<MeshDataID> meshDataID;
	std::vector<StructuredBufferModelData::MaterialCPU> materialCPU;
	std::vector<size_t> meshletSize;
};

template<>
struct ModelContext::ModelData::DataTypeTraits<MeshDataID>
{
	static inline const std::string kName = "MeshDataID";
};

template<>
struct ModelContext::ModelData::DataTypeTraits<StructuredBufferModelData::MaterialCPU>
{
	static inline const std::string kName = "MaterialCPU";
};

template<>
struct ModelContext::ModelData::DataTypeTraits<size_t>
{
	static inline const std::string kName = "MeshletSize";
};

