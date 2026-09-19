#pragma once
#include "../../RenderContext.h"
#include "../RenderPassState.h"
#include "../../RenderStateComponent.h"

//外部
#include "../../../../../Assets/Shared/ConstantBuffers.h"


struct RenderContext::RuntimePassInfo
{
	RuntimePassInfo
	(
		NexusFieldProof proof_,
		std::unique_ptr<PassDesc> desc_,
		std::unordered_map<std::string, BufferUniqueID> const& idMap_,
		UINT const refOffset_
	);

	struct ColorBuffer
	{
		std::vector<float> clearColor{};
		uint32_t width{};
		uint32_t height{};
		RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kDependsModel;
		BufferUniqueID bufferID{};
	};

	struct DepthStencilBuffer
	{
		float clearDepth{};
		int clearStencil{};
		BufferUniqueID bufferID;
	};

	auto const& WatchColorBuffersInfo() const { return colorBuffersInfo; }
	auto const& WatchDepthStencilBufferInfo() const { return depthStencilBufferInfo; }
	auto const& WatchReferenceBufferIDs() const { return referenceBufferIDMap; }
	auto const& WatchRootConstants() const { return rootConstants; }

private:

	//Descから情報をピックする
	std::vector<ColorBuffer> colorBuffersInfo;
	std::optional<DepthStencilBuffer> depthStencilBufferInfo;
	
	//こいつらは別機関から情報を埋めてもらう
	std::unordered_map<std::string, BufferUniqueID> referenceBufferIDMap;
	ConstantBuffers::PassBufferIndexRangeCPUGPU rootConstants;

	//PassDescからランタイムに必要な情報をピックする
	void PickUpRuntimeRequirementsFromDesc(PassDesc const& desc_);
	//その他、PassDesc以外の情報を入力
	void InputOtherParams
	(
		std::unordered_map<std::string, BufferUniqueID> const& idMap_,
		UINT const refOffset_
	);
};

