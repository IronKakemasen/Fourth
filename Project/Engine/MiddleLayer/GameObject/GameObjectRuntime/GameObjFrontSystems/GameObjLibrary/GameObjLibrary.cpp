#include "PreCompileHeader.h"
#include "GameObjLibrary.h"
#include "../../../GameObjectStructure/GameObjectBehavior.h"

namespace
{
	auto const fileName = "GameObjLibrary.cpp";
}

GameObjectContext::FrontlineSystems::ObjLibrary::ObjLibrary(NexusFieldProof proof_)
{
	objMapCache = std::make_unique<std::unordered_map<std::string, std::pair<bool , std::vector<GameObjectBehavior*>>>>();
}

void GameObjectContext::FrontlineSystems::ObjLibrary::Sort(std::vector<std::string> const& priorityList_)
{
	SortByPriority(priorityList_);
}

std::vector<GameObjectBehavior*>& GameObjectContext::FrontlineSystems::ObjLibrary::RefObjContainer()
{
	return sortedByProority;
}

void GameObjectContext::FrontlineSystems::ObjLibrary::SortByPriority(std::vector<std::string> const& priorityList_)
{
	//文字列データから優先順位ソート
	//優先順位リストがちゃんと活用されたかチェック
	//オブジェの名前とリストに表記されている名前が一致している確認する
	
	//活用されなかったpriorityList_のオブジェ名
	std::vector < std::string > mismatchedList;

	sortedByProority.reserve(objUniqueMap.size());

	for (auto const& srcName_ : priorityList_)
	{
		bool hasMatched{};

		for (auto& [name, doneFlag_objPtrVec] : *objMapCache)
		{
			if (srcName_ == name)
			{
				for (auto* objPtr : doneFlag_objPtrVec.second)
				{
					sortedByProority.emplace_back(objPtr);
				}

				//格納済みです
				doneFlag_objPtrVec.first = true;
				//活用されました
				hasMatched = true;
			}
		}

		if (!hasMatched) mismatchedList.emplace_back(srcName_);
	}

	std::string log;
	for (auto const& mismatchedName: mismatchedList)
	{
		log += mismatchedName + ",";
	}

	ErrorMessageOutput::Assert::DetectError
	(
		mismatchedList.size() == 0,
		"ミスマッチなオブジェ優先順位名: " + log,
		fileName
	);


	//doneFlagが立ってない、つまり、初期化リストに記述されていないオブジェクトを
	//つめていく
	for (auto const& [name, doneFlag_objPtrVec] : *objMapCache)
	{
		if (doneFlag_objPtrVec.first) continue;

		for (auto* objPtr : doneFlag_objPtrVec.second)
		{
			sortedByProority.emplace_back(objPtr);
		}
	}

	//キャッシュデータ削除
	objMapCache.reset();

	ErrorMessageOutput::Assert::DetectError
	(
		objUniqueMap.size() == sortedByProority.size(),
		"objUniqueMapとsortedByProrityのサイズが一致していない(エンジンのせい)",
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
	(*objMapCache)[objName_].second.emplace_back(objPtr);
	(*objMapCache)[objName_].first = false;

	Logger::Log("Import: " + nameID, fileName);
}
