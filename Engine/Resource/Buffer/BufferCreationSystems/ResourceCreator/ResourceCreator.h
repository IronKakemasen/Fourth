#pragma once
#include "../../BufferContext.h"

class BufferContext::ResourceCreator
{

public:

	ResourceCreator(BufferContext::InstanceKey instanceKey_, BufferContext::CreateResourceCommand createResourceCommand_);
	~ResourceCreator();

	[[nodiscard]] std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>> Create
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValuePtr_, 
		std::array<D3D12_RESOURCE_STATES, ProjectConfig::Render::kRequiredGPUBufferSum> initialStates_,
		const std::string& name_
	);

private:

	//リソース生成コマンド
	BufferContext::CreateResourceCommand createResourceCommand;


};