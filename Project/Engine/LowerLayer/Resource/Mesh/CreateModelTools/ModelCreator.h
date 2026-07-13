#pragma once
#include "../MeshContext.h"


class MeshContext::ModelCreator
{

public:

	//モデルファイルからメッシュ情報を読み込む
	class ModelDataLoader;

	ModelCreator(MeshContext::InstanceKey key_);
	~ModelCreator();


private:
	std::unique_ptr<ModelDataLoader> modelDataLoader;
};

