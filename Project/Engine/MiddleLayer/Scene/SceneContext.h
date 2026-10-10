#pragma once

class Nexus;

class SceneContext
{
	class SceneController;


public:

	struct NexusFieldProof;

	SceneContext(NexusFieldProof proof_);


private:



};

struct SceneContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};
