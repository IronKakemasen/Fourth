#pragma once

class Nexus;

class SceneContextDiplomat;

class SceneContext
{
	//シーンを作成する
	class SceneCreator;

public:
	//シーンの制御、シーンデータのバッチングなどをランタイムで行う
	class ScenePipeline;
	class ExecutionAgent;

	struct NexusFieldProof;
	struct AgentKey;

	SceneContext(NexusFieldProof proof_);
	~SceneContext();

	auto& AccessDiplomat() { return *diplomat; }

private:

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
