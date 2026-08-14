#include "PreCompileHeader.h"
#include "SceneTextureCreator.h"
#include "../../PassDesc/PassDesc.h"

SceneTextureCreator::SceneTextureCreator(RenderContext::Local_CreateRenderPassLicence licence_, const RenderContext::PassDesc& desc_)
	:RenderContext::PassBehavior(licence_,desc_)
{

}
