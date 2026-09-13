#pragma once
#include "../../ModelDataCreator.h"

//外部
#include "../../../../../../../../Assets/Shared/StructuredBufferModelData.h"

class ModelContext::ModelDataCreator::MeshDataBufferUploader
{
	friend class ModelContext::ModelDataCreator;

	//BufferUploaderが中間リソースに実メッシュデータをマッピングして、静的バッファの生リソースをアップロードする
	static void CopyAndUploadBuffer
	(
		const std::vector<StructuredBufferModelData::MeshCPU>& data_,
		const std::vector<MeshDataBufferUniqueIDGroup>& meshDataBufferUniqueIDGroup_,
		BufferContext::BufferUploader* bufferUploader_
	);

};

