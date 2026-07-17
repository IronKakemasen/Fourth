#pragma once
#include "../../MeshContext.h"

struct ModelDataAggregate;
struct ResourceMesh;
struct ResourrceMatrilal;
struct BufferCreator;


class MeshContext::ModelDataCreator
{

public:

	//モデルファイルからメッシュ情報を読み込む
	class ModelDataLoader;
	//モデルデータ管理クラス
	
	///全てのメッシュデータを作成する
	void CreateAllModelData(MeshContext::ModelSlotAllocator* allocator_);


	ModelDataCreator(MeshContext::InstanceKey key_);
	~ModelDataCreator();


private:

	//モデルファイルからモデルデータを読み込む
	std::unique_ptr<ModelDataLoader> modelDataLoader;
	//ファイル名がキーのメッシュデータバッファ配列上のインデックス
	std::unordered_map<std::string, MeshDetaID> meshDataIDLib;


	//モデルファイルが登録されているファイルから、ファイル名をキーとしてデータのポインタを
	std::unordered_map<std::string, std::string > LoadModelRegistry(std::string const registryFilePath_);
	//ローダーが全モデルファイルを読み込み、そのモデルデータのポインタを返す
	///被り無しのはず設計なので、被りがあった場合はアサートでとまる
	std::unordered_map<std::string, ModelDataAggregate*> LoadAllModelFiles();
	//メッシュデータのバッファを作成する
	void CreateMeshDataBuffer(const ResourceMesh& data_);
};

