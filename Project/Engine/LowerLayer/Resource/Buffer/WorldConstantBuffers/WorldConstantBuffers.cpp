#include "PreCompileHeader.h"
#include "WorldConstantBuffers.h"

namespace
{
	auto const fileName = "WorldConstantBuffers.cpp";
}


BufferContext::WorldConstantBuffers::WorldConstantBuffers
(
	NexusFieldProof proof_
)
{

}

void BufferContext::WorldConstantBuffers::PackRuntimeContainer(NexusFieldProof proof_, AgentKey agentKey_)
{
	//デバッグ用
	uint8_t slotCnt{};

	//昇順は担保されてるはずだからそのまま詰めてく
	for (auto [key, value] : gpuVirtualAddressMap)
	{
		ErrorMessageOutput::Assert::DetectError(slotCnt++ == key, "定数バッファのスロット設定おかしくね？", fileName);

		gpuVirtualAddressVector[0].emplace_back(value[0]);
		gpuVirtualAddressVector[1].emplace_back(value[1]);
	}

	Logger::Log("=====Number Of cBuffer Slots: " + std::to_string(slotCnt) + "=====",fileName);
	for (auto [key, value] : bufferNameMap)
	{
		Logger::Log("Slot[" + std::to_string(key) + "]: " + value);
	}

	gpuVirtualAddressMap.clear();
}


void BufferContext::WorldConstantBuffers::Import
(
	Local_ImportLicence licence_,
	std::string const bufferName_,
	const uint8_t bindSlot_,
	DoubleVirtualGPUAddress doubleVirtualGPUAddress_
) 
{
	ErrorMessageOutput::Assert::DetectError
	(
		gpuVirtualAddressMap.find(bindSlot_) == gpuVirtualAddressMap.end(),
		"この定数バッファのスロットは使われているよ",
		fileName
	);

	bufferNameMap[bindSlot_] = bufferName_;
	gpuVirtualAddressMap[bindSlot_] = doubleVirtualGPUAddress_;
}