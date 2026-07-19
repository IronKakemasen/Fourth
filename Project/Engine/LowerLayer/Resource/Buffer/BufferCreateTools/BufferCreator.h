#pragma once
#include "../BufferContext.h"
#include "BufferCollector/BufferCollector.h"
#include "BufferAssembler/BufferAssembler.h"
#include "../BufferDefinition/AllBuffersInclude.h"

class BufferContext::BufferCreator
{
	template<typename DescType>
	struct DescTypeTraits;


public:

	BufferCreator
	(
		BufferContext::InstanceKey instancekey_,
		BufferContext::ResourceCreator* resourceCreator_,
		DescriptorHeapContext* descriptorHeapContext_,
		BufferPoolSet* bufferPoolSet_
	);

	~BufferCreator();

	//生成したバッファの管理を請け負います
	template<typename DescType>
	[[nodiscard]] BufferUniqueID Create(const DescType& desc_, const std::string& name_)
	{
		using ActualBufferType = typename DescTypeTraits<DescType>::Type;

		std::unique_ptr<ActualBufferType> buffer = assembler->Assemble<ActualBufferType>(desc_, name_);
		
		//生成数 = IDとす
		BufferUniqueID dispatchUniqueID = BufferUniqueID(generateBufferSum++);

		//コレクターに登録
		collector->Register<ActualBufferType>(std::move(buffer), dispatchUniqueID);

		//バッファユニークIDを返す
		return dispatchUniqueID;
	}

	//生成したバッファの管理はしません。あとは任せました状態
	template<typename DescType>
	[[nodiscard]] std::unique_ptr<DescTypeTraits<DescType>> CreateBeyondMyJurisdiction(const DescType& desc_, const std::string& name_)
	{
		using ActualBufferType = typename DescTypeTraits<DescType>::Type;

		return assembler->Assemble<ActualBufferType>(desc_, name_);
	}


private:

	//バッファを生成した合計数。ユニークIDとして使用する
	uint32_t generateBufferSum{};
	std::unique_ptr<BufferContext::BufferAssembler> assembler;
	std::unique_ptr<BufferContext::BufferCollector> collector;
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
