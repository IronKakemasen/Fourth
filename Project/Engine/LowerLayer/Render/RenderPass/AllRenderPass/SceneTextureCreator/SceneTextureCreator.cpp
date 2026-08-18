#include "PreCompileHeader.h"
#include "SceneTextureCreator.h"
#include "../../PassDesc/PassDesc.h"

SceneTextureCreator::SceneTextureCreator(RenderContext::NexusFieldProof proof_ , const RenderContext::PassDesc& desc_)
	:RenderContext::PassBehavior(proof_,desc_)
{

}
