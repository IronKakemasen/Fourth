#include "ResourceUploader.h"
#include "../Synchronizer/Synchronizer.h"


//外部
#include "../../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"

namespace
{
	auto fileName = "ResourceUploader.cpp";
}

CommandContext::ResourceUploader::ResourceUploader
(
	NexusFieldProof proof_,
	DeviceContextDiplomat* deviceContextDiplomat_,
	ID3D12CommandQueue* commandQueue_,
	CommandContext::Synchronizer* synchronizer_

) :commandQueue(commandQueue_), synchronizer(synchronizer_)
{

	auto* cmdExecutor = deviceContextDiplomat_->Access<DeviceContext::CommandExecutor>();
	
	//リソースアップロード用
	auto [allocator_forUpload, cmdList_forUpload] =
		cmdExecutor->CreateCommandContextCorePartsForUpload(proof_);

	allocator = std::move(allocator_forUpload);
	commandList = std::move(cmdList_forUpload);

	//最初開いてるから閉じておく
	commandList->Close();
	Logger::Log("Close: upload cmdList", fileName);

	///後続するリソースのアップロードのためにコマンドの記録を開始する
	RecordingStart();
	Logger::Log("Commmand recording start", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::ResourceUploader::KickAndSynchronize(const NexusFieldProof& nexusFieldProof_, AgentKey agentKey_)
{
	HRESULT hr = commandList->Close();
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンド確定できない", fileName);

	ID3D12CommandList* commandLists[] = { commandList.Get()};
	commandQueue->ExecuteCommandLists(1, commandLists);

	synchronizer->WaitDirectly();

	Logger::Log("Kicked ResourceUploadCommands", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandContext::ResourceUploader::RecordingStart()
{
	HRESULT hr = allocator->Reset();
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンドアロケーターのリセットに失敗", fileName);

	hr = commandList->Reset(allocator.Get(), nullptr);
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "コマンドリストのリセットに失敗", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandContext::ResourceUploader::UploadCommand CommandContext::ResourceUploader::ProvideUploadCommand(ProviderKey providerKey_)
{
	return[this]
	(
		ID3D12Resource* dstResource_,
		ID3D12Resource* intermediateResource_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	)
	{
		UpdateSubresources(commandList.Get(), dstResource_, intermediateResource_, 0, 0, subResourceCount_, subeResource_);
	};

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandContext::ResourceUploader::PitchBarrierCommand CommandContext::ResourceUploader::ProvideBarrierPitchCommand(ProviderKey providerKey_)
{
	return [this](const std::vector<D3D12_RESOURCE_BARRIER>& barriers_)
	{
		commandList->ResourceBarrier(UINT(barriers_.size()), barriers_.data());
	};

}
