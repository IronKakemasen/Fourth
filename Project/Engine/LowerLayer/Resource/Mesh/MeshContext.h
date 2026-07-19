#pragma once

class Nexus;
class BufferContext;

class MeshContext
{
public:
	//モデルを生成する。
	class ModelDataCreator;
	class ModelSlotAllocator;

	//自身の生成キー
	struct InstanceKey;

	MeshContext(const InstanceKey& key_, BufferContext* bufferContext_);
	~MeshContext();


private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;

};

struct MeshContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
