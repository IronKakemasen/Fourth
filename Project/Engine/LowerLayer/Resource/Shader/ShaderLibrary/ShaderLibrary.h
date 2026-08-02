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

	//コンパイルする
	void CompileAllShaderFiles(ShaderContext::Compiler* compiler_);
	std::unordered_map<std::string, std::vector<std::wstring>> GetArgs();


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
