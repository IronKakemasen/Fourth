#pragma once
#include "../BufferInterface.h"

struct ColorBufferDescription;

//カラーバッファクラス
class ColorBuffer final : public GPUBufferBehavior,IRWBuffer,IColorBuffer, IRenderTargetBuffer
{
	enum Status
	{
		kRTV_SRV,
		kSRV_RTV
	};

public:

	ColorBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	//ダブルバッファのうち適切な方のバッファからCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperCPUHandle()const override;
	//適切な方のバッファからテクスチャのFormat出す。まあ今ケースの場合はFormatは共通なんだけども
	virtual DXGI_FORMAT OutProperRenderTargetFormat()const override;
	//適切な方のバッファからClearColor出す
	virtual std::array<float, 4> OutProperClearColor()const override;
	//自身のステートに応じて、それぞれのバッファのバリアを生成する
	virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
		CreateNextStepBarriers(ExtractMaterialKey key_)override;

	//役割を入れ替える
	virtual void Swap()override;

private:

	Status status = kRTV_SRV;

};



