#pragma once
#include "BufferRequiredInfo.h"
#include "RenderPassState.h"

struct RenderContext::PassDesc
{
private:

	struct DataKeyString
	{
		std::string const kIsOffScreenB				= "isOffScreen";
		std::string const kMS						= "ms";
		std::string const kPS						= "ps";

		std::string const kColorBufferName			= "colorBufferName";
		std::string const kBlendMode				= "blendMode";
		std::string const kColorFormatI				= "colorFormat";
		std::string const kClearColorV4				= "clearColor";
		std::string const kColorWidthI				= "colorWidth";
		std::string const kColorHeightI				= "colorHeight";
		std::string const kNumBuffer_colorI			= "numBuffer_Color";

		std::string const kDepthBufferName			= "depthBufferName";
		std::string const kUseDepthStenciB			= "useDepthStencil";
		std::string const kDsvFormatI				= "dsvFormat";
		std::string const kSrvFormatI				= "srvFormat";
		std::string const kClearDepthF				= "clearDepth";
		std::string const kClearStencilI			= "clearStencil";
		std::string const kDepthWidthI				= "depthWidth";
		std::string const kDepthHeightI				= "depthHeight";
		std::string const kNumBuffer_depthI			= "numBuffer_Depth";

		std::string const kDepthTestI				= "depthTest";
		std::string const kDepthEnableB				= "depthEnable";
		std::string const kDepthBiasI				= "depthBias";
		std::string const kDepthBiasClampF			= "depthBiasClamp";
		std::string const kSlopeScaledDepthBiasF	= "slopeScaledDepthBias";

	};

public:

	static inline DataKeyString dataKeyString;

	PassDesc
	(
		std::string name_,
		std::optional<std::pair<std::string, std::string >> ms_psFileName_,
		RenderPassState renderPassState_,
		std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo_,
		std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo_
	);

	
	RenderPassState const& WatchRenderPassState()const;
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> const& WatchColorBuffersInfo()const;
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> const& WatchDepthStencilBufferInfo()const;
	std::optional<std::pair<std::string, std::string >> const& WatchMs_PsFileName()const;

	void SetColorBufferUniqueID(BufferUniqueID id_, size_t index_);
	void SetDepthStencilBufferUniqueID(BufferUniqueID id_);

	void DebugLog()const;
	std::string const WatchName()const;
private:

	//オフスクリーンパスの場合、シェーダーファイルは1つに限定される
	std::optional<std::pair<std::string, std::string >> ms_psFileName;

	//renderPassComponentの塊
	RenderPassState renderPassState;

	//必要なバッファの情報
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo;
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;

	//デバッグ用
	std::string passName;

};

