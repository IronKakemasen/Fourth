#pragma once
#include "../ModelDataCreator.h"
#include "../../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"

//外部
#include "../../../../../Buffer/BufferContextCmds.h"

class UploadStructuredBuffer;
struct UploadStructuredBufferDescription;

class ModelContext::ModelDataCreator::PerDrawDataBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	///モデルの個体ごとに送るデータの大本データのバッファを作成する
	///meshDataのほうは別クラスで作成済みなので、それ以外。
	///TransformMatrixContainer,MaterialContainer
	///そしてモデルの個体ごとに送るperDrawDataはルートコンスタンツなので、それの定数バッファも作成しちゃう
	static void CreatePerDrawConstntBuffer
	(
		BufferContext::BufferCreator* bufferCreator_,
		ModelDataBatcher* modelDataBatcher_,
		BufferContextCmds::CreateCBufferCmd& createCBufferCmd_
	);

		//以下ヘルパー
private:

	//ディスクの引数と同じだが、余計にインクルードしたくないため
	struct DescImitation
	{
		UINT const sizeOfStructure;
		UINT const sizeOfArr;
		std::string const bufferName;
	};

	//バッファのディスクを作って、uploadStructuredBuffer(ダブルバッファ)を作成
	//そのSrvHeapIndexのコンスタントバッファを作成
	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	static void Create
	(
		BufferContext::BufferCreator* bufferCreator_,
		ModelDataBatcher* modelDataBatcher_,
		BufferContextCmds::CreateCBufferCmd& createCBufferCmd_
	)
	{
		//バッファのディスク(厳密にはイミテーション)
		auto const bufferDesc = CreateDesc<bufferType>();
		
		//それをもとにUploadStructuredBufferを生成
		auto bufferID_bufferPtr = CreateBuffer(bufferDesc, bufferCreator_);

		///ランタイムで更新するために、その索引用としてバッファIDを見せてもらう
		modelDataBatcher_->ImportPerDrawBufferID<bufferType>
			(ModelDataBatcher::Local_InputBufferUniqueIDLicence{}, bufferID_bufferPtr.first);

		//作成したバッファのsrvHeapIndexをマッピングした定数バッファを作成
		PackageInConstanrBuffer(bufferID_bufferPtr.second, createCBufferCmd_, bufferType);

	}

	//UploadStructuredBufferDescのイミテーションを作成
	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	static DescImitation CreateDesc()
	{
		return DescImitation
		(
			ModelDataBatcher::BufferTypeTraits<bufferType>::kStructureSize,
			ModelDataBatcher::BufferTypeTraits<bufferType>::kArrSize,
			ModelDataBatcher::BufferTypeTraits<bufferType>::kBufferName
		);
	}

	//巨大データバッファ(UploadStructuredBuffer)を作成
	static std::pair<BufferUniqueID, UploadStructuredBuffer*> CreateBuffer
	(
		DescImitation const& descImitation,
		BufferContext::BufferCreator* bufferCreator_
	);

	//巨大データバッファのsrvHeapIndexを定数バッファに梱包
	static void PackageInConstanrBuffer
	(
		UploadStructuredBuffer* dstBuffer_,
		BufferContextCmds::CreateCBufferCmd& createCBufferCmd_,
		ConstantBuffers::ConstantBufferBindSlots dstSlot_
	);

	//srvHeapIndex抽出
	static std::array<SRVHeapIndex, UINT(ProjectConfig::Render::NumBuffer::kDoubleBuffer)>
		ExtractSrvHeapIndices(UploadStructuredBuffer* srcBuffer_);

	//ルートコンスタンツであるPerDrawIndicesの定数バッファを作成する
	static void CreatePerDrawCBuffer(BufferContextCmds::CreateCBufferCmd& createCBufferCmd_);

};

