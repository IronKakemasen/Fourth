#pragma once
#include "../../BufferContext.h"


class GPUBufferBehavior;

class BufferContext::BufferDispatcher
{

	//テーブル
	inline std::vector<std::unique_ptr<GPUBufferBehavior>>* ContainerTable(BufferContext::RegisterType type_)
	{
		static std::vector<std::unique_ptr<GPUBufferBehavior>>* table[(int)RegisterType::kCount]
		{
			renderTargetBufferPool,
			frameBufferpool,
			computeBufferPool
		};

		return table[(int)type_];
	}

public:

	BufferDispatcher
	(
		BufferContext::InstanceKey key_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* renderTargetBufferContainer_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* computeBufferContainer_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* frameBufferContainer_,
		std::unordered_map<BufferUniqueID, std::pair<RegisterType, uint32_t>>* bufferLocationMap_
	);

	///ユニークIDからバッファを渡します
	inline GPUBufferBehavior* Dispatch(BufferUniqueID bufferID_)
	{
		auto& tmp = (*bufferLocationMap)[bufferID_];

		BufferContext::RegisterType registerType = tmp.first;
		uint32_t dstIndex = tmp.second;

		return ContainerTable(registerType)->at(dstIndex).get();
	}

private:

	//検索先
	std::vector<std::unique_ptr<GPUBufferBehavior>>* renderTargetBufferPool;
	std::vector<std::unique_ptr<GPUBufferBehavior>>* frameBufferpool;
	std::vector<std::unique_ptr<GPUBufferBehavior>>* computeBufferPool;
	//ユニークIDがどこのバッファコンテナの何番目のバッファを指しているのか示すマップコンテナ
	std::unordered_map<BufferUniqueID, std::pair<RegisterType, uint32_t>>* bufferLocationMap;

};
