#include "PreCompileHeader.h"
#include "PassSettingsLoader.h"

using namespace ProjectConfig::Window;
using namespace ProjectConfig::Render;
using namespace RenderPassComponent;

namespace
{
	auto const fileName = "PassSettingsLoader.cpp";
}


[[nodiscard]] RenderContext::PassDesc RenderContext::RenderPassCreator::PassSettingsLoader::Load(std::string const passName_)
{
	std::string const srcJsonFileName = "RenderPassSettings";
	
	auto* miyajison = Miyajison::Get();

	PassDesc desc
	(
		DepthTest(miyajison->LoadData<int>(srcJsonFileName, { passName_,PassDesc::dataKeyString.kDepthTestI })),
		DepthEnable(miyajison->LoadData<bool>(srcJsonFileName, { passName_,PassDesc::dataKeyString.kDepthEnableB })),
		ParseColorBufferInfo(passName_, srcJsonFileName),
		ParseDepthStencilBufferInfo(passName_, srcJsonFileName)
	);

	return desc;
}

std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> RenderContext::RenderPassCreator::PassSettingsLoader::ParseColorBufferInfo
(
	std::string const passName_,
	std::string const jsonFileName_
)
{
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBufferInfo;

	auto* miyajison = Miyajison::Get();

	//カラーバッファのフォーマット。以降、こいつの数といくつかのパラメーターは同期している前提で進める
	auto const colorBufferFormats = 
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassDesc::dataKeyString.kColorFormatI });
	//カラーバッファの数
	auto const numColorBuffers = colorBufferFormats.size();

	//カラーバッファのクリアカラー
	auto const clearColors = 
		miyajison->LoadData<std::vector<std::vector<float>>>(jsonFileName_, { passName_,PassDesc::dataKeyString.kClearColorV4 });

	//カラーバッファの縦横
	auto const widthContainer = 
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassDesc::dataKeyString.kColorWidthI });
	auto const heightContainer =
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassDesc::dataKeyString.kColorHeightI });

	//シングルかダブルか
	auto const numBufferContainer =
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassDesc::dataKeyString.kNumBuffer_colorI });


	//サイズの比が一致してるかチェック
	ErrorMessageOutput::Assert::DetectError
	(
		numColorBuffers == clearColors.size()		 &&
		numColorBuffers == widthContainer.size()	 &&
		numColorBuffers == numBufferContainer.size() &&
		numColorBuffers == heightContainer.size(),
		"カラーバッファの設定が間違っている",
		fileName
	);

	colorBufferInfo.resize(numColorBuffers);
	for (auto i = 0;i < numColorBuffers;++i)
	{
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
	std::string const passName_,
	std::string const jsonFileName_
)
{

	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;

	auto* miyajison = Miyajison::Get();

	//深度バッファ使わんならしらん
	if (!miyajison->LoadData<bool>(jsonFileName_, { passName_,PassDesc::dataKeyString.kUseDepthStenciB }))
		return std::nullopt;

	depthStencilBufferInfo.emplace();

	depthStencilBufferInfo->dsvFormat = 
		(DXGI_FORMAT)miyajison->LoadData<int>(jsonFileName_, { passName_,PassDesc::dataKeyString.kDsvFormatI});

	depthStencilBufferInfo->srvFormat = 
		(DXGI_FORMAT)miyajison->LoadData<int>(jsonFileName_, { passName_,PassDesc::dataKeyString.kSrvFormatI });

	depthStencilBufferInfo->clearDepth =
		miyajison->LoadData<float>(jsonFileName_, { passName_,PassDesc::dataKeyString.kClearDepthF });

	depthStencilBufferInfo->clearStencil =
		miyajison->LoadData<int>(jsonFileName_, { passName_,PassDesc::dataKeyString.kClearStencilI });

	depthStencilBufferInfo->numBuffer = 
		(NumBuffer)miyajison->LoadData<int>(jsonFileName_, { passName_,PassDesc::dataKeyString.kNumBuffer_depthI });


	int const widthHeight[2] =
	{
		miyajison->LoadData<int>(jsonFileName_, { passName_,PassDesc::dataKeyString.kDepthWidthI }),
		miyajison->LoadData<int>(jsonFileName_, { passName_,PassDesc::dataKeyString.kDepthHeightI})
	};

	depthStencilBufferInfo->width = widthHeight[0] == -1 ? kWidth : widthHeight[0];
	depthStencilBufferInfo->height = widthHeight[1] == -1 ? kHeight : widthHeight[1];


	return depthStencilBufferInfo;
}
