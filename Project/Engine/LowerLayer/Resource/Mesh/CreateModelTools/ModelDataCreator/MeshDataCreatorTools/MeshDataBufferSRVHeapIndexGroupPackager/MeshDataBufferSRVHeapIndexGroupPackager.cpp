#include "PreCompileHeader.h"
#include "MeshDataBufferSRVHeapIndexGroupPackager.h"

//外部
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/BufferInterface.h"
#include "../../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"


namespace
{
	auto const fileName = "MeshDataBufferSRVHeapIndexGroupPackager.cpp";
}

using namespace StructuredBufferDataDefinition;


void MeshContext::ModelDataCreator::MeshDataBufferSRVHeapIndexGroupPackager::PackMeshDataBufferSRVHeapIndex
(
	const std::vector<MeshDataBufferUniqueIDGroup>& uniqueIDGroupContainer_,
	std::vector<MeshDataSRVHeapIndexGroupGPUCPU>& tmpMeshDataSRVHeapIndexGroupContainer_,
	BufferContext::BufferDispatcher* dispatcher_
)
{

	size_t containerSize = uniqueIDGroupContainer_.size();

	auto GetSRVHeapIndexFunc = [dispatcher_](BufferUniqueID id_)
	{
		auto* bufferBehav = dispatcher_->Dispatch(id_);
		auto* readableBuffer = dynamic_cast<IReadable*>(bufferBehav);
		ErrorMessageOutput::Assert::DetectError(readableBuffer, "リーダブルじゃない", fileName);

		return readableBuffer->OutProperSRVHeapIndex();
	};

	for (size_t i = 0;i< containerSize;++i)
	{
		MeshDataSRVHeapIndexGroupGPUCPU srvHeapIndexGroup;

		srvHeapIndexGroup.vertices =			GetSRVHeapIndexFunc(uniqueIDGroupContainer_[i].verticesGPU);
		srvHeapIndexGroup.uniqueVertexIndices = GetSRVHeapIndexFunc(uniqueIDGroupContainer_[i].uniqueVertsIndices);
		srvHeapIndexGroup.meshlets =			GetSRVHeapIndexFunc(uniqueIDGroupContainer_[i].meshlets);
		srvHeapIndexGroup.primitiveIndices =	GetSRVHeapIndexFunc(uniqueIDGroupContainer_[i].primIndices);

		tmpMeshDataSRVHeapIndexGroupContainer_.emplace_back(srvHeapIndexGroup);
	}
}
