#include "PreCompileHedder.h"
#include "CommandOfCreatingGPUBuffer.h"
#include "../../DeviceContextCommandGenerator/DeviceContextCommandGenerator.h"
#include "../../../../Resource/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"
#include "../../../../Resource/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
 

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CommandCreateGPUBuffer::CreateConstantBuffer
	( ID3D12Device8* device_ , const ConstantBufferDescription& desc_)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> ret_resource;
	//リソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	//リソースのヒープ設定
	D3D12_HEAP_PROPERTIES heapProperties{};

	//バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//リソースのサイズ。
	resourceDesc.Width = (desc_.sizeInByte + 255) & ~255;
	//DimensionがBufferの場合はこれらを1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	//行優先レイアウト
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//CPUから書き込みもできるが遅い
	heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;


	//[ 生成 ]
	[[maybe_unused]] HRESULT hr = device_->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc, 
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&ret_resource));
	
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "定数バッファの生成に失敗", "CommandOfCreatingGPUBuffer.cpp");

	return ret_resource;

}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CommandCreateGPUBuffer::CreateColorBuffer
	( ID3D12Device8* device_ , const ColorBufferDescription& desc_)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> ret_resource;
	D3D12_RESOURCE_DESC resourceDesc{};

	//幅
	resourceDesc.Width = UINT(desc_.width);
	//高さ
	resourceDesc.Height = UINT(desc_.height);
	//mipmapの数
	resourceDesc.MipLevels = 1;
	//奥行orTextureの配列数
	resourceDesc.DepthOrArraySize = 1;
	//Textureのformat
	resourceDesc.Format = desc_.format;
	//サンプリングカウント。１固定
	resourceDesc.SampleDesc.Count = 1;
	//テクスチャの次元数。2
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = desc_.flag;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	//[ 利用するHeapの設定 ]
	D3D12_HEAP_PROPERTIES heapProperties{};
	//vramの奥
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	// Clear 値を正しく渡す（CreateRenderTargetView と同じフォーマット）
	D3D12_CLEAR_VALUE clearValue{};
	clearValue.Format = desc_.format;
	for (int i = 0;i < 4;++i)clearValue.Color[i] = desc_.clearColor[i];

	// [ 生成 ]
	[[maybe_unused]]HRESULT hr = device_->CreateCommittedResource(
		&heapProperties,									//Heapの設定
		D3D12_HEAP_FLAG_NONE,								//Heapの特殊な設定、特になし
		&resourceDesc,										//Resourceの設定
		desc_.initialState,									//初期ステート
		&clearValue,										//Clear最適値。使わないのでnullptr
		IID_PPV_ARGS(ret_resource.GetAddressOf()));			//作成するresourceへのポインタのポインタ

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "ColorBufferの生成に失敗", "CommandOfCreatingGPUBuffer.cpp");


	return ret_resource;
}


CommandCreateGPUBuffer::CommandCreateGPUBuffer(DeviceContext::CommandGenerator::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateGPUBuffer::~CommandCreateGPUBuffer()
{

}