#include "PreCompileHeader.h"
#include "MaterialDataBatcher.h"



//外部
#include "../../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"


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

void MaterialContext::MaterialDataBatcher::ImportMaterialIDGroupArrBufferID(BufferUniqueID id_)
{
	materialIDGroupArrBufferID = id_;
	Logger::Log("Import MaterialIDGroupArrBufferID: " + std::to_string(id_), fileName);
}




void MaterialContext::MaterialDataBatcher::WriteMaterialIndexGroups
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

	//バッチ先

	materialIndexGroupsCache.clear();
	materialIndexGroupsCache.shrink_to_fit();
	Logger::Log("Delete materialIndexGroupsCache", fileName);


}


