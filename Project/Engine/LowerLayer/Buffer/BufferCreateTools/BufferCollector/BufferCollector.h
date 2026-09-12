#pragma once
#include "../../BufferContext.h"
#include "../../BufferDefinition/AllBuffersFwd.h"


class BufferContext::BufferCollector
{
	template<typename BufferType>
	struct BufferTypeTraits;

public:

	struct RegisterLicence;

	BufferCollector
	(
		BufferContext::NexusFieldProof proof_,
		BufferContext::BufferPoolSet* bufferPoolSet_
	);

	~BufferCollector();
	
	///作成されたバッファを一時保管場所へ移動
	template<typename BufferType>
	void Register(RegisterLicence licence_, std::unique_ptr<BufferType> buffer_,BufferUniqueID id_)
	{
		auto registerType = BufferTypeTraits<BufferType>::type;

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

};


struct BufferContext::BufferCollector::RegisterLicence
{
private:

	friend class BufferContext::BufferCreator;
	explicit RegisterLicence() = default;
};

template<>
struct BufferContext::BufferCollector::BufferTypeTraits<UploadStructuredBuffer>
{
	constexpr static RegisterType type = RegisterType::kFrameBuffer;
};

template<>
struct BufferContext::BufferCollector::BufferTypeTraits<ConstantBuffer>
{
	constexpr static RegisterType type = RegisterType::kFrameBuffer;
};

template<>
struct BufferContext::BufferCollector::BufferTypeTraits<ColorBuffer>
{
	constexpr static RegisterType type = RegisterType::kRenderTarget;
};

template<>
struct BufferContext::BufferCollector::BufferTypeTraits<DepthStencilBuffer>
{
	constexpr static RegisterType type = RegisterType::kRenderTarget;
};

template<>
struct BufferContext::BufferCollector::BufferTypeTraits<StaticStructuredBuffer>
{
	constexpr static RegisterType type = RegisterType::kReadOnlyBuffer;
};

template<>
struct BufferContext::BufferCollector::BufferTypeTraits<Texture2DBuffer>
{
	constexpr static RegisterType type = RegisterType::kReadOnlyBuffer;
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

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<Texture2DBuffer> buffer_);
