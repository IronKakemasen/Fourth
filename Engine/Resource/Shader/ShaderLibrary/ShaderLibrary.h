#pragma once
#include "../ShaderContext.h"


//外部
#include "../../../Render/RenderPathStructure/RenderPathComposer/RenderPathComposer.h"

struct RenderPath::PathComposer::ShaderCombiner;

class ShaderLibrary
{
public:

	struct InstanceKey;
	struct GetDataKey;

	ShaderLibrary(InstanceKey key_, ShaderContext::Compiler* compiler_);

	///シェーダーバイナリオブジェのポインタを輸出
	IDxcBlob* Export(GetDataKey key_, const std::string& fileName_);

private:
	///本元データ
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<IDxcBlob>> data;

	//シェーダー登録ファイルから何が登録されているか読み込む
	std::unordered_map<std::string, std::string> LoadShaderRegistry(const std::string& filePath);
	//コンパイルする
	void CompileAllShaderFiles(ShaderContext::Compiler* compiler_);
};


struct ShaderLibrary::InstanceKey
{
private:

	friend class ShaderContext;
	explicit InstanceKey() = default;
};

struct ShaderLibrary::GetDataKey
{
private:
	friend struct RenderPath::PathComposer::ShaderCombiner;
	explicit GetDataKey() = default;
};
