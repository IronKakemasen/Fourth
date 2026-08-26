#include "PreCompileHeader.h"
#include "SceneTextureCompositor.h"
#include "../../PassDesc/PassDesc.h"

SceneTextureCompositor::SceneTextureCompositor(RenderContext::NexusFieldProof proof_, const RenderContext::PassDesc& desc_)
	:RenderContext::PassBehavior(proof_, desc_)
{

}
