#pragma once
#include "../../BufferAssembler.h"

class BufferContext::BufferAssembler::BufferMaterializer
{
	friend class BufferContext::BufferAssembler;

	template<typename BufferType>
	static [[nodiscard]] std::unique_ptr<BufferType> Materialize
	(
		ResourceContainer resourceContainer_,
		const BufferDescriptionBehavior& desc_,
		std::string nameCnv_
	);

};

template<>
static [[nodiscard]] std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
);

template<>
static [[nodiscard]] std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
);

template<>
static [[nodiscard]] std::unique_ptr<StaticStructuredBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
);

template<>
static [[nodiscard]] std::unique_ptr<UploadStructuredBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
);

template<>
static [[nodiscard]] std::unique_ptr<ComputeBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
);

template<>
static [[nodiscard]] std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::BufferMaterializer::Materialize
(
	ResourceContainer resourceContainer_,
	const BufferDescriptionBehavior& desc_,
	std::string nameCnv_
);
