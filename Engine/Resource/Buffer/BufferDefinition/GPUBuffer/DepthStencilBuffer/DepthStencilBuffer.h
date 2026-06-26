#pragma once
#include "../BufferInterface.h"


//定数バッファクラス
class DepthStencilBuffer final : public GPUBufferBehavior, IRWBuffer, IRenderTargetBuffer
{
	enum Status
	{
		kDSV_SRV,
		kSRV_DSV
	};

public:

	DepthStencilBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	////自身の状態をもとに貼るべきバリアを生成する
	//virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
	//	CreateNextStepBarriers(ExtractMaterialKey key_)override;
	//役割をスワップする
	virtual void Swap()override;
	//ダブルバッファのうち適切な方のバッファからCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperCPUHandle()const override;
	//DSVFormat出す
	virtual DXGI_FORMAT OutProperRenderTargetFormat()const override;
	//ClearColor出す
	virtual std::array<float, 4> OutProperClearColor()const override;


private:
	Status status = kDSV_SRV;
};

