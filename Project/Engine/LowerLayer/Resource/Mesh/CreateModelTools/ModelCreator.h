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

	//モデルファイルからメッシュデータを読み込む
	std::unique_ptr<ModelDataLoader> modelDataLoader;
	//モデルファイルが登録されているファイルから、ファイル名をキーとしてファイルパスを保存する
	std::unordered_map<std::string, std::string > modelFileName_pathLib;

	//モデル登録ファイルから何が登録されているか読み込む
	void LoadModelRegistry(std::string const registryFilePath_);
	//全モデルファイルを読み込む
	void LoadAllModelFiles();
};

