#include "PreCompileHeader.h"
#include "RenderPassCreator.h"
#include "../PassDesc/PassDesc.h"
#include "../RenderPassContainer/RenderPassContainer.h"
#include "../AllRenderPass/AllPassInclude.h"
#include "PassSettingsLoader/PassSettingsLoader.h"
#include "PassBufferCreator/PassBufferCreator.h"

RenderContext::RenderPassCreator::RenderPassCreator
(
	NexusFieldProof proof_,
	RenderPassContainer* container_,
	BufferContextDiplomat& bufferContextDiplomat_
)
:passContainer(container_)
{

}


template<>
SceneTextureCreator* RenderContext::RenderPassCreator::InstantiatePass(Local_CreateRenderPassLicence licence_, PassDesc desc_)
{

	return passContainer->Import(licence_, std::move(std::make_unique<SceneTextureCreator>(licence_, std::move(desc_))));
}

RenderContext::PassDesc RenderContext::RenderPassCreator::CreateDesc(std::string const passName_, BufferContext::BufferCreator* bufferCreator_)
{
	//パスのセッティングを読み込む
	PassRequiredInfo passRequiredInfo = PassSettingsLoader::Load(passName_);
	//その設定をもとにバッファを作成しそのユニークをディスクに記録
	PassBufferCreator::CreateBuffer(passName_, passRequiredInfo, bufferCreator_);

	return PassDesc(passRequiredInfo);

}
