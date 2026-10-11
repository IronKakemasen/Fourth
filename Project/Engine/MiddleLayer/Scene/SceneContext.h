#pragma once

class Nexus;
class CameraContextDiplomat;

class SceneContext
{

public:
	class SceneCreator;
	class SceneController;
	class SceneLibrary;

	struct NexusFieldProof;

	SceneContext(NexusFieldProof proof_);
	~SceneContext();


private:

	std::unique_ptr<SceneController> sceneController;

};

struct SceneContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};
