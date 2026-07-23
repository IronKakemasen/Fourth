#pragma once
#include "../../BufferAssembler.h"

class BufferContext::BufferAssembler::BufferNameConverter
{
    friend class BufferContext::BufferAssembler;

    //名前変換
    template<typename BufferType>
    static inline std::string ConvertName(const std::string& srcName_)
    {
        std::string attach;

        if constexpr (std::is_same_v<BufferType, ConstantBuffer>)               attach = "Constant";
        else if constexpr (std::is_same_v<BufferType, ColorBuffer>)             attach = "Color";
        else if constexpr (std::is_same_v<BufferType, DepthStencilBuffer>)      attach = "DepthStencil";
        else if constexpr (std::is_same_v<BufferType, ComputeBuffer>)           attach = "Compute";
        else if constexpr (std::is_same_v<BufferType, UploadStructuredBuffer>)  attach = "UploadStructured";
        else if constexpr (std::is_same_v<BufferType, StaticStructuredBuffer>)  attach = "StaticStructuredBuffer";

        return attach + "Buffer" + "[ " + srcName_ + " ] ";
    }


};

