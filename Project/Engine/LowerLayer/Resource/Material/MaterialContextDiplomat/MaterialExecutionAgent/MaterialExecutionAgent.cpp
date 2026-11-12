#include "PreCompileHeader.h"
#include "MaterialExecutionAgent.h"
#include "../../MaterialRuntime/MaterialDataBatcher/MaterialDataBatcher.h"


MaterialContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	MaterialDataBatcher& materialDataBatcher_
):materialDataBatcher(materialDataBatcher_)
{

}

void MaterialContext::ExecutionAgent::WriteMaterialIndexGroupsArrBuffer
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//マテリアル配列インデックス群配列バッファに書き込む
	//キャッシュは削除する
	materialDataBatcher.WriteMaterialIndexGroupsArrBuffer
	(
		proof_,
		AgentKey{},
		bufferContextDiplomat_
	);
}
