#pragma once

class Nexus;

class MeshContext
{
protected:

	//ファイルからメッシュ情報を読み込む
	class ModelDataLoader;

public:

	struct InstanceKey;
	//MeshLoaderを使ってモデルを生成する。
	class ModelCreator;

};

struct MeshContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
