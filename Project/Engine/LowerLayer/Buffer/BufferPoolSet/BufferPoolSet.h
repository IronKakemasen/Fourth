#pragma once
#include "../BufferContext.h"
#include "../BufferDefinition/BufferTraits.h"

class GPUBufferBehavior;
template<typename ValueType> class ClosedHashMap;

struct BufferContext::BufferPoolSet
{
	BufferPoolSet();

	//ColorBufferやDepthStencilBufferなどレンダーターゲットなバッファプール
	std::vector<std::unique_ptr<GPUBufferBehavior>> renderTargetBufferPool;
	//computeBufferのような、コンピュートシェーダをかませるバッファのプール
	std::vector<std::unique_ptr<GPUBufferBehavior>> computeBufferPool;
	//ConstantBufferやUploadStructuredBufferのようなフレームバッファのプール
	std::vector<std::unique_ptr<GPUBufferBehavior>> frameBufferPool;
	//staticStructuredBufferやtextureBufferのような、読みしかしない確定のシングルバッファのプール
	std::vector<std::unique_ptr<GPUBufferBehavior>> readOnlyBufferPool;

	//ユニークIDがどこのバッファコンテナの何番目のバッファを指しているのか示すマップコンテナ
	//std::unordered_map<BufferUniqueID, std::pair<RegisterType, uint32_t>> bufferLocationMap;
	std::unique_ptr<ClosedHashMap<std::pair<BufferTraits::RegisterType, uint32_t>>> bufferLocationClosedHashedMap;
	//RegisterTypeがキーのテーブル
	std::vector<std::unique_ptr<GPUBufferBehavior>>* ContainerTable(BufferTraits::RegisterType type_);

private:
	//bufferLocationClosedHashedMapのサイズ
	static constexpr int kHashedMapSize = 16384;

};

