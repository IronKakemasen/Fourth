#include "PreCompileHeader.h"
#include "BufferUploader.h"


#include "BufferUploaderTools/IntermediateResourceCreator/IntermediateResourceCreator.h"
#include "BufferUploaderTools/BarrierExtractor/BarrierExtractor.h"
#include "BufferUploaderTools/BufferAndResourcePicker/BufferAndResourcePicker.h"

//外部
#include "../../../../Core/Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../../../../Core/Command/CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProvider.h"

namespace
{
	auto const fileName = "BufferUploader.cpp";
}

BufferContext::BufferUploader::BufferUploader
(
	BufferContext::NexusFieldProof proof_,
	BufferContext::ResourceCreator* resourceCreator_,
	BufferContext::BufferDispatcher* dispatcher_,
	CommandContextDiplomat* commandContextDiplomat_
):resourceCreator(resourceCreator_), dispatcher(dispatcher_)
{
	//コマンドプロバイダーにアクセス
	auto* commandProvider = commandContextDiplomat_->Access<CommandContext::CommandProvider>();
	CommandContext::CommandProvider::PermissionType<CommandContext::ResourceUploader::UploadCommand> licence{};

	uploadCommand = commandProvider->Provide<CommandContext::ResourceUploader::UploadCommand>(licence);
	pitchBarriersCommand = commandProvider->Provide<CommandContext::ResourceUploader::PitchBarrierCommand>(licence);
}

BufferContext::BufferUploader::~BufferUploader()
{
	Logger::Log("BufferUploader Destructor Runs", fileName);
	Logger::Log("Delete: all intermediateResources(" + std::to_string((UINT)intermediateResources.size()) + ")", fileName);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ID3D12Resource* BufferContext::BufferUploader::CreateInterMediateResource(UINT const resourceSize_)
{
	return intermediateResources.emplace_back
	(IntermediateResourceCreator::CreateInterMediateResource(resourceCreator, resourceSize_)).Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::ExtractBarrier(GPUBufferBehavior* dstBuffer_)
{
	barriers.emplace_back(BarrierExtractor::ExtractBarrier(dstBuffer_));
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::tuple<GPUBufferBehavior*, ID3D12Resource*, std::string> BufferContext::BufferUploader::PickBufferAndResource(BufferUniqueID id_)
{
	return BufferAndResourcePicker::PickBufferAndResource(dispatcher, id_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::PitchAllBarrier(BufferContext::NexusFieldProof proof_, BufferContext::AgentKey agentKey_)
{
	pitchBarriersCommand(barriers);
	Logger::Log("Pitch All Barriers(" + std::to_string((UINT)barriers.size()) + ")", fileName);
}
