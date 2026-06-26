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
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	//ダブルバッファのうち適切な方のバッファからCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperCPUHandle()const override;
	//適切な方のバッファからテクスチャのFormat出す。まあ今ケースの場合はFormatは共通なんだけども
	virtual DXGI_FORMAT OutProperRenderTargetFormat()const override;
	//ClearColor出す
	virtual std::array<float, 4> OutProperClearColor()const override;
	//自身のステートに応じて、それぞれのバッファのバリアを生成する
	//virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
	//	CreateNextStepBarriers(ExtractMaterialKey key_)override;
	//立幅横幅を出力
	virtual std::pair<uint32_t, uint32_t> OutWidthAndHeight()const override;

	//役割を入れ替える
	virtual void Swap()override;

private:

	Status status = kRTV_SRV;

};



