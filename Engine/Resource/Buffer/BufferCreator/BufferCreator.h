#pragma once

#include "../BufferCollector/BufferCollector.h"
#include "../BufferAssembler/BufferAssembler.h"


class BufferContext::BufferCreator
{
public:
	BufferCreator
	(
		std::unique_ptr<BufferContext::BufferAssembler>&& assembler_, 
		std::unique_ptr<BufferContext::BufferCollector>&& collector_
	);

	~BufferCreator();

	//生成したバッファの管理を請け負います
	template<typename BufferType, typename DescType>
	void Create(const DescType& desc_, const std::string& name_)
	{
		std::unique_ptr<BufferType> buffer = assembler->Assemble<BufferType>(desc_, name_);
		collector->Register(std::move(buffer));
	}

	//生成したバッファの管理はしません
	template<typename BufferType, typename DescType>
	std::unique_ptr<BufferType> CreateBeyondMyJurisdiction(const DescType& desc_, const std::string& name_)
	{
		return assembler->Assemble<BufferType>(desc_, name_);
	}

private:
	std::unique_ptr<BufferContext::BufferAssembler> assembler;
	std::unique_ptr<BufferContext::BufferCollector> collector;
};

