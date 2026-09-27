#include "RootSignatureLibrary.h"


namespace
{
	auto const fileName = "RootSignatureLibrary.cpp";

}

RootSignatureContext::RootSignatureLibrary::RootSignatureLibrary(NexusFieldProof proof_)
{

}

RootSignatureContext::RootSignatureLibrary::~RootSignatureLibrary()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::BufferUsage::kGraphics>(HandleLicence licence_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((UINT)RootSignatureContext::BufferUsage::kGraphics), "中身が空です", fileName);

	return data.at((UINT)RootSignatureContext::BufferUsage::kGraphics).Get();

}

template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::BufferUsage::kCompute>(HandleLicence licence_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((int)RootSignatureContext::BufferUsage::kCompute), "中身が空です", fileName);

	return data.at((int)RootSignatureContext::BufferUsage::kCompute).Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::BufferUsage::kGraphics>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_)
{
	data.at(UINT(RootSignatureContext::BufferUsage::kGraphics)) = std::move(rootSig_);
}

template<>
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::BufferUsage::kCompute>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_)
{
	data.at(UINT(RootSignatureContext::BufferUsage::kCompute)) = std::move(rootSig_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::BufferUsage::kGraphics>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);


template
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::BufferUsage::kCompute>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);



template
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::BufferUsage::kGraphics>
(HandleLicence licence_);


template
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::BufferUsage::kCompute>
(HandleLicence licence_);
