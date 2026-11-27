#include "PreCompileHeader.h"
#include "SceneConfigLoder.h"

std::unique_ptr<SceneBehavior::SceneConfig> 
SceneContext::SceneCreator::SceneConfigLoder::Load(std::string const& sceneName_)
{
	auto* miyajison = Miyajison::Get();


	return std::make_unique<SceneBehavior::SceneConfig>
	(
		miyajison->LoadData<bool>(sceneName_, { DataKey::kAlwaysUpdateStaticB })
	);
}
