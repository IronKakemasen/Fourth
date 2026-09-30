#pragma once
#include "../../RenderContext.h"
#include "../RenderPassState.h"
#include "../../RenderStateComponent.h"

//外部
#include "../../../../../Assets/Shared/ConstantBuffers.h"

class ColorBuffer;
class DepthStencilBuffer;

struct RenderContext::RuntimePassInfo
{
	RuntimePassInfo
	(
		NexusFieldProof proof_,
		std::unique_ptr<PassDesc> desc_,
		std::vector<BufferUniqueID> const& refColorBuffersID_,
		std::vector<BufferUniqueID> const& refDepthStencilBuffersID_,
		UINT const refOffset_
	);

	struct ColorBuffer
	{
		std::vector<float> clearColor{};
		D3D12_VIEWPORT viewport;
		D3D12_RECT scissorRect;
		RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kDependsModel;
		BufferUniqueID bufferID{};
	};

	struct DepthStencilBuffer
	{
		float clearDepth{};
		D3D12_CLEAR_FLAGS doesClearStencil;
		int clearStencil{};
		BufferUniqueID bufferID;
	};

	auto const& WatchPass() const { return pass; }
	auto const& WatchColorBuffersInfo() const { return colorBuffersInfo; }
	auto const& WatchDepthStencilBufferInfo() const { return depthStencilBufferInfo; }
	auto const& WatchRootConstants() const { return rootConstants; }


	template<typename BufferType>
	std::vector<BufferUniqueID> const& WatchReferenceBufferIDs() const 
	{
		std::vector<BufferUniqueID> const& refIDContainer = refColorBuffersID;

		if constexpr (std::is_same_v<BufferType, DepthStencilBuffer>) return refDepthStencilBuffersID;

		return refIDContainer;
	}

private:

	//Descから情報をピックする
	RenderPassComponent::Pass pass;
	std::vector<ColorBuffer> colorBuffersInfo;
	std::optional<DepthStencilBuffer> depthStencilBufferInfo;
	
	//こいつらは別機関から情報を埋めてもらう
	//参照するカラーバッファのID群
	std::vector<BufferUniqueID> refColorBuffersID;
	//その深度ステンシルバッファバージョン
	std::vector<BufferUniqueID> refDepthStencilBuffersID;

	ConstantBuffers::PassBufferIndexRangeCPUGPU rootConstants;

	//PassDescからランタイムに必要な情報をピックする
	void PickUpRuntimeRequirementsFromDesc(PassDesc const& desc_);
	
	//その他、PassDesc以外の情報を入力
	void InputOtherParams
	(
		std::vector<BufferUniqueID> const& refColorBuffersID_,
		std::vector<BufferUniqueID> const& refDepthStencilBuffersID_,
		UINT const refOffset_
	);

	//シザー行列、ビューポート行列を組み立てる
	template<typename MarixType>
	MarixType AssembleMatrix(uint32_t width_, uint32_t height_);

};


template<>
D3D12_VIEWPORT RenderContext::RuntimePassInfo::AssembleMatrix(uint32_t width_, uint32_t height_);

template<>
D3D12_RECT RenderContext::RuntimePassInfo::AssembleMatrix(uint32_t width_, uint32_t height_);


