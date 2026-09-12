#pragma once
#include "../../BufferUploader.h"


class BufferContext::BufferUploader::IntermediateResourceCreator
{
	friend class BufferContext::BufferUploader;

	//生成数。命名に使うだけ
	static inline int createNum{};

	static [[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateInterMediateResource
	(
		BufferContext::ResourceCreator* resourceCreator_,
		UINT resourceSize_
	);

	static D3D12_RESOURCE_DESC CreateIntermedeiteResourceDesc(UINT resourceSize_);
	static D3D12_HEAP_PROPERTIES CreateIntermedeiteHeapProp();

};

