#include "PreCompileHeader.h"
#include "SceneTextureCompositor.h"
#include "../../PassDesc/PassDesc.h"


//外部
#include "../../../../Resource/Model/ModelStructure/Model.h"
#include "../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

SceneTextureCompositor::SceneTextureCompositor(RenderContext::NexusFieldProof proof_, const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_)
	:RenderContext::PassBehavior(proof_, desc_,pass_)
{

}

void SceneTextureCompositor::Update
(
	[[maybe_unused]] std::vector<Model> const& modelContainer_,
	CommandContext::RuntimeWrapper& cmdWrapper_
)
{

}
