#pragma once
#include "../GameObjFrontlineSystems.h"

class GameObjectBehavior;

class GameObjectContext::FrontlineSystems::ObjLibrary
{
public:

	ObjLibrary(NexusFieldProof proof_);

	void Import
	(
		std::string const& objName_,
		std::unique_ptr<GameObjectBehavior>&& obj_
	);

	//名前からゲームオブジェクトを検索する
	std::vector<GameObjectBehavior*>& FindGameObj(std::string const& objName_);
		
	//更新優先順にソートされたオブジェコンテナの参照を返す
	std::vector<GameObjectBehavior*>& RefSortedObjContainer();
	//とその名簿
	std::vector<std::string> const& WatchSortedObjContainerNameList()const;

	//objUniqueMapを返す
	std::unordered_map<std::string, std::unique_ptr<GameObjectBehavior>>& RefObjUniqueMap();

	//ソートする
	void Sort(std::vector<std::string> const& priorityList_);

private:

	//本体のマップ
	std::unordered_map<std::string, std::unique_ptr<GameObjectBehavior>> objUniqueMap;
	//更新優先度ソート用のキャッシュ
	std::unique_ptr<std::unordered_map<std::string, std::pair<bool, std::vector<GameObjectBehavior*>>>> objMapCache;
	//更新優先度順に並び替えられたコンテナ
	std::vector<GameObjectBehavior*> sortedByProority;
	//とその名簿。デバッグUI表示に利用
	std::vector<std::string> sortedByProorityNameList;

	//ゲームオブジェクト検索用マップ
	std::unordered_map<std::string, std::vector<GameObjectBehavior*>> forSearchObjMap;


	//優先順位で並び替える
	void SortByPriority(std::vector<std::string> const& priorityList_);

};

