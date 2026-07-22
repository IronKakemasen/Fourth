
#include "ShaderCompiler.h"
#include "../../../../Utility/StringConnverter/StringConverter.h"

namespace
{
	auto fileName = "ShaderCompiler.cpp";
}


ShaderContext::Compiler::Compiler(ShaderContext::InstanceKey key_)
{
	InstantiateCorePatrts();
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] Microsoft::WRL::ComPtr<IDxcBlob> ShaderContext::Compiler::CompileShader
(
	std::string const& folderPath,
	std::string const& fileName_,
	const wchar_t* profile_,
	std::vector<std::wstring> const& extraArguments_
)
{
	Logger::Entry("Compile: " + fileName_);

	Microsoft::WRL::ComPtr<IDxcBlobEncoding> shaderSource = nullptr;

	//完成パス
	std::wstring cnvFilePath = AssembleFilePath(folderPath, fileName_);

	//ファイルを読み込む	
	DxcBuffer shaderSourceBuffer = LoadFile(cnvFilePath, shaderSource);

	//コンパイルする
	Microsoft::WRL::ComPtr<IDxcResult> result = Compile(shaderSourceBuffer, cnvFilePath, profile_, extraArguments_);

	//コンパイル結果が問題ないかチェックし、バイナリーデータを返す
	Microsoft::WRL::ComPtr<IDxcBlob> shaderBlob = CheckResult(result.Get());

	Logger::End("Compile: " + fileName_);

	//実行用のバイナリをリターン
	return shaderBlob;
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
Microsoft::WRL::ComPtr<IDxcResult> ShaderContext::Compiler::Compile
(
	DxcBuffer& shaderSourceBuffer_,
	std::wstring const& cnvFilePath_,
	const wchar_t* profile_,
	std::vector<std::wstring> const& extraArguments_
)
{
	std::vector<const wchar_t*> arguments;

	//argmentsを構築
	{
		//ターゲットファイル名とプロファイルの設定
		arguments.emplace_back(cnvFilePath_.c_str());
		arguments.emplace_back(L"-E");
		arguments.emplace_back(L"main");
		arguments.emplace_back(L"-T");
		//後で書き換えるための一時登録
		arguments.emplace_back(profile_);

		//基本フラグ（デバッグ情報や警告の扱い）の登録
#ifdef _DEBUG
		arguments.emplace_back(DXC_ARG_DEBUG);
		arguments.emplace_back(DXC_ARG_SKIP_OPTIMIZATIONS);
#else
		arguments.emplace_back(DXC_ARG_OPTIMIZATION_LEVEL3);
#endif
		arguments.emplace_back(DXC_ARG_WARNINGS_ARE_ERRORS);

		//リソースのエイリアスを許可
		arguments.emplace_back(L"-res-may-alias");
		//すべてのリソースがバインド済みとして最適化
		arguments.emplace_back(L"-all-resources-bound");

		//外部から渡されたマクロや追加引数を合流させる
		for (auto const& arg : extraArguments_)
		{
			arguments.push_back(arg.c_str());
		}
	}

	//argumentsをログに出力
	{
		std::string argString = "< arguments >----------------------------------------\n";
		size_t const argumentSize = arguments.size();
		for (size_t i = 1;i < argumentSize;++i)
		{
			argString += StringConverter::ConvertString(arguments.at(i));

			if (i + 1 < argumentSize)argString += " , ";

			if (i % 4 == 0)argString += "\n";
		}
		argString += "\n-----------------------------------------------------";
		Logger::Log(argString);
	}

	Microsoft::WRL::ComPtr<IDxcResult> shaderResult = nullptr;
	HRESULT hr = dxcCompiler.Get()->Compile
	(
		//読み込んだファイル
		&shaderSourceBuffer_,
		//コンパイルオプション
		arguments.data(),
		//コンパイルオプションの数
		UINT32(arguments.size()),
		//includeが含まれたもろもろ
		includeHandler.Get(),
		IID_PPV_ARGS(shaderResult.GetAddressOf())
	);

	//dxcが起動できないなどの致命的な状況
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "Crit Error(DxCompiler)", fileName);
	
	Logger::Log("Complete: compile");

	return shaderResult;
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
std::wstring ShaderContext::Compiler::AssembleFilePath
(
	std::string const& folderPath,
	std::string const& fileName_
)
{
	std::string const fileType = ".hlsl";
	std::string compositePath = folderPath + fileName_ + fileType;
	
	Logger::Log("FilePath: " + compositePath, fileName);

	//完成パス
	return StringConverter::ConvertString(compositePath);
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
Microsoft::WRL::ComPtr<IDxcBlob> ShaderContext::Compiler::CheckResult(IDxcResult* shaderResult_)
{
	//警告エラーが出てたらログに出して止める
	Microsoft::WRL::ComPtr<IDxcBlobUtf8> shaderError = nullptr;
	
	shaderResult_->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(shaderError.GetAddressOf()), nullptr);

	ErrorMessageOutput::Abort::DetectError
	(
		((shaderError == nullptr) || (shaderError->GetStringLength() == 0)),
		"シェーダーのエラーがあります", fileName
	);

	//コンパイル結果から実行用のバイナリ部分を受け取る
	Microsoft::WRL::ComPtr<IDxcBlob> shaderBlob = nullptr;
	
	HRESULT hr = shaderResult_->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "shaderBlobの生成失敗", fileName);

	Logger::Log("Create: ShaderBlob");

	return shaderBlob;
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
DxcBuffer ShaderContext::Compiler::LoadFile(std::wstring const& cnvFilePath_, Microsoft::WRL::ComPtr<IDxcBlobEncoding>& shaderSource_)
{
	HRESULT hr = dxcUtils.Get()->LoadFile(cnvFilePath_.c_str(), nullptr, &shaderSource_);
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "シェーダーファイルを読み込めません", fileName);

	//読み込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource_->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource_->GetBufferSize();
	//UTF-8であることを通知
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;

	Logger::Log("Complete:  loading shader");

	return shaderSourceBuffer;
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShaderContext::Compiler::InstantiateCorePatrts()
{
	HRESULT hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "dxcUtilsの生成失敗", fileName);
	Logger::Log("Create: dxcUtils", fileName);

	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "dxcCompilerの生成失敗", fileName);
	Logger::Log("Create: dxcCompiler", fileName);

	hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "includeHandlerの生成失敗", fileName);
	Logger::Log("Create: includeHandler", fileName);

	Logger::Log("Complete: CreatingCoreParts", fileName);
}
