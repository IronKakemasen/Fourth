#pragma once
#include "../ShaderContext.h"

class ShaderContext::Compiler
{
public:

	Compiler(ShaderContext::InstanceKey key_);

	[[nodiscard]] Microsoft::WRL::ComPtr<IDxcBlob> CompileShader
	(
		std::string const& folderPath,
		std::string const& fileName_,
		const wchar_t* profile_,
		std::vector<std::wstring> const& extraArguments_ = {}
	);
	
private:

	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils = nullptr;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler = nullptr;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler = nullptr;

	//コアパーツのインスタンス化
	void InstantiateCorePatrts();
	//ファイルパスにする
	std::wstring AssembleFilePath(std::string const& folderPath, std::string const& fileName_);
	//シェーダーファイルを読み込む
	DxcBuffer LoadFile(std::wstring const& cnvFilePath_, Microsoft::WRL::ComPtr<IDxcBlobEncoding>& shaderSource_);
	//コンパイルする
	Microsoft::WRL::ComPtr<IDxcResult> Compile
	(
		DxcBuffer& shaderSourceBuffer_, 
		std::wstring const& cnvFilePath_, 
		const wchar_t* profile_,
		std::vector<std::wstring> const& extraArguments_
	);
	//コンパイル結果が問題ないかチェックし、バイナリーデータを返す
	Microsoft::WRL::ComPtr<IDxcBlob> CheckResult(IDxcResult* shaderResult_);

};

