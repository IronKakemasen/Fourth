#include "PreCompileHeader.h"
#include "SceneTextureCreatorOpaque.h"
#include "../../PassDesc/PassDesc.h"

//外部
#include "../../../../Resource/Model/ModelStructure/Model.h"
#include "../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

SceneTextureCreatorOpaque::SceneTextureCreatorOpaque(RenderContext::NexusFieldProof proof_ , const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_)
	:RenderContext::PassBehavior(proof_,desc_,pass_)
{

}

void SceneTextureCreatorOpaque::Update
(
	[[maybe_unused]] std::vector<Model> const& modelContainer_,
	CommandContext::RuntimeWrapper& cmdWrapper_
)
{

}
