#pragma once
#include "../../RenderContext.h"
#include "../RenderPassState.h"
#include "../../RenderStateComponent.h"

//外部
#include "../../../../../Assets/Shared/ConstantBuffers.h"


struct RenderContext::RuntimePassInfo
{
	RuntimePassInfo(NexusFieldProof proof_,std::unique_ptr<PassDesc> desc_);

	struct ColorBuffer
	{
		std::vector<float> clearColor{};
		uint32_t width{};
		uint32_t height{};
		RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kDependsModel;
		BufferUniqueID bufferID;
	};

	struct DepthStencilBuffer
	{
		float clearDepth{};
		int clearStencil{};
		BufferUniqueID bufferID;
	};

	std::vector<ColorBuffer> const& WatchColorBuffersInfo() const { return colorBuffersInfo; }
	std::optional<DepthStencilBuffer> const& WatchDepthStencilBufferInfo() const { return depthStencilBufferInfo; }
	std::vector<BufferUniqueID> const& WatchReferenceBufferIDs() const { return referenceBufferIDs; }
	ConstantBuffers::PassBufferIndexRangeCPUGPU const& WatchRootConstants() const { return rootConstants; }

private:

	//Descから情報をピックする
	std::vector<ColorBuffer> colorBuffersInfo;
	std::optional<DepthStencilBuffer> depthStencilBufferInfo;
	
	//こいつらは別機関から情報を埋めてもらう
	std::vector<BufferUniqueID> referenceBufferIDs;
	ConstantBuffers::PassBufferIndexRangeCPUGPU rootConstants;

	//PassDescからランタイムに必要な情報をピックする
	void PickUpRuntimeRequirementsFromDesc(PassDesc const& desc_);
};

