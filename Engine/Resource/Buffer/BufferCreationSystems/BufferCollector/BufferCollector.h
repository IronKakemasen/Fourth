#pragma once
#include "../../BufferContext.h"

class GPUBufferBehavior;
class ColorBuffer;
class ConstantBuffer;
class DepthStencilBuffer;
class ComputeBuffer;
class UploadStructuredBuffer;

class BufferContext::BufferCollector
{
public:

	BufferCollector
	(
		BufferContext::InstanceKey key_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* renderTargetBufferContainer_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* computeBufferContainer_,
		std::vector<std::unique_ptr<GPUBufferBehavior>>* frameBufferContainer_,
		std::unordered_map<BufferUniqueID, std::pair<BufferContext::RegisterType, uint32_t>>* bufferLocationMap_
	);

	~BufferCollector();
	
	//作成されたバッファを一時保管場所へ移動
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

	//分別先
	std::vector<std::unique_ptr<GPUBufferBehavior>>* renderTargetBufferContainer;
	std::vector<std::unique_ptr<GPUBufferBehavior>>* computeBufferContainer;
	std::vector<std::unique_ptr<GPUBufferBehavior>>* frameBufferContainer;

	//ユニークIDがどこのバッファコンテナの何番目のバッファを指しているのか示すマップコンテナ
	std::unordered_map<BufferUniqueID, std::pair<RegisterType, uint32_t>>* bufferLocationMap;

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

		return type;
	}

	//目的のコンテナのイテレーターを返す
	std::vector<std::unique_ptr<GPUBufferBehavior>>::iterator FindFreeSlot(std::vector<std::unique_ptr<GPUBufferBehavior>>* container_);
	//コンテナテーブル
	std::vector<std::unique_ptr<GPUBufferBehavior>>* ContainerTable(BufferContext::RegisterType type_);

};

