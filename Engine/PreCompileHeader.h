#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <wrl.h>
#include <dxgidebug.h>
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dbghelp.h>
#include <wrl/client.h>
#include <directXMath.h>

#include "../External/d3dx12/d3dx12.h"
#include "../External/imgui/imgui.h"

#include <vector>
#include <memory>
#include <string>
#include <optional>
#include <unordered_map>
#include <stdint.h>
#include <assert.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <array>
#include <format>
#include <functional>
#include <mutex>
#include <variant>
#include <type_traits> 

//abort()やassert()でエラーを吐いて文字列を出力する
#include "Debug/ErrorMessageOutput/ErrorMessageOutput.h"
//出力ウィンドウとログファイルにログを出力
#include "Debug/Logger/Logger.h"


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"Dbghelp.lib")
#pragma comment(lib,"winmm.lib")

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ConstantForCalculation
{
	constexpr float kPi = 3.141592653589f;
	constexpr float kInvPi = 1.0f / 3.141592653589f;
	constexpr float kInv255 = 1.0f / 255.0f;
	constexpr float kHalf = 0.5f;

}
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
		constexpr float kDefaultFovY = 90.0f * 3.141592653589f / 180.0f;
		constexpr std::array<float,4> kColor = { 1.0f,0.0f,0.0f,1.0f };
		constexpr DXGI_FORMAT kRtFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
	}

	namespace Render
	{
		enum NumBuffer
		{
			kSingleBuffer = 1,
			kDoubleBuffer = 2
		};

		constexpr D3D_SHADER_MODEL kMaximumShaderModel = D3D_SHADER_MODEL_6_6;	
	}


	namespace Debug
	{
		//DebugLayer
		constexpr bool kEnableDebugLayer = true;
		//ポインター破壊検知
		constexpr bool kEnablePointerValidator = true;
		//Comptrのリークチェック
		constexpr bool kEnableLeakChecker = true;

	}

	namespace Core
	{
		constexpr uint32_t kNumDescriptorsRTVHeap = 16;
		constexpr uint32_t kNumDescriptorSRVHeap = 1024;
		constexpr uint32_t kNumDescriptorsDSVHeap = 16;
	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class ViewType
{
	kSRV,
	kUAV,
	kSampler,
	kRTV,
	kDSV,

	kCount
};




