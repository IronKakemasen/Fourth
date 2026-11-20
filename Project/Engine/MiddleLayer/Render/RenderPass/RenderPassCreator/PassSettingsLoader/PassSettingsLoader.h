#pragma once
#include "../RenderPassCreator.h"


class RenderContext::RenderPassCreator::PassSettingsLoader
{
	friend class RenderPassCreator;

	static [[nodiscard]] std::unique_ptr<PassDesc> Load(std::string const& passName_);


	//以下ヘルパー
private:
	//自前のカラーバッファの情報
	static std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> ParseColorBufferInfo(std::string const& passName_);

	//自前の深度バッファの情報
	static std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> ParseDepthStencilBufferInfo(std::string const& passName_);

	//パスの情報
	static RenderPassState ParseRenderPassState(std::string const& passName_);

	//オフスクリーンは自前のシェーダーファイルがあるのでそれを読み込む
	static std::optional<std::pair<std::string, std::string >> ParseShaderFile(std::string const& passName_);

	//参照するバッファの名前
	static std::vector<std::string> ParseReferenceBufferNames(std::string const& passName_);

	//バッファ書き込みをシェアする他パスのバッファの名前
	static std::vector<std::string> ParseWriteSharingColorBufferNames(std::string const& passName_);
	static std::string ParseWriteSharingDepthBufferName(std::string const& passName_);

	struct DataKeyString
	{
		//パスの情報が詰まったjsonファイル名
		static inline std::string const kSrcJsonFileName		= "RenderPassSettings";

		//オフスクリーンの設定
		static inline std::string const kIsOffScreenB			= "isOffScreen";
		static inline std::string const kMS						= "ms";
		static inline std::string const kPS						= "ps";

		//カラーバッファの設定
		static inline std::string const kDoesOwnColorBuffersB	 = "doesOwnColorBuffers";
		static inline std::string const kColorBufferName		 = "ownedColorBufferNames";
		static inline std::string const kBlendMode				 = "blendModes";
		static inline std::string const kColorFormatI	 		 = "colorFormats";
		static inline std::string const kClearColorV4	 		 = "clearColors";
		static inline std::string const kColorWidthI	 		 = "colorWidths";
		static inline std::string const kColorHeightI	 		 = "colorHeights";
		static inline std::string const kNumBuffer_colorI		 = "numBuffer_Colors";
																 
		//深度バッファの設定										   
		static inline std::string const kDoesOwnDepthStencilB	 = "doesOwnDepthStencil";
		static inline std::string const kDepthBufferName 		 = "ownedDepthBufferName";
		static inline std::string const kDsvFormatI		 		 = "dsvFormat";
		static inline std::string const kSrvFormatI		 		 = "srvFormat";
		static inline std::string const kClearDepthF	 		 = "clearDepth";
		static inline std::string const kClearStencilFlagB		 = "clearStencilFlag";
		static inline std::string const kClearStencilI	 		 = "clearStencil";
		static inline std::string const kDepthWidthI	 		 = "depthWidth";
		static inline std::string const kDepthHeightI	 		 = "depthHeight";
		static inline std::string const kNumBuffer_depthI		 = "numBuffer_Depth";
																 
		//深度・ステンシル設定									  
		static inline std::string const kDepthTestI		 		 = "depthTest";
		static inline std::string const kDepthEnableB	 		 = "depthEnable";
		static inline std::string const kDepthBiasI		 		 = "depthBias";
		static inline std::string const kDepthBiasClampF 		 = "depthBiasClamp";
		static inline std::string const kSlopeScaledDepthBiasF	 = "slopeScaledDepthBias";

		//参照するバッファ名
		static inline std::string const kReferenceBufferNames	 = "referenceBufferNames";

		//書き込みシェアするバッファ名
		static inline std::string const kWriteSharingColorBufferNames = "writeSharingColorBufferNames";
		static inline std::string const kWriteSharingDepthBufferName  = "writeSharingDepthBufferName";


	};

};




