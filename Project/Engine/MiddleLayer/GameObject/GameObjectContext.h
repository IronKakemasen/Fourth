#pragma once

class Nexus;

class GameObjectContext
{
	//ゲームオブジェクトを作成する
	class GameObjectCreator;
	//シーンデータからゲームオブジェクトの情報をインプットする
	class ObjDataLoader;

public:

	//1シーンが一つ持つ、前線システム群
	class FrontlineSystems;

	struct NexusFieldProof;

	GameObjectContext(NexusFieldProof proof_);
	~GameObjectContext();


private:


};


struct GameObjectContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};