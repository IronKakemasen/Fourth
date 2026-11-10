#include "PreCompileHeader.h"
#include "MaterialAttacher.h"


//外部
#include "../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"


MaterialContext::MaterialAttacher::MaterialAttacher
(
	NexusFieldProof proof_,
	MaterialIndexDispatcher& materialIndexDispatcher_,
	BufferContextDiplomat& nufferContextDiplomat_
) :materialIndexDispatcher(materialIndexDispatcher_)
{
	//bufferDispatcherを借りる
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence;
	bufferDispatcher = nufferContextDiplomat_.Access<BufferContext::ToolLender>()->
		Lend<BufferContext::BufferDispatcher>(licence);




}

UINT MaterialContext::MaterialAttacher::DispatchMaterialID()
{
	return materialIndexDispatcher.DispatchMaterialID();
}
