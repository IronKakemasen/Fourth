#include "PreCompileHeader.h"
#include "RenderPassCreator.h"
#include "../PassDesc/PassDesc.h"
#include "../AllRenderPass/AllPassInclude.h"
#include "PassSettingsLoader/PassSettingsLoader.h"
#include "PassBufferCreator/PassBufferCreator.h"

//外部
#include "../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"


RenderContext::RenderPassCreator::RenderPassCreator
(
	NexusFieldProof proof_,
	RenderPassContainer* container_
)
:passContainer(container_)
{

}

BufferContext::BufferCreator* RenderContext::RenderPassCreator::BorrowBufferCreator(BufferContextDiplomat& bufferContextDiplomat_)
{
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> borrowLicence;
	return bufferContextDiplomat_.Access<BufferContext::ToolLender>()->Lend<BufferContext::BufferCreator>(borrowLicence);
}


RenderContext::PassDesc RenderContext::RenderPassCreator::CreateDesc(std::string const passName_, BufferContext::BufferCreator* bufferCreator_)
{
	//パスのセッティングを読み込む
	PassDesc desc = PassSettingsLoader::Load(passName_);
	//その設定をもとにバッファを作成しそのユニークをディスクに記録
	PassBufferCreator::CreateBuffer(passName_, desc, bufferCreator_);

	return desc;

}
