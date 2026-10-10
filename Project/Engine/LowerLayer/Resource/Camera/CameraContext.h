#pragma once

class Nexus;
class BufferContextDiplomat;
class CameraContextDiplomat;

class CameraContext
{

public:

	struct NexusFieldProof;
	struct AgentKey;

	//カメラのデータのバッチング処理を行う
	class CameraDataBatcher;
	//カメラのランタイムシステムを束ねたもの。1シーンに1つ存在
	class CameraFrontlineSystems;
	//CameraFrontlineSystemsの分配を行う
	class FrontlineSystemsDispatcher;

	class ExecutionAgent;

	CameraContext
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~CameraContext();

	auto& AccessDiplomat() { return diplomat; }

private:

	std::unique_ptr<FrontlineSystemsDispatcher> frontlineSystemsDispatcher;
	std::unique_ptr<CameraDataBatcher> cameraDataBatcher;
	std::unique_ptr<CameraContextDiplomat> diplomat;
	
};


struct CameraContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct CameraContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};


