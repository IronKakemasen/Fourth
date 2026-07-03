#include "PreCompileHeader.h"
#include "RootSignatureAssembler.h"

//ツール
#include "ToolCreateRootSignature/CreateRootParam/CreateRootParam.h"
#include "ToolCreateRootSignature/CreateStaticSamplerDesc/CreateStaticSamplerDesc.h"

namespace
{
	auto const fileName = "RootSignatureAssembler.cpp";
}


using namespace RootSignatureLayoutComponent;

RootSignatureContext::Assembler::Assembler(RootSignatureContext::InstanceKey key_, RootSignatureContext::CommandCreateRootSignature cmd_)
	:cmdCreaterootSignature(cmd_)
{

}

RootSignatureContext::Assembler::~Assembler() {};
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignatureContext::Assembler::Create(const RootSignatureDesc::Graphics& srcDesc_)
{
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

	//ルートパラメーターの生成
	std::vector<D3D12_ROOT_PARAMETER> tmpRootParam;
	{
		CreateRootParam createRootParam;

		tmpRootParam = createRootParam.CreateRootparamGloballyCommonCBV(srcDesc_);
	}

	//静的サンプラーディスクの生成
	std::vector<D3D12_STATIC_SAMPLER_DESC> tmpStaticSamplerDesc;
	{
		CreateStaticSamplerDesc createStaticSamplerDesc;

		tmpStaticSamplerDesc = createStaticSamplerDesc.Create(srcDesc_);
	}

	//D3D12_ROOT_SIGNATURE_DESCに入力
	D3D12_ROOT_SIGNATURE_DESC desc;
	{
		desc.pParameters = tmpRootParam.data();
		desc.NumParameters = UINT(tmpRootParam.size());
		desc.pStaticSamplers = tmpStaticSamplerDesc.data();
		desc.NumStaticSamplers = UINT(tmpStaticSamplerDesc.size());
		desc.Flags =
			D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS	|
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS		|
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS	|
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS  |
			D3D12_ROOT_SIGNATURE_FLAG_CBV_SRV_UAV_HEAP_DIRECTLY_INDEXED |
			D3D12_ROOT_SIGNATURE_FLAG_SAMPLER_HEAP_DIRECTLY_INDEXED;
	}

	//シリアライズしてバイナリにする
	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	{
		HRESULT hr = D3D12SerializeRootSignature
		(
			&desc,
			D3D_ROOT_SIGNATURE_VERSION_1,
			&signatureBlob,
			&errorBlob
		);

		ErrorMessageOutput::Abort::DetectError
		(
			SUCCEEDED(hr),
			(errorBlob) ? reinterpret_cast<char*>(errorBlob->GetBufferPointer()): " ",
			fileName
		);
	}

	//バイナリをもとにrootSignatureを作成
	{
		cmdCreaterootSignature
		(
			0,
			signatureBlob,
			rootSignature.GetAddressOf()
		);
	}


	return rootSignature;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

