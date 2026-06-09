#include "PreCompileHedder.h"
#include "GPUBufferCreator.h"
#include "../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"

#include "../GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../GPUBuffer/ColorBuffer/ColorBuffer.h"

namespace
{
	const std::string fileName = "GPUBufferCreator.cpp";
}

void GPUBufferCreator::SetCommands(const CrateColorBufferCommand& crateColorBufferCommand_, const CrateConstantBufferCommand& crateConstantBufferCommand_)
{
	crateConstantBufferCommand = crateConstantBufferCommand_;
	Logger::Log("Set: crateConstantBufferCommand", fileName);
	crateColorBufferCommand = crateColorBufferCommand_;
	Logger::Log("Set: crateColorBufferCommand", fileName);

}

template <>
std::unique_ptr<ConstantBuffer> GPUBufferCreator::CreateSpecificBuffer<ConstantBuffer, ConstantBufferDescription>(const ConstantBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource1_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource2_)
{
	resource1_ = crateConstantBufferCommand(desc_);
	resource2_ = crateConstantBufferCommand(desc_);

	std::unique_ptr<ConstantBuffer> constantBuffer(new ConstantBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

	Logger::Log("Create: name_", fileName);

	return std::move(constantBuffer);
}


template <>
std::unique_ptr<ColorBuffer> GPUBufferCreator::CreateSpecificBuffer<ColorBuffer, ColorBufferDescription>(const ColorBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource1_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource2_)
{
	resource1_ = crateColorBufferCommand(desc_);
	resource2_ = crateColorBufferCommand(desc_);

	std::unique_ptr<ColorBuffer> colorBuffer(new ColorBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

	Logger::Log("Create: name_", fileName);

	return std::move(colorBuffer);
}

template <>
std::string GPUBufferCreator::NameConverter<ConstantBuffer>(const std::string& name_)
{
	return "ConstantBuffer [ " + name_ + " ] ";
}

template <>
std::string GPUBufferCreator::NameConverter<ColorBuffer>(const std::string& name_)
{
	return "ColorBuffer [ " + name_ + " ] ";
}


void GPUBufferCreator::CheckDescription(const BufferDescriptionBehavior& srcDesc_)
{
	srcDesc_.CheckRequirementsFilled();
}

GPUBufferCreator::GPUBufferCreator(GPUBufferCreator::InstanceKey instanceKey_)
{

}

GPUBufferCreator::~GPUBufferCreator()
{

}

void GPUBufferCreator::Log(std::string convName_)
{
	Logger::Log("CreateBuffer :" + convName_);
}
