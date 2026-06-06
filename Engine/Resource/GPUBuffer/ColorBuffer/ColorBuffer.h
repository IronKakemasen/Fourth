#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"



//カラーバッファクラス
class ColorBuffer : public GPUBufferBehavior
{
public:

	ColorBuffer(const InstanceKey& instanceKey_, std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, ColorBufferDescription desc_);

private:

	D3D12_CPU_DESCRIPTOR_HANDLE handle;
	ColorBufferDescription desc;
	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	void SetMatrix();

};

