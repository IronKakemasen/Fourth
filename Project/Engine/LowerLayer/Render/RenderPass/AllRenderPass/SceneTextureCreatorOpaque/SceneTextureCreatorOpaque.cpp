#include "PreCompileHeader.h"
#include "SceneTextureCreatorOpaque.h"
#include "../../PassDesc/PassDesc.h"

SceneTextureCreatorOpaque::SceneTextureCreatorOpaque(RenderContext::NexusFieldProof proof_ , const RenderContext::PassDesc& desc_)
	:RenderContext::PassBehavior(proof_,desc_)
{

}
