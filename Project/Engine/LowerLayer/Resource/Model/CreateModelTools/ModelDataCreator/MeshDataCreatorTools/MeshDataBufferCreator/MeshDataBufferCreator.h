#pragma once
#include "../../ModelDataCreator.h"
#include "../../../../../../../../Assets/Shared/StructuredBufferModelData.h"


class ModelContext::ModelDataCreator::MeshDataBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	//メッシュデータのバッファを作成し,そのメッシュデータのバッファユニークID群を返す
	[[nodiscard]] static std::vector<MeshDataBufferUniqueIDGroup> CreateMeshDataBuffer
	(
		ModelContext::ModelSlotAllocator* allocator_, 
		const std::vector<StructuredBufferModelData::MeshCPU>& data_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferCollector* bufferCollector_,
		std::string modelFileName_,
		MeshDataID& meshDataID_
	);

};

