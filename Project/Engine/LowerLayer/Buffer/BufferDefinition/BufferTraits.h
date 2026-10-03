#pragma once
#include "AllBuffersFwd.h"


namespace BufferTraits
{
	//登録先識別用(CollectorとDispatcherが主に使う)
	enum class RegisterType
	{
		kRenderTarget,
		kFrameBuffer,
		kComputeBuffer,
		kReadOnlyBuffer,
		kCount
	};


	//バッファタグ。使うことはあんまりないと思うが
	enum class BufferTag
	{
		kColor,
		kDepthStencil,
		kConstant,
		kCompute,
		kUploadStructured,
		kStaticStructured,
		kTexture2D,
		
		kCount
	};

	template<BufferTag tag>
	struct TagTraits;

	template<typename BufferType>
	struct ClassTraits;



	template<>
	struct TagTraits<BufferTag::kColor>
	{
		using classType = ColorBuffer;
	};

	template<>
	struct TagTraits<BufferTag::kConstant>
	{
		using classType = ConstantBuffer;
	};

	template<>
	struct TagTraits<BufferTag::kDepthStencil>
	{
		using classType = DepthStencilBuffer;
	};

	template<>
	struct TagTraits<BufferTag::kCompute>
	{
		using classType = ComputeBuffer;
	};

	template<>
	struct TagTraits<BufferTag::kUploadStructured>
	{
		using classType = UploadStructuredBuffer;
	};

	template<>
	struct TagTraits<BufferTag::kStaticStructured>
	{
		using classType = StaticStructuredBuffer;
	};

	template<>
	struct TagTraits<BufferTag::kTexture2D>
	{
		using classType = Texture2DBuffer;
	};



	template<>
	struct ClassTraits<ColorBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kColor;
	};

	template<>
	struct ClassTraits<ConstantBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kConstant;
	};

	template<>
	struct ClassTraits<DepthStencilBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kDepthStencil;
	};

	template<>
	struct ClassTraits<ComputeBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kCompute;
	};

	template<>
	struct ClassTraits<UploadStructuredBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kUploadStructured;
	};

	template<>
	struct ClassTraits<StaticStructuredBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kStaticStructured;
	};

	template<>
	struct ClassTraits<Texture2DBuffer>
	{
		static constexpr BufferTag kTag = BufferTag::kTexture2D;
	};

	
}