#pragma once
#include "../../BufferContext.h"

class BufferContext::ResourceCreator
{
	using ResourceContainer = std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>;
public:

	ResourceCreator(BufferContext::InstanceKey instanceKey_, BufferContext::CreateResourceCommand createResourceCommand_);
	~ResourceCreator();

	[[nodiscard]] ResourceContainer Create
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValuePtr_, 
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_,
		int numResource_
	);

private:

	//リソース生成コマンド
	BufferContext::CreateResourceCommand createResourceCommand;


};