#pragma once

class Nexus;
class BufferContextDiplomat;

class MeshContext
{
public:
	//モデルを生成する。
	class ModelDataCreator;
	//モデルファイルからメッシュ情報を読み込む
	class ModelDataLoader;
	class ModelSlotAllocator;

	//自身の生成キー
	struct NexusFieldProof;

	MeshContext(NexusFieldProof proof_, BufferContextDiplomat* bufferContextDiplomat_);
	~MeshContext();


private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;

};

struct MeshContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};
