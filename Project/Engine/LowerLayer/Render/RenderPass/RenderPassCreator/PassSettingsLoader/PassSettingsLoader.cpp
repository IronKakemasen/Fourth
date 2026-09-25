#include "PreCompileHeader.h"
#include "PassSettingsLoader.h"
#include "../../PassDesc/PassDesc.h"

using namespace ProjectConfig::Window;
using namespace ProjectConfig::Render;
using namespace RenderPassComponent;

namespace
{
	auto const fileName = "PassSettingsLoader.cpp";
}


[[nodiscard]] std::unique_ptr<RenderContext::PassDesc> RenderContext::RenderPassCreator::PassSettingsLoader::Load(std::string const passName_)
{
	return std::make_unique<PassDesc>
	(
		passName_,
		ParseShaderFile(passName_),
		ParseRenderPassState(passName_),
		ParseColorBufferInfo(passName_),
		ParseDepthStencilBufferInfo(passName_),
		ParseReferenceBufferNames(passName_)
	);
}

std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> RenderContext::RenderPassCreator::PassSettingsLoader::ParseColorBufferInfo
(
	std::string const passName_
)
{
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBufferInfo;

	auto* miyajison = Miyajison::Get();

	//カラーバッファのフォーマット。以降、こいつの数といくつかのパラメーターは同期している前提で進める
	auto const colorBufferFormats = 
		miyajison->LoadData<std::vector<int>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kColorFormatI });
	//カラーバッファの数
	auto const numColorBuffers = colorBufferFormats.size();

	//カラーバッファのクリアカラー
	auto const clearColors = 
		miyajison->LoadData<std::vector<std::vector<float>>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kClearColorV4 });

	//カラーバッファの縦横
	auto const widthContainer = 
		miyajison->LoadData<std::vector<int>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kColorWidthI });
	auto const heightContainer =
		miyajison->LoadData<std::vector<int>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kColorHeightI });

	//シングルかダブルか
	auto const numBufferContainer =
		miyajison->LoadData<std::vector<int>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kNumBuffer_colorI });

	//バッファの名前
	auto const bufferNames = 
		miyajison->LoadData<std::vector<std::string>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kColorBufferName });

	//ブレンドモード
	auto const blendModesString =
		miyajison->LoadData<std::vector<std::string>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kBlendMode});
	//名前からenumへ変換
	std::vector<RenderStateComponent::BlendMode> blendModes;
	for (auto const& string : blendModesString)
	{
		blendModes.emplace_back(RenderStateComponent::BlendModeToEnum(string));
	}


	//サイズの比が一致してるかチェック
	ErrorMessageOutput::Assert::DetectError
	(
		numColorBuffers == clearColors.size()		 &&
		numColorBuffers == widthContainer.size()	 &&
		numColorBuffers == numBufferContainer.size() &&
		numColorBuffers == heightContainer.size()	 &&
		numColorBuffers == bufferNames.size()		 &&
		numColorBuffers == blendModes.size(), 
		"カラーバッファの設定が間違っている",
		fileName
	);
	

	colorBufferInfo.resize(numColorBuffers);
	for (auto i = 0;i < numColorBuffers;++i)
	{
		colorBufferInfo[i].bufferName = bufferNames[i];
		colorBufferInfo[i].blendMode = blendModes[i];
		colorBufferInfo[i].format = DXGI_FORMAT(colorBufferFormats[i]);
		colorBufferInfo[i].clearColor = clearColors[i];
		colorBufferInfo[i].width = widthContainer[i] == -1 ? kWidth : widthContainer[i];
		colorBufferInfo[i].height = heightContainer[i] == -1 ? kHeight : heightContainer[i];
		colorBufferInfo[i].numBuffer = NumBuffer(numBufferContainer[i]);
	}

	return colorBufferInfo;
}


std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> RenderContext::RenderPassCreator::PassSettingsLoader::ParseDepthStencilBufferInfo
(
	std::string const passName_
)
{

	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;

	auto* miyajison = Miyajison::Get();

	//深度バッファ使わんならしらん
	if (!miyajison->LoadData<bool>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kUseDepthStenciB }))
		return std::nullopt;

	depthStencilBufferInfo.emplace();

	depthStencilBufferInfo->dsvFormat = (DXGI_FORMAT)
		miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDsvFormatI});

	depthStencilBufferInfo->srvFormat = (DXGI_FORMAT)
		miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kSrvFormatI });

	depthStencilBufferInfo->clearDepth =
		miyajison->LoadData<float>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kClearDepthF });

	depthStencilBufferInfo->doesClearStencil = (D3D12_CLEAR_FLAGS)
		miyajison->LoadData<bool>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kClearStencilFlagB });

	depthStencilBufferInfo->clearStencil =
		miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kClearStencilI });

	depthStencilBufferInfo->numBuffer = 
		(NumBuffer)miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kNumBuffer_depthI });

	depthStencilBufferInfo->bufferName =
		miyajison->LoadData<std::string>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthBufferName });



	int const widthHeight[2] =
	{
		miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthWidthI }),
		miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthHeightI})
	};

	depthStencilBufferInfo->width = widthHeight[0] == -1 ? kWidth : widthHeight[0];
	depthStencilBufferInfo->height = widthHeight[1] == -1 ? kHeight : widthHeight[1];


	return depthStencilBufferInfo;
}

RenderContext::RenderPassState RenderContext::RenderPassCreator::PassSettingsLoader::ParseRenderPassState
(
	std::string const passName_
)
{
	auto* miyajison = Miyajison::Get();

	bool doesUseDepthBuffer =
		miyajison->LoadData<bool>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kUseDepthStenciB });

	return doesUseDepthBuffer ? RenderPassState
	(
		DepthTest(miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthTestI })),
		DepthEnable(miyajison->LoadData<bool>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthEnableB })),
		INT(miyajison->LoadData<int>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthBiasI })),
		FLOAT(miyajison->LoadData<float>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kDepthBiasClampF })),
		FLOAT(miyajison->LoadData<float>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kSlopeScaledDepthBiasF }))
	)
	: RenderPassState{};	//深度バッファ使わないならダミー値で構わん

}

std::optional<std::pair<std::string, std::string >> RenderContext::RenderPassCreator::PassSettingsLoader::ParseShaderFile
(
	std::string const passName_
)
{
	std::optional<std::pair<std::string, std::string >> ms_psOpt;
	std::pair<std::string, std::string > ms_ps;

	auto* miyajison = Miyajison::Get();
	bool isOffScreen = miyajison->LoadData<bool>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kIsOffScreenB });

	if (isOffScreen)
	{
		ms_ps.first = miyajison->LoadData<std::string>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kMS });
		ms_ps.second = miyajison->LoadData<std::string>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kPS });
		ms_psOpt = ms_ps;
	}

	return ms_psOpt;
}

std::vector<std::string> RenderContext::RenderPassCreator::PassSettingsLoader::ParseReferenceBufferNames(std::string const passName_)
{
	auto* miyajison = Miyajison::Get();

	return miyajison->LoadData<std::vector<std::string>>(DataKeyString::kSrcJsonFileName, { passName_,DataKeyString::kReferenceBufferNames });
}
