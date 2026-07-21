#pragma once
#include "../../MeshContext.h"

//外部
#include "../../../Buffer/BufferContext.h"
#include "../../../../../../Assets/Shared/StructuredBuffer.h"

struct ModelDataAggregate;
struct ResourceMesh;
struct ResourrceMatrilal;
class StaticStructuredBuffer;


class MeshContext::ModelDataCreator
{
	//MeshDataBufferのユニークIDを列挙するため
	struct MeshDataBufferUniqueIDGroup
	{
		BufferUniqueID verticesID{};
		BufferUniqueID uniqueVertsIndicesID{};
		BufferUniqueID meshletsID{};
		BufferUniqueID primIndicesID{};
	};

	//メッシュデータの静的ストラクチャードバッファのアドレス群
	struct MeshDataStructuredBufferGroup
	{
		///STB = StructuredBuffer
		StaticStructuredBuffer* verticesSTB;
		StaticStructuredBuffer* uniqueVertsIndicesSTB;
		StaticStructuredBuffer* meshletsSTB;
		StaticStructuredBuffer* primIndicesSTB;
	};

	using BufferContextTools = std::tuple
	<
		BufferContext::BufferCreator*,
		BufferContext::BufferCollector*,
		BufferContext::BufferDispatcher*,
		BufferContext::BufferUploader*
	>;


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
	//ファイル名がキーのメッシュデータバッファ配列上のインデックス
	std::unordered_map<std::string, MeshDetaID> meshDataIDLib;






	//モデルファイルが登録されているファイルから、ファイル名をキーとしてデータのポインタを
	std::unordered_map<std::string, std::string > LoadModelRegistry(std::string const registryFilePath_);
	
	//ローダーが全モデルファイルを読み込み、そのモデルデータのポインタを返す
	///被り無しのはず設計なので、被りがあった場合はアサートでとまる
	std::unordered_map<std::string, ModelDataAggregate*> LoadAllModelFiles();
	
	//バッファコンテキストクラスからツールをお借りする
	BufferContextTools BorrowBufferContextTools(BufferContextDiplomat* bufferContextDiplomat_);

	//メッシュデータのバッファを作成する
	///そのメッシュデータのバッファユニークID群を返す
	std::vector<MeshDataBufferUniqueIDGroup> CreateMeshDataBuffer
	(
		const std::vector<ResourceMesh>& data_,
		BufferContext::BufferCreator* bufferCreator_,
		BufferContext::BufferCollector* bufferCollector_,
		std::string meshDataName_,
		MeshDetaID& meshDataID_
	);

	///バッファユニークIDが指すバッファのアドレス群を取得
	std::vector<MeshDataStructuredBufferGroup> BufferUniqueID_To_BufferPtr
	(
		const std::vector<MeshDataBufferUniqueIDGroup>& uniqueIDGroup_, 
		BufferContext::BufferDispatcher* bufferDispatcher_
	);




	//メッシュデータのバッファをアップロードし、
	//そのバッファ群のMeshDataSRVHeapIndexGroupGPUCPUを返す


};

