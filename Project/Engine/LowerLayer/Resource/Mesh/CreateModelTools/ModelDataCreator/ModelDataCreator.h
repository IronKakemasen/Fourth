#pragma once
#include "../../MeshContext.h"

//外部
#include "../../../Buffer/BufferContext.h"

struct ModelDataAggregate;

class MeshContext::ModelDataCreator
{
	using BufferContextTools = std::tuple
	<
		BufferContext::BufferCreator*,
		BufferContext::BufferCollector*,
		BufferContext::BufferUploader*,
		BufferContext::BufferDispatcher*
	>;

protected:

	//MeshDataBufferのユニークIDを列挙するため
	struct MeshDataBufferUniqueIDGroup
	{
		BufferUniqueID verticesGPU{};
		BufferUniqueID uniqueVertsIndices{};
		BufferUniqueID meshlets{};
		BufferUniqueID primIndices{};
	};

private:

	//メッシュデータのバッファを作成し,そのメッシュデータのバッファユニークID群を返す
	class MeshDataBufferCreator;
	//モデルの理事ストリーファイルを読み込んで、キーがファイル名のバリューがファイルパスであるマップを返す
	class ModelRegistryLoader;
	//頂点データをGPU用に変換したり、BufferUniqueIDからstructuredBufferポインタに変換する
	class DataTransducer;
	//メッシュデータのバッファのアップロードを行う
	class MeshDataBufferUploader;
	//メッシュデータバッファのsrvHeapIndex群を詰めていく
	class MeshDataBufferSRVHeapIndexGroupPackager;
	//メッシュデータバッファsrvHeapIndexGroup配列のバッファを作る
	class MeshDataSRVHeapIndexGroupContainerBufferCreator;

public:


	///全てのメッシュデータのバッファを作成してアップロードし、
	///キー(ファイル名)とメッシュデータバッファのsrvHapIndex群を紐づける
	///全メッシュデータバッファのsrvHeapIndex群のコンテナのバッファも作成してアップロードし、
	///そのsrvHeapIndexをMeshSlotAllocatorが受け取る
	void CreateAllModelData
	(
		MeshContext::ModelSlotAllocator* allocator_,
		BufferContextDiplomat* bufferContextDiplomat_
	);

	ModelDataCreator
	(
		NexusFieldProof proof_,
		std::unique_ptr<ModelDataLoader>&& modelDataLoader_,
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

