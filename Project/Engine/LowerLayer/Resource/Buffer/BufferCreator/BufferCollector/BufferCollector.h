#pragma once
#include "../../BufferContext.h"

class GPUBufferBehavior;
class ColorBuffer;
class ConstantBuffer;
class DepthStencilBuffer;
class ComputeBuffer;
class UploadStructuredBuffer;
class StaticStructuredBuffer;

class BufferContext::BufferCollector
{
public:

	BufferCollector
	(
		BufferContext::InstanceKey key_,
		BufferContext::BufferPoolSet* bufferPoolSet_
	);

	~BufferCollector();
	
	///作成されたバッファを一時保管場所へ移動
	template<typename BufferType>
	void Register(std::unique_ptr<BufferType> buffer_,BufferUniqueID id_)
	{
		auto registerType = Identify<BufferType>();

		TempSaveFormat tmpSaveFormat;
		tmpSaveFormat.type = registerType;
		tmpSaveFormat.buffer = std::move(buffer_);
		tmpSaveFormat.id = id_;

		tmp_bufferContainer.emplace_back(std::move(tmpSaveFormat));
	}

	//実体を目的のコンテナに分配する
	void Distribute();

private:

	struct TempSaveFormat
	{
		RegisterType type;
		std::unique_ptr<GPUBufferBehavior> buffer;
		BufferUniqueID id;
	};


	//一時保管用
	std::vector<TempSaveFormat> tmp_bufferContainer;

	///分別先
	BufferContext::BufferPoolSet* bufferPoolSet;

	//バッファのデータ型に応じて登録先識別用のタイプを返す
	template<typename BufferType>
	RegisterType Identify()
	{
		RegisterType type = RegisterType::kComputeBuffer;

		if constexpr 
		(
			std::is_same_v<BufferType, UploadStructuredBuffer>  ||
			std::is_same_v<BufferType, ConstantBuffer>
		)
		{
			type = RegisterType::kFrameBuffer;
		}
		else if constexpr
		(
			std::is_same_v<BufferType, ColorBuffer>				||
			std::is_same_v<BufferType, DepthStencilBuffer>		
		)
		{
			type = RegisterType::kRenderTarget;
		}
		else if constexpr
		(
			std::is_same_v<BufferType, StaticStructuredBuffer> 
		)
		{
			type = RegisterType::kReadOnlyBuffer;
		}

		return type;
	}


	//目的のコンテナのイテレーターを返す
	std::vector<std::unique_ptr<GPUBufferBehavior>>::iterator FindFreeSlot(std::vector<std::unique_ptr<GPUBufferBehavior>>* container_);
};

