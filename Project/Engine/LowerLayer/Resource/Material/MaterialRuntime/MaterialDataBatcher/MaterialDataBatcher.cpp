#include "PreCompileHeader.h"
#include "MaterialDataBatcher.h"



//外部
#include "../../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"
#include "../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"

namespace
{
	auto const fileName = "MaterialDataBatcher.cpp";
}


MaterialContext::MaterialDataBatcher::MaterialDataBatcher
(
	NexusFieldProof proof_
) 
{
	materialIndexGroupsCache.resize((UINT)ProjectConfig::Render::BufferSize::kMaterialIndexGroupArr);
}

void MaterialContext::MaterialDataBatcher::ImportMaterialIndexGroupArrBufferID(BufferUniqueID id_)
{
	materialIndexGroupArrBufferID = id_;
	Logger::Log("Import MaterialIndexGroupArrBufferID: " + std::to_string(id_), fileName);
}


void MaterialContext::MaterialDataBatcher::WriteMaterialIndexGroupsArrBuffer
(
	NexusFieldProof proof_, 
	AgentKey key_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//bufferDispatcherを借りる
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence;
	auto& bufferDispatcher = *bufferContextDiplomat_.Access<BufferContext::ToolLender>()->
	Lend<BufferContext::BufferDispatcher>(licence);

	//バッチ先バッファ
	auto* dstWriteInBuffer = static_cast<UploadStructuredBuffer*>(bufferDispatcher.Dispatch(materialIndexGroupArrBufferID));
	
	//両面にマテリアル配列インデックス群配列のデータを書き込む
	dstWriteInBuffer->WriteRangeInBoth< Material::MaterialIndexGroupCPUGPU >
	(
		{
			materialIndexGroupsCache,
			materialIndexGroupsCache
		}
	);
	Logger::Log("Write materialIndexGroups", fileName);


	materialIndexGroupsCache.clear();
	materialIndexGroupsCache.shrink_to_fit();
	Logger::Log("Delete materialIndexGroupsCache", fileName);
}


