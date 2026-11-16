#include "PreCompileHeader.h"
#include "MaterialExecutionAgent.h"
#include "../../MaterialRuntime/MaterialDataBatcher/MaterialDataBatcher.h"
#include "MaterialAgentLicences.h"

MaterialContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	MaterialDataBatcher& materialDataBatcher_
):materialDataBatcher(materialDataBatcher_)
{

}

void MaterialContext::ExecutionAgent::WriteInMaterialIndexGroupsArrBuffer
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//マテリアル配列インデックス群配列バッファに書き込む
	materialDataBatcher.WriteInMaterialIndexGroupsArrBuffer
	(
		proof_,
		AgentKey{},
		bufferContextDiplomat_
	);
}

void MaterialContext::ExecutionAgent::WriteInAllMaterialData
(
	SceneContextProof proof_,
	std::vector<MaterialBatchFormat>& src_,
	UINT frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	materialDataBatcher.WriteInAllMaterialData
	(
		AgentKey{},
		src_,
		frameIndex_,
		bufferContextDiplomat_
	);
}

