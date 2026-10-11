#pragma once

class Nexus;

class SceneContextDiplomat;

class SceneContext
{
	//シーンのユニークを保管
	class SceneLibrary;

public:
	//シーンを作成する
	class SceneCreator;
	//ランタイムでシーンの制御を行う
	class SceneController;
	//そのシーンで使用しているデータのバッチング場
	class SceneDataBatchingPlace;

	class ExecutionAgent;

	struct NexusFieldProof;
	struct AgentKey;

	SceneContext(NexusFieldProof proof_);
	~SceneContext();

	auto& AccessDiplomat() { return diplomat; }

private:

	std::unique_ptr<SceneLibrary> sceneLibrary;
	std::unique_ptr<SceneController> sceneController;
	std::unique_ptr<SceneCreator> sceneCreator;

	std::unique_ptr<SceneContextDiplomat> diplomat;
};

struct SceneContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};

struct SceneContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;

};
