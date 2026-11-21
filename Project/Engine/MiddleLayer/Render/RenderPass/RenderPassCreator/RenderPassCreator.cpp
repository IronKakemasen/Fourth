#include "PreCompileHeader.h"
#include "RenderPassCreator.h"
#include "../AllRenderPass/AllPassInclude.h"
#include "PassSettingsLoader/PassSettingsLoader.h"
#include "PassBufferCreator/PassBufferCreator.h"


RenderContext::RenderPassCreator::RenderPassCreator
(
	NexusFieldProof proof_,
	RenderPassContainer& container_
)
:passContainer(container_)
{

}


std::unique_ptr<RenderContext::PassDesc> RenderContext::RenderPassCreator::CreateDesc(std::string const& passName_, BufferContextDiplomat& bufferContextDiplomat_)
{
	//パスのセッティングを読み込む
	std::unique_ptr<PassDesc> desc = PassSettingsLoader::Load(passName_);

	//その設定をもとにバッファを作成しそのユニークをディスクに記録
	PassBufferCreator::CreateBuffer
	(
		passName_, 
		*desc, 
		passBufferCache,
		colorBufferInfoMapCache,
		depthBufferInfoMapCache,
		bufferContextDiplomat_
	);

	return desc;
}

std::unordered_map<std::string, BufferUniqueID> const& RenderContext::RenderPassCreator::WatchPassBufferCache(NexusFieldProof proof_)const
{
	return passBufferCache;
}


std::unordered_map<std::string, RenderContext::RequiredBufferInfo::ColorBuffer*> const&
RenderContext::RenderPassCreator::WatchColorBufferInfoMapCache(NexusFieldProof proof_)const
{
	return colorBufferInfoMapCache;
}

std::unordered_map<std::string, RenderContext::RequiredBufferInfo::DepthStencilBuffer*> const&
RenderContext::RenderPassCreator::WatchDepthBufferInfoMapCache(NexusFieldProof proof_)const
{
	return depthBufferInfoMapCache;
}
