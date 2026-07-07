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
#include <dxcapi.h>

#include "../../External/d3dx12/d3dx12.h"
#include "../../External/imgui/imgui.h"

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
#include <bit>
#include <cstdint>

//abort()やassert()でエラーを吐いて文字列を出力する
#include "../LowerLayer/Debug/ErrorMessageOutput/ErrorMessageOutput.h"
//出力ウィンドウとログファイルにログを出力
#include "../LowerLayer/Debug/Logger/Logger.h"
#include "../ProjectConfig.h"


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"Dbghelp.lib")
#pragma comment(lib,"winmm.lib")






