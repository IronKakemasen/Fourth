#include "PreCompileHeader.h"
#include "PassDescAssembler.h"
#include "Miyajison.h"

using namespace ProjectConfig::Window;

namespace
{
	auto const fileName = "PassDescAssembler.cpp";
}


[[nodiscard]] PassRequiredInfo RenderContext::RenderPassCreator::PassDescAssembler::LoadPassSettings(std::string const passName_)
{
	PassRequiredInfo info;

	std::string const srcJsonFileName = "RenderPassSettings";
	
	//カラーバッファの設定情報
	info.colorBuffersInfo= ParseColorBufferInfo(passName_, srcJsonFileName);
	//深度ステンシルバッファの設定情報
	info.depthStencilBufferInfo = ParseDepthStencilBufferInfo(passName_, srcJsonFileName);

	///未分類（いつかリファクタ）
	auto* miyajison = Miyajison::Get();
	info.depthTest = RenderPassComponent::DepthTest(miyajison->LoadData<int>(srcJsonFileName, { passName_,PassRequiredInfo::dataKeyString.kDepthTestI }));
	info.depthEnable = RenderPassComponent::DepthEnable(miyajison->LoadData<bool>(srcJsonFileName, { passName_,PassRequiredInfo::dataKeyString.kDepthEnableB }));


	return info;
}

std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> RenderContext::RenderPassCreator::PassDescAssembler::ParseColorBufferInfo
(
	std::string const passName_,
	std::string const jsonFileName_
)
{
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBufferInfo;

	auto* miyajison = Miyajison::Get();

	//カラーバッファのフォーマット。以降、こいつの数といくつかのパラメーターは同期している前提で進める
	auto const colorBufferFormats = 
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kColorFormatI });
	//カラーバッファの数
	auto const numColorBuffers = colorBufferFormats.size();

	//カラーバッファのクリアカラー
	auto const clearColors = 
		miyajison->LoadData<std::vector<std::vector<float>>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kClearColorV4 });

	//カラーバッファの縦横
	auto const widthContainer = 
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kWidthI });
	auto const heightContainer =
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kHeightI });

	//サイズの比が一致してるかチェック
	ErrorMessageOutput::Assert::DetectError
	(
		numColorBuffers == clearColors.size()		 &&
		numColorBuffers == widthContainer.size()	 &&
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
	}


	return colorBufferInfo;
}


std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> RenderContext::RenderPassCreator::PassDescAssembler::ParseDepthStencilBufferInfo
(
	std::string const passName_,
	std::string const jsonFileName_
)
{

	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;

	auto* miyajison = Miyajison::Get();

	//深度バッファ使わんならしらん
	if (!miyajison->LoadData<bool>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kUseDepthStenciB }))
		return std::nullopt;

	depthStencilBufferInfo->dsvFormat = 
		(DXGI_FORMAT)miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kDsvFormatI});

	depthStencilBufferInfo->srvFormat = 
		(DXGI_FORMAT)miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kSrvFormatI });

	depthStencilBufferInfo->clearDepth =
		miyajison->LoadData<float>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kClearDepthF });

	depthStencilBufferInfo->clearStencil =
		miyajison->LoadData<float>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kClearStencilF });

	return depthStencilBufferInfo;
}
