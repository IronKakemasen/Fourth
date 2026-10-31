#include "PreCompileHeader.h"
#include "ObjDataLoader.h"

std::vector<std::string> GameObjectContext::FrontlineSystems::FrontlineSystems::GameObjController::ObjDataLoader::LoadUpdatePriority(std::string const& sceneName_)
{
	auto* miyajison = Miyajison::Get();

	return miyajison->LoadData<std::vector<std::string>>(sceneName_, { DataKey::kGameObjectUpdatePriority });

}