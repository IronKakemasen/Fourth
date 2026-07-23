#include "DeviceContextSetupper.h"
#include "EngineRequirementsChecker/EngineRequirementsChecker.h"

#include "StringConnverter/StringConverter.h"

namespace 
{
	std::string fileName = "DeviceContextSetupper.cpp";
}

DeviceContext::Setupper::Setupper(InstanceKey instanceKey_)
{
	//dxgiFactoryの生成
	CreateDXGI_Factory();

	//アダプターを取得
	FetchAdapter();

	//デバイスの生成
	CreateDevice();

	//デバッグレイヤーのフィルターを設定
	SetDebugLayerFilter();

	//シェーダーモデルサポートチェック
	EngineRequiementsChecker::ShaderModelChack(device.Get(),ProjectConfig::Render::kRequiredShaderModel);

	//メッシュシェーダーをサポートしているかチェック
	EngineRequiementsChecker::IsMeshShaderSupported(device.Get());

	//ResourceBindingTierが必要値を満たしているか
	EngineRequiementsChecker::ResourceBindingTierCheck(device.Get());

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] std::tuple<Microsoft::WRL::ComPtr<IDXGIAdapter4>, Microsoft::WRL::ComPtr<ID3D12Device8>, Microsoft::WRL::ComPtr<IDXGIFactory7>>
DeviceContext::Setupper::HandOver(DeviceContext::InstanceKey instanceKey_)
{
	return std::make_tuple(std::move(useAdapter), std::move(device), std::move(dxgiFactory));
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::Setupper::SetDebugLayerFilter()
{
#if defined(_DEBUG)

	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;

	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		// ヤバいエラーの時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		// エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		// 警告時に止まる
		// infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		// 抑制するメッセージのID
		D3D12_MESSAGE_ID denyIds[] =
		{
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };

		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = static_cast<UINT>(_countof(denyIds));
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = static_cast<UINT>(_countof(severities));
		filter.DenyList.pSeverityList = severities;

		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);

	}
#endif

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::Setupper::FetchAdapter()
{
	//一番いいアダプタを頼む
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		//アダプタの情報を取得する
		DXGI_ADAPTER_DESC3 adapterDisc{};
		HRESULT hr = useAdapter->GetDesc3(&adapterDisc);
		ErrorMessageOutput::Abort::DetectError((SUCCEEDED(hr)), "アダプタの取得に失敗しました", fileName);

		//ソフトウェアアダプタでなければ採用
		if (!(adapterDisc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			//採用したアダプタの情報をログに出力
			Logger::Log(StringConverter::ConvertString(std::format(L"Use Adapter:{}", adapterDisc.Description)));

			break;
		}
		//ソフトウェアアダプタの場合はなかったことに
		useAdapter = nullptr;
	}

	//適切なアダプタが見つからなかった場合は起動できない
	ErrorMessageOutput::Abort::DetectError((useAdapter != nullptr), "適切なアダプタが見つからなかった", fileName);
	Logger::Log("Fetch: Adapter");
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::Setupper::CreateDXGI_Factory()
{
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	//初期化の根本的な部分でエラーが出た場合はプログラムが間違っているか、
	//どうにもできない場合が多いのでassertにしておく
	ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "DXGIFactoryの生成に失敗しました", fileName);
	Logger::Log("Create: DXGI_Factory");

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::Setupper::CreateDevice()
{
	//機能レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0
	};

	std::string featureLevelStrings[] = { "12.2","12.1","12.0" };

	//高い順に生成できるか試していく
	for (size_t i = 0; i < _countof(featureLevels); ++i)
	{
		Microsoft::WRL::ComPtr<ID3D12Device> d3d12Device;

		//採用したアダプタでデバイスを生成
		HRESULT hr = D3D12CreateDevice(useAdapter.Get(), featureLevels[i], IID_PPV_ARGS(&d3d12Device));
		ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "デバイスの生成に失敗", fileName);
		
		//型変換
		hr = d3d12Device.As(&device); 
		if (FAILED(hr)) continue;


		//指定した機能7レベルでデバイスが生成できたか確認
		if (SUCCEEDED(hr))
		{
			//生成できたのでログを出力してループを抜ける
			Logger::Log(std::format("FeatureLevel:{}", featureLevelStrings[i]));

			break;
		}
	}

	//デバイスの生成が上手くいかなかったので起動できない
	ErrorMessageOutput::Abort::DetectError(device != nullptr, "デバイスの生成が上手くいかなかったので起動できない", fileName);
	Logger::Log("Create: Device");
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
