#pragma once
#include "BufferRequiredInfo.h"
#include "../RenderPassComponent.h"

//jsonファイルに登録時のキー
struct PassRequiredInfo
{
private:

	struct DataKeyString
	{
		std::string const kColorFormatI =		"colorFormat";
		std::string const kClearColorV4 =		"clearColor";
		std::string const kColorWidthI =		"colorWidth";
		std::string const kColorHeightI =		"colorHeight";
		std::string const kNumBuffer_colorI =	"numBuffer_Color";

		std::string const kUseDepthStenciB =	"useDepthStencil";
		std::string const kDsvFormatI =			"dsvFormat";
		std::string const kSrvFormatI =			"srvFormat";
		std::string const kClearDepthF =		"clearDepth";
		std::string const kClearStencilF =		"clearStencil";
		std::string const kDepthWidthI =		"depthWidth";
		std::string const kDepthHeightI =		"depthHeight";
		std::string const kNumBuffer_depthI =   "numBuffer_Depth";

		std::string const kDepthTestI =			"depthTest";
		std::string const kDepthEnableB =		"depthEnable";

	};

public:

	static inline DataKeyString dataKeyString;

	RenderPassComponent::DepthTest depthTest;
	RenderPassComponent::DepthEnable depthEnable;
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo;
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;

};

