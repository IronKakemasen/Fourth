#pragma once
#include "../BufferContext.h"
#include "BufferCollector/BufferCollector.h"
#include "BufferAssembler/BufferAssembler.h"


class BufferContext::BufferCreator
{

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
	template<typename BufferType, typename DescType>
	[[nodiscard]] BufferUniqueID Create(const DescType& desc_, const std::string& name_)
	{
		std::unique_ptr<BufferType> buffer = assembler->Assemble<BufferType>(desc_, name_);

		collector->Register(std::move(buffer));

		//バッファユニークIDを返す
		return BufferUniqueID(generateBufferSum++);
	}

	//生成したバッファの管理はしません。あとは任せました状態
	template<typename BufferType, typename DescType>
	[[nodiscard]] std::unique_ptr<BufferType> CreateBeyondMyJurisdiction(const DescType& desc_, const std::string& name_)
	{
		return assembler->Assemble<BufferType>(desc_, name_);
	}


private:

	//バッファを生成した合計数。ユニークIDとして使用する
	uint32_t generateBufferSum{};
	std::unique_ptr<BufferContext::BufferAssembler> assembler;
	std::unique_ptr<BufferContext::BufferCollector> collector;
};

