#pragma once

class Nexus;
class BufferContextDiplomat;

class MeshContext
{
public:
	//モデルを生成する。
	class ModelDataCreator;
	class ModelSlotAllocator;

	//自身の生成キー
	struct InstanceKey;

	MeshContext(const InstanceKey& key_, BufferContextDiplomat* bufferContextDiplomat_);
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
