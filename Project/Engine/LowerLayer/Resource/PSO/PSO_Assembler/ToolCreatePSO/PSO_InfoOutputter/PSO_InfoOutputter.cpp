
#include "PSO_InfoOutputter.h"
#include "../../PipelineStateDesc.h"


using namespace RenderStateComponent;

void PSO_InfoOutputter::OutputGraphicsPSOInfo
(
	PipelineStateDesc::Graphics& srcDesc_,
	std::string debugName_
)
{
	debugName = "< " + debugName_ + " >";

	//カラーバッファ関連
	{
		debugText += "---RenderTarget---\n";

		//rtvフォーマットとブレンドモード
		auto const kRtSize = srcDesc_.renderTargetDesc.rtvFormatContainer.size();
		for (size_t i = 0;i < kRtSize;++i)
		{
			debugText += "[ " + srcDesc_.renderTargetDesc.bufferNameContainer[i] + " ]\n";
			debugText += "Format: " + DebugTextTable(srcDesc_.renderTargetDesc.rtvFormatContainer[i]) + "\n";
			debugText += "BlendMode: " + DebugTextTable(srcDesc_.renderTargetDesc.blendModeContainer[i]) + "\n";
		}
		debugText += "\n";
	}

	//ディプスバッファ関連
	{
		debugText += "---DepthStencilBuffer---";

		debugText += "[ " + srcDesc_.depthStencilDesc.bufferName + " ]\n";
		(srcDesc_.depthStencilDesc.blendMode == BlendMode::kOpaque) ? debugText += "DepthWriteMask: MASK_ALL" : debugText += "DepthWriteMask: MASK_ZERO";
		debugText += "DepthStencilFormat: " + DebugTextTable(srcDesc_.depthStencilDesc.dsvFormat) + "\n";
		debugText += "DepthWrite: " + DebugTextTable(srcDesc_.depthStencilDesc.depthWrite) + "\n";
		debugText += "DepthTest: " + DebugTextTable(srcDesc_.depthStencilDesc.depthTest) + "\n";
	}

	//シェーダー
	{
		debugText += "---SrcShaderFile---\n";
		debugText += "MeshShader: " + srcDesc_.shaderSet.meshShaderName + "\n";
		if (srcDesc_.shaderSet.pixelShader) debugText += "pixelShader: " + srcDesc_.shaderSet.pixelShaderName + "\n";
	}

	{

	}


}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///サンキュ－ジェミニ☆
std::string const PSO_InfoOutputter::DebugTextTable(DXGI_FORMAT format_) const
{
	std::string formatString{};

	switch (format_)
	{
		// --- 1. カラーバッファ / レンダーターゲット用 (標準 & sRGB) ---
	case DXGI_FORMAT_R8G8B8A8_UNORM:         formatString = "R8G8B8A8_UNORM"; break;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:    formatString = "R8G8B8A8_UNORM_SRGB"; break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:         formatString = "B8G8R8A8_UNORM"; break; // SwapChain等
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:    formatString = "B8G8R8A8_UNORM_SRGB"; break;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:     formatString = "R16G16B16A16_FLOAT"; break; // HDR
	case DXGI_FORMAT_R32G32B32A32_FLOAT:     formatString = "R32G32B32A32_FLOAT"; break;
	case DXGI_FORMAT_R11G11B10_FLOAT:        formatString = "R11G11B10_FLOAT"; break; // 高効率HDR
	case DXGI_FORMAT_R10G10B10A2_UNORM:      formatString = "R10G10B10A2_UNORM"; break;

		// --- 2. 1〜2チャンネル（シャドウマップ、マスク、法線、1チャンネルカラー等） ---
	case DXGI_FORMAT_R8_UNORM:               formatString = "R8_UNORM"; break;
	case DXGI_FORMAT_R16_FLOAT:              formatString = "R16_FLOAT"; break;
	case DXGI_FORMAT_R32_FLOAT:              formatString = "R32_FLOAT"; break;
	case DXGI_FORMAT_R16G16_FLOAT:           formatString = "R16G16_FLOAT"; break;
	case DXGI_FORMAT_R32G32_FLOAT:           formatString = "R32G32_FLOAT"; break;

		// --- 3. デプス / ステンシルバッファ専用 (DSV用) ---
	case DXGI_FORMAT_D32_FLOAT:              formatString = "D32_FLOAT"; break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:      formatString = "D24_UNORM_S8_UINT"; break;
	case DXGI_FORMAT_D16_UNORM:              formatString = "D16_UNORM"; break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:   formatString = "D32_FLOAT_S8X24_UINT"; break;

		// --- 4. デプス関連の TYPELESS (SRV/DSVのバインド切り替え用) ---
	case DXGI_FORMAT_R32_TYPELESS:           formatString = "R32_TYPELESS"; break;           // D32_FLOAT用
	case DXGI_FORMAT_R24G8_TYPELESS:         formatString = "R24G8_TYPELESS"; break;         // D24_UNORM_S8_UINT用
	case DXGI_FORMAT_R16_TYPELESS:           formatString = "R16_TYPELESS"; break;           // D16_UNORM用
	case DXGI_FORMAT_R32G8X24_TYPELESS:      formatString = "R32G8X24_TYPELESS"; break;      // D32_FLOAT_S8X24_UINT用

		// --- 5. カラー関連の TYPELESS ---
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:      formatString = "R8G8B8A8_TYPELESS"; break;
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:      formatString = "B8G8R8A8_TYPELESS"; break;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:  formatString = "R16G16B16A16_TYPELESS"; break;
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:  formatString = "R32G32B32A32_TYPELESS"; break;

	default:
		formatString = "UNKNOWN_OR_UNSUPPORTED_FORMAT (" + std::to_string(static_cast<int>(format_)) + ")";
		break;
	}

	return formatString;
}

std::string const PSO_InfoOutputter::DebugTextTable(BlendMode mode_) const
{
	switch (mode_)
	{
	case BlendMode::kOpaque:     return "Opaque";
	case BlendMode::kAlphaBlend: return "AlphaBlend";
	case BlendMode::kAdditive:   return "Additive";
	default:                     return "UNKNOWN_BLEND_MODE";
	}
}

std::string const PSO_InfoOutputter::DebugTextTable(FillMode mode_) const
{
	switch (mode_)
	{
	case FillMode::kWireFrame: return "WireFrame";
	case FillMode::kSolid:     return "Solid";
	default:                   return "UNKNOWN_FILL_MODE";
	}
}

std::string const PSO_InfoOutputter::DebugTextTable(CullMode mode_) const
{
	switch (mode_)
	{
	case CullMode::kNone:  return "None";
	case CullMode::kFront: return "Front";
	case CullMode::kBack:  return "Back";
	default:               return "UNKNOWN_CULL_MODE";
	}
}

std::string const PSO_InfoOutputter::DebugTextTable(DepthWrite write_) const
{
	switch (write_)
	{
	case DepthWrite::kDisable: return "Disable";
	case DepthWrite::kEnable:  return "Enable";
	default:                   return "UNKNOWN_DEPTH_WRITE";
	}
}

std::string const PSO_InfoOutputter::DebugTextTable(DepthTest test_) const
{
	switch (test_)
	{
	case DepthTest::kLessEqual:    return "LessEqual";
	case DepthTest::kGreaterEqual: return "GreaterEqual";
	default:                       return "UNKNOWN_DEPTH_TEST";
	}
}