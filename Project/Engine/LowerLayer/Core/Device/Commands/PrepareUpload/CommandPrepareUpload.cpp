#include "PreCompileHeader.h"
#include "CommandPrepareUpload.h"

CommandPrepareUpload::CommandPrepareUpload(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

void CommandPrepareUpload::PrepareUpload
(
	ID3D12Device8* device_,
	DirectX::ScratchImage const& image_,
	std::vector<D3D12_SUBRESOURCE_DATA>& subResources_
)
{
	HRESULT hr = DirectX::PrepareUpload
	(
		device_,
		image_.GetImages(),
		image_.GetImageCount(),
		image_.GetMetadata(),
		subResources_
	);

	ErrorMessageOutput::Abort::DetectError
	(
		SUCCEEDED(hr),
		"DirectX::PrepareUpload()からのエラーです",
		"CommandPrepareUpload.cpp"
	);
}
