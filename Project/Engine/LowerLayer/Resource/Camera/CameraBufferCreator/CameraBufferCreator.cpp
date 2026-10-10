#include "PreCompileHeader.h"
#include "CameraBufferCreator.h"
#include "../CameraContextRuntime/CameraDataBatcher/CameraDataBatcher.h"
#include "../CameraContextRuntime/CameraSocket.h"


//外部
#include "../../../Buffer/BufferDefinition/BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"
#include "../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include "../../../Buffer/BufferContextDiplomats.h"
#include "../../../Buffer/BufferContextToolsInclude.h"

#include "../../../../../Assets/Shared/StructuredBufferCameraData.h"
#include "../../../../../Assets/Shared/ConstantBuffers.h"

using namespace StructuredBufferCameraData;
using namespace ConstantBuffers;
namespace
{
	auto const fileName = "CameraBufferCreator.cpp";
}

void CameraContext::CameraBufferCreator::Create
(
	NexusFieldProof proof_,
	CameraDataBatcher& cameraDataBatcher_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//bufferCreatorを借りる
	auto& toolLender = *bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licence{};
	auto& bufferCreator = *toolLender.Lend<BufferContext::BufferCreator>(licence);


	//定数バッファ作成コマンドをもらう
	auto& cmdProvider = *bufferContextDiplomat_.Access<BufferContext::CmdProvider>();
	BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licence2{};
	auto globalCBufferCreateCmd = cmdProvider.Provide<BufferContextCmds::CreateCBufferCmd>(licence2);


	//bufferCreatorでカメラデータ配列のデータを作成する
	UploadStructuredBufferDescription desc((UINT)sizeof(CameraDataCPUGPU), (UINT)CameraSocket::kCount, 0);
	auto structuredID_buffer = bufferCreator.CreateWithBuffer(desc, "CameraDataArr");
	//ランタイムのため、IDは頂戴する
	cameraDataBatcher_.ImportCameraDataArrBufferID(proof_, structuredID_buffer.first);

	//そのsrvHeapIndexを格納するための定数バッファを作成
	auto constantID_buffer = globalCBufferCreateCmd("CameraDataArrSrv", (UINT)sizeof(SRVHeapIndex), (UINT)ConstantBufferBindSlots::kCameraContainer);
	constantID_buffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ 
			structuredID_buffer.second->OutProperSRVHeapIndex(0),
			structuredID_buffer.second->OutProperSRVHeapIndex(1)
		}
	);

	Logger::Log("Create CameraDataArr Buffer and its srvIndexBuffer", fileName);

}


