#include "PreCompileHeader.h"
#include "RenderPassCreator.h"
#include "../PassDesc/PassDesc.h"
#include "../RenderPassContainer/RenderPassContainer.h"
#include "../AllRenderPass/AllPassInclude.h"

RenderContext::RenderPassCreator::RenderPassCreator(NexusFieldProof proof_, RenderPassContainer* container_)
	:passContainer(container_)
{

}


template<>
SceneTextureCreator* RenderContext::RenderPassCreator::Create
(
	Local_CreateRenderPassLicence licence_,
	const PassDesc& desc_
)
{
	return passContainer->Import(licence_, std::move(std::make_unique<SceneTextureCreator>(licence_, std::move(desc_))));
}
