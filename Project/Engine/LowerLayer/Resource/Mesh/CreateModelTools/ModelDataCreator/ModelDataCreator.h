#pragma once
#include "../../MeshContext.h"

//外部
#include "../../../Buffer/BufferContext.h"

struct ModelDataAggregate;
struct ResourceMesh;
struct ResourrceMatrilal;
class StaticStructuredBuffer;


class MeshContext::ModelDataCreator
{
	using BufferContextTools = std::tuple
	<
		BufferContext::BufferCreator*,
		BufferContext::BufferCollector*,
		BufferContext::BufferDispatcher*,
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

	//メッシュデータの静的ストラクチャードバッファのアドレス群
	struct MeshDataStructuredBufferGroup
	{
		///STB = StructuredBuffer
		StaticStructuredBuffer* verticesGPUSTB;
		StaticStructuredBuffer* uniqueVertsIndicesSTB;
		StaticStructuredBuffer* meshletsSTB;
		StaticStructuredBuffer* primIndicesSTB;
	};

private:

	//モデルの理事ストリーファイルを読み込んで、キーがファイル名のバリューがファイルパスであるマップを返す
	class ModelRegistryLoader;
	//メッシュデータのバッファを作成し,そのメッシュデータのバッファユニークID群を返す
	class MeshDataBufferCreator;
	//頂点データをGPUように変換したり、BufferUniqueIDからstructuredBufferポインタに変換する
	class DataTransducer;
	//メッシュデータのバッファのアップロードを行う
	class MeshDataBufferUploader;

public:

	//モデルファイルからメッシュ情報を読み込む
	class ModelDataLoader;
	//モデルデータ管理クラス
	
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
	//ファイル名がキーのメッシュデータバッファ配列上のインデックスがバリュー
	std::unordered_map<std::string, std::vector<MeshDataID>> meshDataIDLib;


	//ローダーが全モデルファイルを読み込み、そのモデルデータのポインタを返す
	///被り無しのはず設計なので、被りがあった場合はアサートでとまる
	std::unordered_map<std::string, ModelDataAggregate*> LoadAllModelFiles();
	
	//バッファコンテキストクラスからツールをお借りする
	BufferContextTools BorrowBufferContextTools(BufferContextDiplomat* bufferContextDiplomat_);



};

