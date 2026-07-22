#pragma once
#include "../../MeshContext.h"

//外部
#include "../../../Buffer/BufferContext.h"

struct ModelDataAggregate;
struct ResourceMesh;
struct ResourrceMatrilal;


class MeshContext::ModelDataCreator
{
	using BufferContextTools = std::tuple
	<
		BufferContext::BufferCreator*,
		BufferContext::BufferCollector*,
		BufferContext::BufferUploader*
	>;

protected:

	//MeshDataBufferのユニークIDを列挙するため
	struct MeshDataBufferUniqueIDGroup
	{
		BufferUniqueID verticesGPUID{};
		BufferUniqueID uniqueVertsIndicesID{};
		BufferUniqueID meshletsID{};
		BufferUniqueID primIndicesID{};
	};


private:

	//モデルの理事ストリーファイルを読み込んで、キーがファイル名のバリューがファイルパスであるマップを返す
	class ModelRegistryLoader;
	//頂点データをGPUように変換したり、BufferUniqueIDからstructuredBufferポインタに変換する
	class DataTransducer;
	//メッシュデータのバッファのアップロードを行う
	class MeshDataBufferUploader;

public:

	//メッシュデータのバッファを作成し,そのメッシュデータのバッファユニークID群を返す
	class MeshDataBufferCreator;

	
	///全てのメッシュデータのバッファを作成し、
	///メッシュデータのバッファユニークID群の配列のバッファも作成
	void CreateAllModelData
	(
		MeshContext::ModelSlotAllocator* allocator_,
		BufferContextDiplomat* bufferContextDiplomat_
	);


	ModelDataCreator
	(
		MeshContext::InstanceKey key_, 
		MeshContext::ModelSlotAllocator* allocator_, 
		BufferContextDiplomat* bufferContextDiplomat_
	);

	~ModelDataCreator();


private:

	//モデルファイルからモデルデータを読み込む
	std::unique_ptr<ModelDataLoader> modelDataLoader;


	//ローダーが全モデルファイルを読み込み、そのモデルデータのポインタを返す
	///被り無しのはず設計なので、被りがあった場合はアサートでとまる
	std::unordered_map<std::string, ModelDataAggregate*> LoadAllModelFiles();
	
	//バッファコンテキストクラスからツールをお借りする
	BufferContextTools BorrowBufferContextTools(BufferContextDiplomat* bufferContextDiplomat_);



};

