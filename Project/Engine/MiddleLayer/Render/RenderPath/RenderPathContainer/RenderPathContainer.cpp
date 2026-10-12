#include "PreCompileHeader.h"
#include "RenderPathContainer.h"
#include "../AllRenderPath/AllPathInclude.h"


RenderContext::RenderPathContainer::RenderPathContainer(NexusFieldProof proof_)
{

}


void RenderContext::RenderPathContainer::Import(NexusFieldProof proof_, std::unique_ptr<PathBehavior>&& path_)
{
	container.emplace_back(std::move(path_));
}
