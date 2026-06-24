#pragma once
#include "../BufferInterface.h"

struct ColorBufferDescription;

//カラーバッファクラス
class ColorBuffer final : public GPUBufferBehavior,IRWBuffer,IColorBuffer
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


	//テンプレ化予定
	///+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/++/+
	///+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/++/+
	//リソースのディスクリプションを見る
	//const ColorBufferDescription& WatchDescription();
	///+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/++/+
	///+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/++/+

	virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
		CreateNextStepBarriers(ExtractMaterialKey key_)override;

	virtual void Swap()override;

private:

	Status status = kRTV_SRV;

};



