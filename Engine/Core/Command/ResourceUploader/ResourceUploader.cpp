#include "PreCompileHeader.h"
#include "ResourceUploader.h"


namespace
{
	auto fileName = "ResourceUploader.cpp";
}

CommandContext::ResourceUploader::ResourceUploader
(
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>&& allocator_forUpload_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>&& cmdList_forUpload_,
	ID3D12CommandQueue* commandQueue_,
	Synchronizer* synchronizer_

) :allocator(std::move(allocator_forUpload_)),commandList(std::move(cmdList_forUpload_)), commandQueue(commandQueue_), synchronizer(synchronizer_)
{

}

void CommandContext::ResourceUploader::Wait()
{
	HRESULT hr = commandList->Close();
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンド確定できない", fileName);

	ID3D12CommandList* commandLists[] = { commandList.Get()};
	commandQueue->ExecuteCommandLists(1, commandLists);

	synchronizer->WaitDirectly();
}

void CommandContext::ResourceUploader::RecordingStart()
{
	HRESULT hr = allocator->Reset();
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンドアロケーターのリセットに失敗", fileName);

	hr = commandList->Reset(allocator.Get(), nullptr);
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンドリストのリセットに失敗", fileName);

}


void CommandContext::ResourceUploader::Close(CommandContext::CloseKey key_)
{
	commandList->Close();
}
