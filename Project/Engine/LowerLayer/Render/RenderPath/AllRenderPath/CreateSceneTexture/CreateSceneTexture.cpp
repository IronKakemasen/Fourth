#include "PreCompileHeader.h"
#include "CreateSceneTexture.h"

CreateSceneTexture::CreateSceneTexture(RenderContext::NexusFieldProof proof_, std::string const& name_)
:PathBehavior::PathBehavior(proof_, name_)
{

}

void CreateSceneTexture::Update
(
	[[maybe_unused]] std::vector<std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>>> const& modelContainer_,
	RuntimeWrapper& cmdWrapper_
)
{

}
