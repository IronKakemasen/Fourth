#pragma once
#include "../BufferInterface.h"


//定数バッファクラス
class DepthStencilBuffer final : public GPUBufferBehavior, IRenderTargetBuffer,IShaderBuffer,IDepthBuffer
{
	friend class BufferContext::RenderTargetBufferInfoExtractor;

public:

	DepthStencilBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

private:

	//バリアを張る
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) override;
	//適切なCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperDSVHeapHandle()const override;
	//適切なsrvHeapインデックスを渡す
	virtual uint32_t OutProperSRVHeapIndex()const override;
	//DSVFormat出す
	virtual DXGI_FORMAT OutProperDSVFormat()const override;
	//ClearColor出す
	virtual std::array<float, 4> OutProperClearColor()const override;
	//横幅立幅
	virtual std::pair<uint32_t, uint32_t> OutWidthAndHeight()const override;


};

