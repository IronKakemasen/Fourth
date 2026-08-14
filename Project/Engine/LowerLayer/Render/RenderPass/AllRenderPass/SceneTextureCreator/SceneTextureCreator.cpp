#include "PreCompileHeader.h"
#include "SceneTextureCreator.h"
#include "../../PassDesc/PassDesc.h"

SceneTextureCreator::SceneTextureCreator(std::unique_ptr<RenderContext::PassDesc>&& desc_)
	:RenderContext::PassBehavior(std::move(desc_))
{

}
