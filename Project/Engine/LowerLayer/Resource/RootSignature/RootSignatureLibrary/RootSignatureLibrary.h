#pragma once
#include "../RootSignatureContext.h"


class RootSignatureContext::RootSignatureLibrary
{
public:

	struct HandleLicence;

	RootSignatureLibrary(NexusFieldProof proof_);
	~RootSignatureLibrary();

	template<Usage usage>
	ID3D12RootSignature* Export(HandleLicence licence_);
	
	template<Usage usage>
	void Import(HandleLicence licence_,Microsoft::WRL::ComPtr<ID3D12RootSignature>&& rootSig_);


private:
	///本元データ
	std::array<Microsoft::WRL::ComPtr<ID3D12RootSignature>, (int)Usage::kCount> data;


};


struct RootSignatureContext::RootSignatureLibrary::HandleLicence
{
private:

	friend class RootSignatureContext::RootSignatureCreator;
	explicit HandleLicence() = default;
};




