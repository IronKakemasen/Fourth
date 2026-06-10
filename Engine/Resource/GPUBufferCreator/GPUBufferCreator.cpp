#include "PreCompileHedder.h"
#include "GPUBufferCreator.h"

#include "../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"
#include "../BufferDescriptions/SRV_UAVBufferDescription/SRV_UAVBufferDescription.h"

#include "../GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../GPUBuffer/SRV_UAVBuffer/SRV_UAVBuffer.h"

namespace
{
	const std::string fileName = "GPUBufferCreator.cpp";
}

void GPUBufferCreator::SetCommands
(
	const CreateColorBufferCommand& createColorBufferCommand_,
	const CreateConstantBufferCommand& createConstantBufferCommand_,
	const CreateSRV_UAVBufferCommand& createSRV_UAVBufferCommand_
)
{
	createConstantBufferCommand = createConstantBufferCommand_;
	Logger::Log("Set: crateConstantBufferCommand", fileName);
	createColorBufferCommand = createColorBufferCommand_;
	Logger::Log("Set: crateColorBufferCommand", fileName);
	createSRV_UAVBufferCommand = createSRV_UAVBufferCommand_;
	Logger::Log("Set: createSRV_UAVBufferCommand_", fileName);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
std::unique_ptr<ConstantBuffer> GPUBufferCreator::CreateSpecificBuffer<ConstantBuffer, ConstantBufferDescription>(const ConstantBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource1_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource2_)
{
	resource1_ = createConstantBufferCommand(desc_);
	resource2_ = createConstantBufferCommand(desc_);

	std::unique_ptr<ConstantBuffer> constantBuffer(new ConstantBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

	Logger::Log("Create: name_", fileName);

	return std::move(constantBuffer);
}


template <>
std::unique_ptr<ColorBuffer> GPUBufferCreator::CreateSpecificBuffer<ColorBuffer, ColorBufferDescription>(const ColorBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource1_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource2_)
{
	resource1_ = createColorBufferCommand(desc_);
	resource2_ = createColorBufferCommand(desc_);

	std::unique_ptr<ColorBuffer> colorBuffer(new ColorBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

	Logger::Log("Create: name_", fileName);

	return std::move(colorBuffer);
}

template <>
std::unique_ptr<SRV_UAVBuffer> GPUBufferCreator::CreateSpecificBuffer<SRV_UAVBuffer, SRV_UAVBufferDescription>(const SRV_UAVBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource1_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource2_)
{
	resource1_ = createSRV_UAVBufferCommand(desc_);
	resource2_ = createSRV_UAVBufferCommand(desc_);

	std::unique_ptr<SRV_UAVBuffer> srv_uavBuffer(new SRV_UAVBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

	Logger::Log("Create: name_", fileName);

	return std::move(srv_uavBuffer);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

template <>
std::string GPUBufferCreator::NameConverter<SRV_UAVBuffer>(const std::string& name_)
{
	return "SRV_UAVBuffer [ " + name_ + " ] ";
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GPUBufferCreator::Log(std::string convName_)
{
	Logger::Log("CreateBuffer :" + convName_);
}

void GPUBufferCreator::CheckDescription(const BufferDescriptionBehavior& srcDesc_)
{
	srcDesc_.CheckRequirementsFilled();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
GPUBufferCreator::GPUBufferCreator(GPUBufferCreator::InstanceKey instanceKey_)
{

}

GPUBufferCreator::~GPUBufferCreator()
{

}

