#pragma once

class Nexus;

class GameObjectContext
{
	//ゲームオブジェクトを作成する
	class GameObjectCreator;
	//ゲームオブジェクトのセットアップを行う
	class GameObjSetupper;

public:

	//1シーンが一つ持つ、前線システム群
	class FrontlineSystems;
	//FrontlineSystemsをシーンに渡す
	class ObjFSDispatcher;

	struct NexusFieldProof;
	struct AgentKey;

	class ExecutionAgent;

	GameObjectContext(NexusFieldProof proof_);
	~GameObjectContext();


private:

	std::unique_ptr<GameObjectCreator> gameObjectCreator;
	std::unique_ptr<GameObjSetupper> gameObjSetupper;
	std::unique_ptr<ObjFSDispatcher> objFSDispatcher;
};


struct GameObjectContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};

struct GameObjectContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;

};



