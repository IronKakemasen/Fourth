#pragma once
#include "../../MeshContext.h"

//外部
#include "../../../Buffer/BufferContext.h"

struct ModelDataAggregate;
class StaticStructuredBuffer;

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

	//モデルの理事ストリーファイルを読み込んで、キーがファイル名のバリューがファイルパスであるマップを返す
	class ModelRegistryLoader;
	//頂点データをGPU用に変換したり、BufferUniqueIDからstructuredBufferポインタに変換する
	class DataTransducer;
	//メッシュデータのバッファのアップロードを行う
	class MeshDataBufferUploader;
	//メッシュデータバッファのsrvHeapIndexを詰めていく
	class MeshDataBufferSRVHeapIndexGroupPackager;

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
		NexusFieldProof proof_,
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

