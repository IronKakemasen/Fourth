#pragma once
#include "../BufferContext.h"

class ResourceCreator
{

public:

	ResourceCreator(BufferContext::InstanceKey instanceKey_, BufferContext::CreateResourceCommand createResourceCommand_)
		: createResourceCommand(createResourceCommand_) {}

	~ResourceCreator() = default;

	[[nodiscard]] std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>> CreateResource
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValuePtr_, 
		const std::string& name_
	);

private:

	//リソース生成コマンド
	BufferContext::CreateResourceCommand createResourceCommand;


};