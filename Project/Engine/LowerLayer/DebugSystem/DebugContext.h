#pragma once

class Nexus;


class DebugContext
{
public:

	//ネクサスフィールドの証
	struct NexusFieldProof;

	DebugContext(NexusFieldProof proof_);
	~DebugContext();

private:

	class RuntimeDebugger;

	std::unique_ptr<RuntimeDebugger> runtimeDebugger;
};

struct DebugContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

