#pragma once
#include "../BufferInterface.h"

struct ColorBufferDescription;

//カラーバッファクラス
class ColorBuffer final : public GPUBufferBehavior,IColorBuffer,IRenderTargetBuffer,IShaderBuffer
{
public:

	ColorBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	//バリア生成
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) override;
	//適切なRTVヒープインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperRTVHeapHandle()const override;
	//適切なSRVヒープインデックスを出す
	virtual uint32_t OutProperSRVHeapIndex()const override;
	//横幅立幅
	virtual std::pair<uint32_t, uint32_t> OutWidthAndHeight()const override;
	//RTVFormat出す
	virtual DXGI_FORMAT OutProperRTVFormat()const override;
	//ClearColor出す
	virtual std::array<float, 4> OutProperClearColor()const override;
};



