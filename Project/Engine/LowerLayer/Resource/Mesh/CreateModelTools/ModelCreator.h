#pragma once
#include "../MeshContext.h"

struct ModelDataAggregate;

class MeshContext::ModelCreator
{

public:

	//モデルファイルからメッシュ情報を読み込む
	class ModelDataLoader;
	//モデルデータ管理クラス
	
	//


	ModelCreator(MeshContext::InstanceKey key_);
	~ModelCreator();


private:

	//モデルファイルからメッシュデータを読み込む
	std::unique_ptr<ModelDataLoader> modelDataLoader;

	//モデルファイルが登録されているファイルから、ファイル名をキーとしてファイルパスを保存する
	std::unordered_map<std::string, std::string > LoadModelRegistry(std::string const registryFilePath_);
	//全モデルファイルを読み込む
	std::unordered_map<std::string, ModelDataAggregate*> LoadAllModelFiles();
	//モデルデータのバッファを作成する

};

