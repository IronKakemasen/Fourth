#pragma once
#include "../../ModelDataCreator.h"



class MeshContext::ModelDataCreator::MeshDataBufferCreator
{
public:

	//メッシュデータのバッファを作成し,そのメッシュデータのバッファユニークID群を返す
	[[nodiscard]] static std::vector<MeshDataBufferUniqueIDGroup> CreateMeshDataBuffer
	(
		std::unordered_map<std::string, std::vector<MeshDataID>>& meshDataIDLib_,
		const std::vector<ResourceMesh>& data_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferCollector* bufferCollector_,
		std::string modelFileName_,
		MeshDataID& meshDataID_
	);

};

