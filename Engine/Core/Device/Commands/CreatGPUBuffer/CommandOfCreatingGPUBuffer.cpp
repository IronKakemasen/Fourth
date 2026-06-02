#include "PreCompileHedder.h"
#include "CommandOfCreatingGPUBuffer.h"

#include "../../../../Resource/BufferDescriptions/TypeA/BufferDescriptionTypeA.h"
#include "../../../../Resource/BufferDescriptions/TypeB/BufferDescriptionTypeB.h"

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CommandOfCreatingGPUBuffer::CreateResourceTypeA(ID3D12Device8* device_, const BufferDescriptionTypeA& typeA_Desc_)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> ret_resource;
	
	//頂点リソースのヒープ設定
	//upLoadHEapを使う
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	//頂点リソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	//バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_UNKNOWN;

	//リソースのサイズ。
	resourceDesc.Width = typeA_Desc_.sizeInByte;
	//バッファの場合はこれらを1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	//決まり2
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//実際に頂点リソースを作る
	[[maybe_unused]] HRESULT hr = device_->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&ret_resource));
	assert(SUCCEEDED(hr));

	return ret_resource;

}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateResourceTypeB(ID3D12Device8* device_,
	const BufferDescriptionTypeB& typeB_Desc_)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> ret_resource;



	return ret_resource;
}
