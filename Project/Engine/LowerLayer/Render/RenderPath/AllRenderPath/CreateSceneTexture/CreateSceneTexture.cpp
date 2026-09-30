#include "PreCompileHeader.h"
#include "CreateSceneTexture.h"
#include "../../../RenderPass/AllRenderPass/AllPassInclude.h"


CreateSceneTexture::CreateSceneTexture(RenderContext::NexusFieldProof proof_, std::string const& name_)
:PathBehavior::PathBehavior(proof_, name_)
{

}

void CreateSceneTexture::Run
(
	std::unordered_map<uint64_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
	RenderStateComponent::FillMode const modelFillMode_,
	RenderContext::PSO_PoolDispatcher& psoDispatcher_,
	RuntimeWrapper& cmdWrapper_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{
	//SceneOpaque -> SceneCompositor
	
	CallPassUpdate<SceneOpaque>(modelContainer_,modelFillMode_,psoDispatcher_,cmdWrapper_,bufDispatcher_);
	CallPassUpdate<SceneCompositor>(modelContainer_, modelFillMode_, psoDispatcher_, cmdWrapper_, bufDispatcher_);


}
