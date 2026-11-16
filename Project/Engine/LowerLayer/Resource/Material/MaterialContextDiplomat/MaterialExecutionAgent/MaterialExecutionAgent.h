#pragma once
#include "../../MaterialContext.h"

struct MaterialBatchFormat;

class MaterialContext::ExecutionAgent
{
public:

	struct SceneContextProof;

	ExecutionAgent
	(
		NexusFieldProof proof_,
		MaterialDataBatcher& materialDataBatcher_
	);

	//マテリアル配列インデックス群配列のバッファにデータを書き込む
	void WriteInMaterialIndexGroupsArrBuffer
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//マテリアルデータをマテリアル配列にバッチングする
	void WriteInAllMaterialData
	(
		SceneContextProof proof_,
		std::vector<MaterialBatchFormat>& src_,
		UINT frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


private:

	MaterialDataBatcher& materialDataBatcher;

};

