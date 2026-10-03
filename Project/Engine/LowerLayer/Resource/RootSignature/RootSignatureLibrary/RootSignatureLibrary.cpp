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
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::PsoType::kGraphics>(HandleLicence licence_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((UINT)RootSignatureContext::PsoType::kGraphics), "中身が空です", fileName);

	return data.at((UINT)RootSignatureContext::PsoType::kGraphics).Get();

}

template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::PsoType::kCompute>(HandleLicence licence_)
{
	ErrorMessageOutput::Assert::DetectError(data.at((int)RootSignatureContext::PsoType::kCompute), "中身が空です", fileName);

	return data.at((int)RootSignatureContext::PsoType::kCompute).Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::PsoType::kGraphics>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_)
{
	data.at(UINT(RootSignatureContext::PsoType::kGraphics)) = std::move(rootSig_);
}

template<>
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::PsoType::kCompute>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_)
{
	data.at(UINT(RootSignatureContext::PsoType::kCompute)) = std::move(rootSig_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::PsoType::kGraphics>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);


template
void RootSignatureContext::RootSignatureLibrary::Import<RootSignatureContext::PsoType::kCompute>
(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);



template
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::PsoType::kGraphics>
(HandleLicence licence_);


template
ID3D12RootSignature* RootSignatureContext::RootSignatureLibrary::Export<RootSignatureContext::PsoType::kCompute>
(HandleLicence licence_);
