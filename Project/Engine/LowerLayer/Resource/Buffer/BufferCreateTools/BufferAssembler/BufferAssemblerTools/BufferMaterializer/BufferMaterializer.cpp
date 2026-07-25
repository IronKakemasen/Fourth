#include "PreCompileHeader.h"
#include "BufferMaterializer.h"
#include "../../../../BufferDefinition/AllBuffersInclude.h"

namespace
{
	auto const fileName = "BufferMaterializer.cpp";
}

template<>
static [[nodiscard]] std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{

	Logger::Log("BufferType: ColorBuffer", fileName);

	//バッファ生成
	return std::make_unique<ColorBuffer>
	(
		ColorBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		desc_
	);

}

template<>
static [[nodiscard]] std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{
	Logger::Log("BufferType: DepthStencilBuffer", fileName);

	//バッファ生成
	return std::make_unique<DepthStencilBuffer>
	(
		DepthStencilBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		desc_
	);

}

template<>
static [[nodiscard]] std::unique_ptr<StaticStructuredBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{
	Logger::Log("BufferType: StaticStructuredBuffer", fileName);

	//バッファ生成
	return std::make_unique<StaticStructuredBuffer>
	(
		StaticStructuredBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		desc_
	);

}

template<>
static [[nodiscard]] std::unique_ptr<UploadStructuredBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{

	Logger::Log("BufferType: UploadStructuredBuffer", fileName);

	//バッファ生成
	return std::make_unique<UploadStructuredBuffer>
		(
			UploadStructuredBuffer::InstanceKey{},
			nameCnv_,
			std::move(resourceContainer_),
			desc_
		);

}

template<>
static [[nodiscard]] std::unique_ptr<ComputeBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{

	Logger::Log("BufferType: ComputeBuffer", fileName);

	//バッファ生成
	return std::make_unique<ComputeBuffer>
		(
			ComputeBuffer::InstanceKey{},
			nameCnv_,
			std::move(resourceContainer_),
			desc_
		);

}

template<>
static [[nodiscard]] std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{

	Logger::Log("BufferType: ConstantBuffer", fileName);

	//バッファ生成
	return std::make_unique<ConstantBuffer>
	(
		ConstantBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		desc_
	);

}
