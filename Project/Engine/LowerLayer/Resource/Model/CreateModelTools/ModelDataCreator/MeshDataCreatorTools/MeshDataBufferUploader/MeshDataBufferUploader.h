#pragma once
#include "../../ModelDataCreator.h"

struct ResourceMesh;

class ModelContext::ModelDataCreator::MeshDataBufferUploader
{
	friend class ModelContext::ModelDataCreator;

	//BufferUploaderが中間リソースに実メッシュデータをマッピングして、静的バッファの生リソースをアップロードする
	static void CopyAndUploadBuffer
	(
		const std::vector<ResourceMesh>& data_,
		const std::vector<MeshDataBufferUniqueIDGroup>& meshDataBufferUniqueIDGroup_,
		BufferContext::BufferUploader* bufferUploader_
	);

};

