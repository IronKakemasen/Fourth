#pragma once

class Nexus;

class MeshContext
{
public:

	struct InstanceKey;

	MeshContext(const InstanceKey& key_);
	~MeshContext();


private:
	//MeshLoaderを使ってモデルを生成する。
	class ModelCreator;

	std::unique_ptr<ModelCreator> modelCreator;
};

struct MeshContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
