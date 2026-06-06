#include "PreCompileHedder.h"
#include "DeviceContextCommandGenerator.h"

#include "../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"
#include "../Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"

DeviceContext::CommandGenerator::CommandGenerator(DeviceContext::InstanceKey instanceKey_)
{


}

//[[nodiscard]] std::unique_ptr<DeviceContextCommandBehavior> DeviceContext::CommandGenerator::CreateCommand(
//	DeviceContext::InstanceKey instanceKey_, DeviceContext::CommandType type_)
//{
//	auto generateKey = CommandGenerator::GenerateKey{};
//	std::unique_ptr<DeviceContextCommandBehavior> ret;
//
//	switch (type_)
//	{
//	case DeviceContext::kCreatingGPU_Buffer:
//
//		ret = std::make_unique<CreatingGPUBuffer>(generateKey);
//
//		break;
//
//	case DeviceContext::kCreateDescriptorHeap:
//
//		ret = std::make_unique<CommandCreateDescriptorHeap>(generateKey);
//
//		break;
//
//	}
//
//	return std::move(ret);
//}

DeviceContext::CommandGenerator::~CommandGenerator()
{

}


