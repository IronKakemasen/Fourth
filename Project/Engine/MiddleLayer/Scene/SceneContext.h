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
	//シーンの制御、シーンデータのバッチングなどをランタイムで行う
	class ScenePipeline;

	class ExecutionAgent;

	struct NexusFieldProof;
	struct AgentKey;

	SceneContext(NexusFieldProof proof_);
	~SceneContext();

	auto& AccessDiplomat() { return diplomat; }

private:

	std::unique_ptr<SceneLibrary> sceneLibrary;
	std::unique_ptr<SceneCreator> sceneCreator;
	std::unique_ptr<ScenePipeline> scenePipeline;

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
