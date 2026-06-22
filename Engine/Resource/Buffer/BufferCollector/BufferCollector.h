#pragma once
#include "../BufferContext.h"


class GPUBufferBehavior;

class ColorBuffer;
class ConstantBuffer;
class DepthStencilBuffer;
class ComputeBuffer;
class UploadStructuredBuffer;

class BufferContext::BufferCollector
{
	//登録先識別用
	enum class RegisterType
	{
		kPingPong,
		kFrameBuffer,
	};

public:

	BufferCollector
	(
		BufferContext::InstanceKey key_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* bufferContainer_,
		std::vector<GPUBufferBehavior*>* pingPongBufferPtrContainer_,
		std::vector<GPUBufferBehavior*>* frameBufferPtrContainer_
	);

	~BufferCollector();
	
	//作成されたバッファを一時保管場所へ移動
	template<typename BufferType>
	void Register(std::unique_ptr<BufferType> buffer_)
	{
		auto registerType = Identify<BufferType>();
		tmp_bufferContainer.emplace_back(registerType, std::move(buffer_));
	}

	//分別先へ分配する
	void Distribute();

private:

	//一時保管用
	std::vector<std::pair<RegisterType,std::unique_ptr<GPUBufferBehavior>>> tmp_bufferContainer;

	//分別先
	std::vector<std::unique_ptr<GPUBufferBehavior>>* bufferContainer;
	std::vector<GPUBufferBehavior*>* pingPongBufferPtrContainer;
	std::vector<GPUBufferBehavior*>* frameBufferPtrContainer;

	//バッファのデータ型に応じて登録先識別用のタイプを返す
	template<typename BufferType>
	RegisterType Identify()
	{
		RegisterType type = RegisterType::kPingPong;

		if constexpr (std::is_same_v<BufferType, UploadStructuredBuffer>)
		{
			type = RegisterType::kFrameBuffer;
		}
		else if constexpr (std::is_same_v<BufferType, ConstantBuffer>)
		{
			type = RegisterType::kFrameBuffer;
		}
	
		return type;
	}
};

