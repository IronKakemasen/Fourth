#pragma once

//バッファのユニークID
using BufferUniqueID = uint32_t;
//srv/uavディスクリプタヒープ上のインデックス
using SRVHeapIndex = uint32_t;
//メッシュデータのID
using MeshDataID = uint32_t;
static constexpr UINT kInvalid = 0xffffffff;


///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ProjectConfig
{
	namespace Window
	{
		inline const LPCWSTR kTitle = L"Fourth";
		constexpr UINT kWidth = 1280;
		constexpr UINT kHeight = 720;
		constexpr float kDefaultFovY = MathConstants::kPi * MathConstants::kHalf;
		constexpr std::array<float, 4> kColor = { 1.0f,0.0f,0.0f,1.0f };
	}

	namespace Render
	{
		enum class NumBuffer
		{
			kSingleBuffer = 1,
			kDoubleBuffer = 2
		};

		enum class CBufferSize
		{
			//TransformMatrixBufferの同時存在最大数
			kSizeOfTransformMatrixContainerBuffer = 100,
			//そのマテリアルバージョン
			kSizeOfMaterialContainerBuffer = 100,

		};

		constexpr D3D_SHADER_MODEL kRequiredShaderModel = D3D_SHADER_MODEL_6_6;
		constexpr DXGI_FORMAT kSwapChainBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
	}

	namespace Debug
	{
#ifdef _DEBUG

		//DebugLayer
		constexpr bool kEnableDebugLayer = true;
		//ポインター破壊検知
		constexpr bool kEnablePointerValidator = true;
		//Comptrのリークチェック
		constexpr bool kEnableLeakChecker = true;
		//Jsonファイルを読み込むときに型チェックを行うかどうか
		constexpr bool kEnableJsonDataTypeCheck = true;

#endif // _DEBUG

#ifndef _DEBUG

		//DebugLayer
		constexpr bool kEnableDebugLayer = false;
		//ポインター破壊検知
		constexpr bool kEnablePointerValidator = false;
		//Comptrのリークチェック
		constexpr bool kEnableLeakChecker = false;
		//Jsonファイルを読み込むときに型チェックを行うかどうか
		constexpr bool kEnableJsonDataTypeCheck = false;


#endif // !_DEBUG


	}

	namespace Core
	{
		constexpr uint32_t kNumDescriptorsRTVHeap = 16;
		constexpr uint32_t kNumDescriptorSRVHeap = 1024;
		constexpr uint32_t kNumDescriptorsDSVHeap = 16;
	}

	namespace Texture
	{
		//ノーデータテクスチャのファイル名
		inline std::string const kNoDataAlbedoTex	= "noData_albedo";
		inline std::string const kNoDataNormalTex	= "noData_normal";
		inline std::string const kNoDataEmissiveTex = "noData_emissive";
		inline std::string const kNoDataSprite		= "noData_albedo";

	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
