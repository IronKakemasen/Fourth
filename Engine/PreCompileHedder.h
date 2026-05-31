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
#include <directXMath.h>
#include <array>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"Dbghelp.lib")
#pragma comment(lib,"winmm.lib")


namespace ConstantForCalculation
{
	constexpr float kPi = 3.141592653589f;
	constexpr float kInvPi = 1.0f / 3.141592653589f;
	constexpr float kInv255 = 1.0f / 255.0f;
	constexpr float kHalf = 0.5f;

}

namespace ProjectConfig
{
	namespace Window
	{
		constexpr float kWidth = 1280.0f;
		constexpr float kHeight = 720.0f;
		constexpr float kDefaultFovY = 90.0f * 3.141592653589f / 180.0f;
		inline const LPCWSTR kTitle = L"Fourth";
	}

	namespace Render
	{
		constexpr int kRequiredGPUBufferSum = 2;
	}

	namespace Debug
	{
		constexpr bool kEnableDebugLayer = true;
		constexpr bool kEnableLeakChecker = true;
		constexpr bool kEnablePointerValidator = true;
	}
}



