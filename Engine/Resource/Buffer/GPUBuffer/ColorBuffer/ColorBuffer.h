#pragma once
#include "../GPUBufferBehavior.h"

struct ColorBufferDescription;

//カラーバッファクラス
class ColorBuffer final : public GPUBufferBehavior
{
public:

	ColorBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	//リソースのディスクリプションを見る
	const ColorBufferDescription& WatchDescription();

	virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
		CreateNextStepBarriers(ExtractMaterialKey key_)override;

private:

	//行列
	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

	//viewportとscissorRectをセット
	void AssembleMatrix();
};



