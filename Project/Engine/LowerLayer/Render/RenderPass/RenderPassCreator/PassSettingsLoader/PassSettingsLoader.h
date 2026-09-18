#pragma once
#include "../RenderPassCreator.h"
#include "../../PassDesc/PassDesc.h"


class RenderContext::RenderPassCreator::PassSettingsLoader
{
	friend class RenderPassCreator;

	static [[nodiscard]] PassDesc Load(std::string const passName_);


	//以下ヘルパー
private:
	static std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> ParseColorBufferInfo(std::string const passName_);

	static std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> ParseDepthStencilBufferInfo(std::string const passName_);

	static RenderPassState ParseRenderPassState(std::string const passName_);

	static std::optional<std::pair<std::string, std::string >> ParseShaderFile(std::string const passName_);

	static std::vector<std::string> ParseReferenceBufferNames(std::string const passName_);

	struct DataKeyString
	{
		//パスの情報が詰まったjsonファイル名
		static inline std::string const kSrcJsonFileName		= "RenderPassSettings";

		//オフスクリーンの設定
		static inline std::string const kIsOffScreenB			= "isOffScreen";
		static inline std::string const kMS						= "ms";
		static inline std::string const kPS						= "ps";

		//カラーバッファの設定
		static inline std::string const kColorBufferName		= "colorBufferName";
		static inline std::string const kBlendMode				= "blendMode";
		static inline std::string const kColorFormatI	 		= "colorFormat";
		static inline std::string const kClearColorV4	 		= "clearColor";
		static inline std::string const kColorWidthI	 		= "colorWidth";
		static inline std::string const kColorHeightI	 		= "colorHeight";
		static inline std::string const kNumBuffer_colorI		= "numBuffer_Color";

		//深度バッファの設定
		static inline std::string const kDepthBufferName 		= "depthBufferName";
		static inline std::string const kUseDepthStenciB 		= "useDepthStencil";
		static inline std::string const kDsvFormatI		 		= "dsvFormat";
		static inline std::string const kSrvFormatI		 		= "srvFormat";
		static inline std::string const kClearDepthF	 		= "clearDepth";
		static inline std::string const kClearStencilI	 		= "clearStencil";
		static inline std::string const kDepthWidthI	 		= "depthWidth";
		static inline std::string const kDepthHeightI	 		= "depthHeight";
		static inline std::string const kNumBuffer_depthI		= "numBuffer_Depth";

		//深度・ステンシル設定
		static inline std::string const kDepthTestI		 		= "depthTest";
		static inline std::string const kDepthEnableB	 		= "depthEnable";
		static inline std::string const kDepthBiasI		 		= "depthBias";
		static inline std::string const kDepthBiasClampF 		= "depthBiasClamp";
		static inline std::string const kSlopeScaledDepthBiasF	= "slopeScaledDepthBias";

		//参照するテクスチャ名
		static inline std::string const kReferenceBufferNames	= "referenceBufferNames";


	};

};




