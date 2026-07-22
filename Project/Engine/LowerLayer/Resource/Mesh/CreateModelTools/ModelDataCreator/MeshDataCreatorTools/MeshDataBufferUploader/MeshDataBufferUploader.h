#pragma once
#include "../../ModelDataCreator.h"
#include "../../../../ModelStructure/ModelData/ResourceMesh/ResourceMesh.h"

class MeshContext::ModelDataCreator::MeshDataBufferUploader
{
	friend class MeshContext::ModelDataCreator;

	//BufferUploaderが中間リソースに実メッシュデータをマッピングして、静的バッファの生リソースをアップロードする
	static void CopyAndUploadBuffer
	(
		const std::vector<ResourceMesh>& data_,
		const std::vector<MeshDataBufferUniqueIDGroup>& meshDataBufferUniqueIDGroup_,
		BufferContext::BufferUploader* bufferUploader_
	);

};

