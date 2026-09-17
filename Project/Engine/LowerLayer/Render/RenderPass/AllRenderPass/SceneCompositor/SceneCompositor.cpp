#include "PreCompileHeader.h"
#include "SceneCompositor.h"
#include "../../PassDesc/PassDesc.h"


//外部
#include "../../../../Resource/Model/ModelStructure/Model.h"
#include "../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

SceneCompositor::SceneCompositor(RenderContext::NexusFieldProof proof_, const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_)
	:RenderContext::PassBehavior(proof_, desc_,pass_)
{

}

void SceneCompositor::Update
(
	[[maybe_unused]] std::vector<Model> const& modelContainer_,
	CommandContext::RuntimeWrapper& cmdWrapper_
)
{

}
