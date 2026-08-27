#include "PreCompileHeader.h"
#include "SceneTextureCreatorOpaque.h"
#include "../../PassDesc/PassDesc.h"

SceneTextureCreatorOpaque::SceneTextureCreatorOpaque(RenderContext::NexusFieldProof proof_ , const RenderContext::PassDesc& desc_, RenderPassComponent::Pass pass_)
	:RenderContext::PassBehavior(proof_,desc_,pass_)
{

}
