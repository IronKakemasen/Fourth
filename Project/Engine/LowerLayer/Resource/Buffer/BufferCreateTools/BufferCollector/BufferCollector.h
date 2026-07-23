#pragma once
#include "../../BufferContext.h"
#include "../../BufferDefinition/AllBuffersFwd.h"


class BufferContext::BufferCollector
{
public:

	BufferCollector
	(
		BufferContext::NexusFieldProof proof_,
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
		tmpSaveFormat.buffer = CastBuffer(std::move(buffer_));
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

	//GPUBufferBehaviorにキャストしてユニークを返す
	template<typename BufferType>
	std::unique_ptr<GPUBufferBehavior> CastBuffer(std::unique_ptr<BufferType> buffer_);

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

};

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<ColorBuffer> buffer_);

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<ConstantBuffer> buffer_);

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<ComputeBuffer> buffer_);

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<DepthStencilBuffer> buffer_);

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<UploadStructuredBuffer> buffer_);

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<StaticStructuredBuffer> buffer_);
