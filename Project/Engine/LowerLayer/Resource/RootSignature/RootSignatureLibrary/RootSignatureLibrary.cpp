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
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::Usage::kGraphics>(HandleLicence licence_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((UINT)RootSignatureContext::Usage::kGraphics), "中身が空です", fileName);

	return data.at((UINT)RootSignatureContext::Usage::kGraphics).Get();

}

template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::Usage::kCompute>(HandleLicence licence_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((int)RootSignatureContext::Usage::kCompute), "中身が空です", fileName);

	return data.at((int)RootSignatureContext::Usage::kCompute).Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::Usage::kGraphics>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_)
{
	data.at(UINT(RootSignatureContext::Usage::kGraphics)) = std::move(rootSig_);
}

template<>
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::Usage::kCompute>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_)
{
	data.at(UINT(RootSignatureContext::Usage::kCompute)) = std::move(rootSig_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::Usage::kGraphics>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);


template
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::Usage::kCompute>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);



template
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::Usage::kGraphics>
(HandleLicence licence_);


template
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::Usage::kCompute>
(HandleLicence licence_);
