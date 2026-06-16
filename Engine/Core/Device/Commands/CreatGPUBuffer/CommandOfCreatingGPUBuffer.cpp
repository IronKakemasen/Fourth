#include "PreCompileHeader.h"
#include "CommandOfCreatingGPUBuffer.h"
 

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CommandCreateGPUResource::CreateResource
(
	ID3D12Device8* device_,
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValue_,
	D3D12_RESOURCE_STATES initialState_,
	const std::string& name_
)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> resource;

	//[ 生成 ]
	[[maybe_unused]] HRESULT hr = device_->CreateCommittedResource(
		&heapProperties_,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc_,
		initialState_,
		clearValue_,
		IID_PPV_ARGS(&resource));

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), name_ + ": リソース生成失敗", "CommandOfCreatingGPUBuffer.cpp");

	return resource;
}

//D3D12_RESOURCE_STATES CommandCreateGPUResource::ConfigureInitialResourceState(D3D12_HEAP_TYPE heapType_, D3D12_RESOURCE_FLAGS resourceFlag_)
//{
//	D3D12_RESOURCE_STATES initialState{};
//
//	//CPUの近くにおく。からアクセスできるけど遅し。GPUからは触れない
//	if (heapType_ == D3D12_HEAP_TYPE_UPLOAD)
//	{
//		//こうしなきゃいけない
//		initialState = D3D12_RESOURCE_STATE_GENERIC_READ;
//	}
//	//GPUの近くのメモリ、Vramにおく。速し。CPUからアクセスできなくなる
//	else if (heapType_ == D3D12_HEAP_TYPE_DEFAULT)
//	{
//		//UAV生成フラグがあるときは、GPUが書き込めるようにする
//		if (resourceFlag_ & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS)
//		{
//			initialState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
//		}
//		//読み込み専用のStructuredBufferなら、中継バッファからのデータ転送待ち状態にする
//		else
//		{
//			initialState = D3D12_RESOURCE_STATE_COPY_DEST;
//		}
//	}
//
//	return initialState;
//}


CommandCreateGPUResource::CommandCreateGPUResource(DeviceContext::CommandProvider::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateGPUResource::~CommandCreateGPUResource()
{

}