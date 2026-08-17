#include "PreCompileHeader.h"
#include "PassSettingsLoader.h"

using namespace ProjectConfig::Window;
using namespace ProjectConfig::Render;

namespace
{
	auto const fileName = "PassSettingsLoader.cpp";
}


[[nodiscard]] PassRequiredInfo RenderContext::RenderPassCreator::PassSettingsLoader::Load(std::string const passName_)
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
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kColorFormatI });
	//カラーバッファの数
	auto const numColorBuffers = colorBufferFormats.size();

	//カラーバッファのクリアカラー
	auto const clearColors = 
		miyajison->LoadData<std::vector<std::vector<float>>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kClearColorV4 });

	//カラーバッファの縦横
	auto const widthContainer = 
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kColorWidthI });
	auto const heightContainer =
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kColorHeightI });

	//シングルかダブルか
	auto const numBufferContainer =
		miyajison->LoadData<std::vector<int>>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kNumBuffer_colorI });


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
	if (!miyajison->LoadData<bool>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kUseDepthStenciB }))
		return std::nullopt;

	depthStencilBufferInfo.emplace();

	depthStencilBufferInfo->dsvFormat = 
		(DXGI_FORMAT)miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kDsvFormatI});

	depthStencilBufferInfo->srvFormat = 
		(DXGI_FORMAT)miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kSrvFormatI });

	depthStencilBufferInfo->clearDepth =
		miyajison->LoadData<float>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kClearDepthF });

	depthStencilBufferInfo->clearStencil =
		miyajison->LoadData<float>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kClearStencilF });

	depthStencilBufferInfo->numBuffer = 
		(NumBuffer)miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kNumBuffer_depthI });


	int const widthHeight[2] =
	{
		miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kDepthWidthI }),
		miyajison->LoadData<int>(jsonFileName_, { passName_,PassRequiredInfo::dataKeyString.kDepthHeightI})
	};

	depthStencilBufferInfo->width = widthHeight[0] == -1 ? kWidth : widthHeight[0];
	depthStencilBufferInfo->height = widthHeight[1] == -1 ? kHeight : widthHeight[1];


	return depthStencilBufferInfo;
}
