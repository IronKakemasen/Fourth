#pragma once
#include "BufferCollector/BufferCollector.h"
#include "BufferAssembler/BufferAssembler.h"
#include "../BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../BufferDefinition/AllBuffersInclude.h"

class BufferContext::BufferCreator
{
	template<typename DescType>
	struct DescTypeTraits;


public:

	BufferCreator
	(
		BufferContext::NexusFieldProof proof_,
		BufferContext::ResourceCreator* resourceCreator_,
		DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
		BufferCollector* collector_,
		BufferDispatcher* dispatcher_
	);

	~BufferCreator();

	//生成したバッファの管理を請け負います
	///任意のタイミングでcollectorのDistribute()をやってもらわな困る
	template<typename DescType>
	[[nodiscard]] BufferUniqueID Create(const DescType& desc_, const std::string& name_)
	{
		using ActualBufferType = typename DescTypeTraits<DescType>::Type;

		std::unique_ptr<ActualBufferType> buffer = assembler->Assemble<ActualBufferType>(desc_, name_);
		
		//生成数 = IDとす
		BufferUniqueID dispatchUniqueID = BufferUniqueID(generateBufferSum++);

		//コレクターに登録
		collector->Register<ActualBufferType>
		(
			BufferContext::BufferCollector::RegisterLicence{}, 
			std::move(buffer), 
			dispatchUniqueID
		);

		//バッファユニークIDを返す
		return dispatchUniqueID;
	}

	///バージョン2
	///collectorがdistributeし、お望みのバッファの型にして返す
	template<typename DescType>
	[[nodiscard]] std::pair<BufferUniqueID, typename DescTypeTraits<DescType>::Type*>
	CreateWithBuffer(const DescType& desc_, const std::string& name_)
	{
		using ActualBufferType = typename DescTypeTraits<DescType>::Type;

		//生成数 = IDとす
		BufferUniqueID dispatchUniqueID = Create(desc_, name_);
		collector->Distribute();

		ActualBufferType* buffer = dynamic_cast<ActualBufferType*>(dispatcher->Dispatch(dispatchUniqueID));
		ErrorMessageOutput::Assert::DetectError(buffer, "型変換できない", "BufferCreator.f");

		return std::make_pair(dispatchUniqueID, buffer);
	}


	//生成したバッファの管理はしません。あとは任せました状態
	template<typename DescType>
	[[nodiscard]] std::unique_ptr<typename DescTypeTraits<DescType>::Type> CreateBeyondMyJurisdiction(const DescType& desc_, const std::string& name_)
	{
		using ActualBufferType = typename DescTypeTraits<DescType>::Type;

		return assembler->Assemble<ActualBufferType>(desc_, name_);
	}


private:

	//バッファを生成した合計数。ユニークIDとして使用する
	uint32_t generateBufferSum{};
	std::unique_ptr<BufferContext::BufferAssembler> assembler;
	BufferCollector* collector;
	BufferDispatcher* dispatcher;

};

template<>
struct BufferContext::BufferCreator::DescTypeTraits<StaticStructuredBufferDescription>
{
	using Type = StaticStructuredBuffer;
};

template<>
struct BufferContext::BufferCreator::DescTypeTraits<UploadStructuredBufferDescription>
{
	using Type = UploadStructuredBuffer;
};

template<>
struct BufferContext::BufferCreator::DescTypeTraits<ColorBufferDescription>
{
	using Type = ColorBuffer;
};

template<>
struct BufferContext::BufferCreator::DescTypeTraits<DepthStencilBufferDescription>
{
	using Type = DepthStencilBuffer;
};

template<>
struct BufferContext::BufferCreator::DescTypeTraits<ConstantBufferDescription>
{
	using Type = ConstantBuffer;
};

template<>
struct BufferContext::BufferCreator::DescTypeTraits<ComputeBufferDescription>
{
	using Type = ComputeBuffer;
};
