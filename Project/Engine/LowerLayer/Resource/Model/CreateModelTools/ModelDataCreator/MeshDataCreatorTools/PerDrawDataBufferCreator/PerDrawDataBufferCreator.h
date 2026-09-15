#pragma once
#include "../../ModelDataCreator.h"
#include "../../../../ModelContextRuntime/ModelDataBatcher/ModelDataBatcher.h"

//外部
#include "../../../../../../Buffer/BufferContextCmds.h"

class UploadStructuredBuffer;
struct UploadStructuredBufferDescription;

class ModelContext::ModelDataCreator::PerDrawDataBufferCreator
{
	friend class ModelContext::ModelDataCreator;

	//ディスクの引数と同じだが、余計にインクルードしたくないため
	struct DescParam
	{
		UINT const sizeOfStructure;
		UINT const sizeOfArr;
		std::string const bufferName;
	};

	static void CreatePerDrawConstntBuffer
	(
		BufferContext::BufferCreator* bufferCreator_,
		BufferContextCmds::CreateCBufferCmd createCBufferCmd_,
		ModelDataBatcher* modelDataBatcher_
	);

		//以下ヘルパー
private:

	//バッファのディスクを作って、uploadStructuredBuffer(ダブルバッファ)を作成
	template<ModelDataBatcher::BufferType bufferType>
	static std::array<SRVHeapIndex, UINT(ProjectConfig::Render::NumBuffer::kDoubleBuffer)> Create
	(
		BufferContext::BufferCreator* bufferCreator_,
		ModelDataBatcher* modelDataBatcher_
	)
	{
		//バッファのディスク(厳密にはイミテーション)
		auto const bufferDesc = CreateDesc<bufferType>();
		
		//それをもとにUploadStructuredBufferを生成
		auto bufferID_bufferPtr = CreateBuffer(bufferDesc, bufferCreator_);

		///ランタイムで更新するために、その索引用としてバッファIDを見せてもらう
		modelDataBatcher_->ImportPerDrawBufferID<bufferType>
			(ModelDataBatcher::Local_InputBufferUniqueIDLicence{}, bufferID_bufferPtr.first);

		//作成したバッファのsrvHeapIndexを出力
		///あとで、perDrawBufferの定数バッファを作成するために必要

		//SRVHeapIndexを抽出
		return 	ExtractSrvHeapIndices(bufferID_bufferPtr.second);
	}


	template<ModelDataBatcher::BufferType bufferType>
	static DescParam CreateDesc()
	{
		return DescParam
		(
			ModelDataBatcher::BufferTypeTraits<bufferType>::kStructureSize,
			ModelDataBatcher::BufferTypeTraits<bufferType>::kArrSize,
			ModelDataBatcher::BufferTypeTraits<bufferType>::kBufferName
		);
	}

	static std::pair<BufferUniqueID, UploadStructuredBuffer*> CreateBuffer
	(
		DescParam const& descParam_,
		BufferContext::BufferCreator* bufferCreator_
	);

	static void PackageInConstanrBuffer
	(
		UploadStructuredBuffer* dstBuffer_,
		BufferContextCmds::CreateCBufferCmd& createCBufferCmd_,
		ConstantBuffers::ConstantBufferBindSlots dstSlot_
	);

	static std::array<SRVHeapIndex, UINT(ProjectConfig::Render::NumBuffer::kDoubleBuffer)>
		ExtractSrvHeapIndices(UploadStructuredBuffer* srcBuffer_);

};

