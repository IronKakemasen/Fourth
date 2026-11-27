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

std::vector<GameObjectBehavior*>& GameObjectContext::FrontlineSystems::ObjLibrary::RefSortedObjContainer()
{
	return sortedByProority;
}

std::vector<std::string> const& GameObjectContext::FrontlineSystems::ObjLibrary::WatchSortedObjContainerNameList()const
{
	return sortedByProorityNameList;
}

std::unordered_map<std::string, std::unique_ptr<GameObjectBehavior>>& GameObjectContext::FrontlineSystems::ObjLibrary::RefObjUniqueMap()
{
	return objUniqueMap;
}


void GameObjectContext::FrontlineSystems::ObjLibrary::SortByPriority(std::vector<std::string> const& priorityList_)
{
	//文字列データから優先順位ソート
	//優先順位リストがちゃんと活用されたかチェック
	//オブジェの名前とリストに表記されている名前が一致している確認する
	
	//活用されなかったpriorityList_のオブジェ名
	std::vector < std::string > mismatchedList;

	sortedByProority.reserve(objUniqueMap.size());
	sortedByProorityNameList.reserve(objUniqueMap.size());

	for (auto const& srcName_ : priorityList_)
	{
		auto it = objMapCache->find(srcName_);
		if (it == objMapCache->end())
		{
			mismatchedList.emplace_back(srcName_);
			continue;
		}


#ifndef NDEBUG

		UINT cnt{};

#endif // !NDEBUG

		auto& [done, objects] = it->second;
		for (auto* objPtr : objects)
		{
			sortedByProority.emplace_back(objPtr);

#ifndef NDEBUG

			//デバッグUI表示用に記録しておく
			auto objName = srcName_ + std::to_string(cnt++);
			sortedByProorityNameList.emplace_back(objName);

#endif // !NDEBUG

		}

		done = true;
	}

#ifdef _DEBUG

	std::string log;

	for (auto const& mismatchedName : mismatchedList)
	{
		log += mismatchedName + ",";
	}
	ErrorMessageOutput::Assert::DetectError
	(
		mismatchedList.size() == 0,
		"ミスマッチなオブジェ優先順位名: " + log,
		fileName
	);

#endif // _DEBUG

	//doneFlagが立ってない、つまり、初期化リストに記述されていないオブジェクトを
	//つめていく
	for (auto const& [name, doneFlag_objPtrVec] : *objMapCache)
	{
		if (doneFlag_objPtrVec.first) continue;

#ifndef NDEBUG

		UINT cnt{};

#endif // !NDEBUG

		for (auto* objPtr : doneFlag_objPtrVec.second)
		{
			sortedByProority.emplace_back(objPtr);

#ifndef NDEBUG

			//デバッグUI表示用に記録しておく
			auto objName = name + std::to_string(cnt++);
			sortedByProorityNameList.emplace_back(objName);

#endif // !NDEBUG

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

std::vector<GameObjectBehavior*>& GameObjectContext::FrontlineSystems::ObjLibrary::FindGameObj(std::string const& objName_)
{
#ifdef _DEBUG
	auto& objects = forSearchObjMap[objName_];

	ErrorMessageOutput::Assert::DetectError
	(
		objects.size() > 0,
		objName_ + "こんな名前のゲームオブジェクトは存在しねぇ",
		fileName
	);

	return objects;

#endif // DEBUG

	return forSearchObjMap[objName_];
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
	
	//オブジェ検索用
	forSearchObjMap[objName_].emplace_back(objPtr);

	//優先度ソート用
	(*objMapCache)[objName_].second.emplace_back(objPtr);
	(*objMapCache)[objName_].first = false;

	Logger::Log("Import: " + nameID, fileName);
}
