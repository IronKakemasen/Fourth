#include "PreCompileHeader.h"
#include "GameObjLibrary.h"
#include "../../../GameObjectStructure/GameObjectBehavior.h"

namespace
{
	auto const fileName = "GameObjLibrary.cpp";
}

GameObjectContext::FrontlineSystems::ObjLibrary::ObjLibrary(NexusFieldProof proof_)
{
	objMapCache = std::make_unique<std::unordered_map<std::string, std::vector<GameObjectBehavior*>>>();
}


void GameObjectContext::FrontlineSystems::ObjLibrary::SortByPriority(std::vector<std::string> const& priorityList_)
{
	//文字列データから優先順位ソート
	for (auto const& srcName_ : priorityList_)
	{
		for (auto const& [name, objPtrVec] : *objMapCache)
		{
			if (srcName_ == name)
			{
				for (auto* objPtr : objPtrVec)
				{
					sortedByProority.emplace_back(objPtr);
				}
			}
		}
	}

	//キャッシュデータ削除
	objMapCache.reset();

	ErrorMessageOutput::Assert::DetectError
	(
		objUniqueMap.size() == sortedByProority.size(),
		"あるオブジェの優先リストとゲームオブジェクトリストの名前が一致してない可能性大",
		fileName
	);

	Logger::Log("Sorted by Priority", fileName);
}

void GameObjectContext::FrontlineSystems::ObjLibrary::Import
(
	std::string const& objName_,
	std::unique_ptr<GameObjectBehavior>&& obj_
) 
{
	auto const nameID = objName_ + "[" + std::to_string(objUniqueMap.size()) + "]";

	auto* objPtr = obj_.get();

	//オブジェおおもと
	objUniqueMap[nameID] = std::move(obj_);
	//単一オブジェ検索用
	forSerchContainer[objName_] = objPtr;
	//優先度ソート用
	(*objMapCache)[objName_].emplace_back(objPtr);

	Logger::Log("Import: " + nameID, fileName);
}
