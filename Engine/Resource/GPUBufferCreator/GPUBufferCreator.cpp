#include "PreCompileHedder.h"
#include "GPUBufferCreator.h"
#include "../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"

#include "../GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../GPUBuffer/ColorBuffer/ColorBuffer.h"


//[[nodiscard]] std::unique_ptr<ConstantBuffer> GPUBufferCreator::CreateConstantBuffer(const ConstantBufferDescription& desc_ , const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_)
//{
//	Microsoft::WRL::ComPtr<ID3D12Resource> resource1 , resource2;
//
//	resource1 = createConstantBuffer(desc_);
//	resource2 = createConstantBuffer(desc_);
//
//	std::unique_ptr<ConstantBuffer> constantBuffer = std::make_unique<ConstantBuffer>(GPUBufferBehavior::InstanceKey{},
//		name_, std::move(resource1), std::move(resource2), desc_);
//
//	return std::move(constantBuffer);
//}
//
//[[nodiscard]] std::unique_ptr<ColorBuffer> GPUBufferCreator::CreateColorBuffer(const ColorBufferDescription& desc_, const std::string& name_)
//{
//	Microsoft::WRL::ComPtr<ID3D12Resource> resource1, resource2;
//
//	resource1 = createColorBuffer(desc_);
//	resource2 = createColorBuffer(desc_);
//
//	std::unique_ptr<ColorBuffer> colorBuffer = std::make_unique<ColorBuffer>(GPUBufferBehavior::InstanceKey{},
//		name_, std::move(resource1), std::move(resource2), desc_);
//
//	return std::move(colorBuffer);
//
//}



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


template <>
std::unique_ptr<ConstantBuffer> GPUBufferCreator::CallSpecificCreator<ConstantBuffer, ConstantBufferDescription>(const ConstantBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_)
{
	resource1_ = createConstantBuffer(desc_);
	resource2_ = createConstantBuffer(desc_);

	std::unique_ptr<ConstantBuffer> constantBuffer(new ConstantBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

	return std::move(constantBuffer);
}


template <>
std::unique_ptr<ColorBuffer> GPUBufferCreator::CallSpecificCreator<ColorBuffer, ColorBufferDescription>(const ColorBufferDescription& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_)
{
	resource1_ = createColorBuffer(desc_);
	resource2_ = createColorBuffer(desc_);

	std::unique_ptr<ColorBuffer> colorBuffer(new ColorBuffer(GPUBufferBehavior::InstanceKey{},
		name_, std::move(resource1_), std::move(resource2_), desc_));

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
