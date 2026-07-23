#include "PreCompileHeader.h"
#include "BufferMaterializer.h"
#include "../../../../BufferDefinition/AllBuffersInclude.h"



template<>
static [[nodiscard]] std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
)
{
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
	//バッファ生成
	return std::make_unique<ConstantBuffer>
	(
		ConstantBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		desc_
	);

}
