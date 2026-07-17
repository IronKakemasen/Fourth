#pragma once

class Nexus;

class MeshContext
{
public:

	//モデルを生成する。
	class ModelDataCreator;
	//自身の生成キー
	struct InstanceKey;

	MeshContext(const InstanceKey& key_);
	~MeshContext();


private:
	class ModelSlotAllocator;


	std::unique_ptr<ModelDataCreator> modelDataCreator;
};

struct MeshContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
