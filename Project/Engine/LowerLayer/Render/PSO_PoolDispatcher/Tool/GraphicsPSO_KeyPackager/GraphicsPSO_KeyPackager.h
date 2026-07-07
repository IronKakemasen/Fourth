#pragma once
#include "../../PSO_PoolDispatcher.h"


struct RenderContext::PSO_PoolDispatcher::GraphicsPSO_KeyPackager
{
private:


    ///以下BL(ふざけてるわけではない)
    struct BitAndLocation
    {
        uint32_t shift{};

        inline void Init(uint32_t count_, uint32_t shift_)
        {
            //必要ビット数を計算
            CalcBitWidth(count_);
            //スタート地点を記録
            CalcShitNum(shift_);

            ErrorMessageOutput::Assert::DetectError((EndLocation() <= 32), "GraphicsPSO_Keyのサイズ超過", "GraphicsPSO_KeyPackager.h");
        }

        uint32_t EndLocation() { return shift + bits; }

    private:

        uint32_t bits{};

        inline void CalcBitWidth(uint32_t count_) { bits = count_ <= 1 ? 1 : std::bit_width(count_ - 1); }
        inline void CalcShitNum(uint32_t shift_) { shift = shift_; }
    };

    static inline BitAndLocation renderPassBL;
    static inline BitAndLocation depthEnableBL;
    static inline BitAndLocation depthTestBL;
    static inline BitAndLocation meshTypeBL;
    static inline BitAndLocation materialTypeBL;
    static inline BitAndLocation blendModeBL;
    static inline BitAndLocation fillModeBL;
    static inline BitAndLocation cullModeBL;

public:

    GraphicsPSO_KeyPackager();

    [[nodiscard]] static inline uint32_t CreateKey(GraphicsPSO_Key key_)
    {
        uint32_t packedKey =
              (uint32_t(key_.pass)          << renderPassBL.shift)
            | (uint32_t(key_.mesh)          << meshTypeBL.shift)
            | (uint32_t(key_.material)      << materialTypeBL.shift)
            | (uint32_t(key_.blend)         << blendModeBL.shift)
            | (uint32_t(key_.fill)          << fillModeBL.shift)
            | (uint32_t(key_.cull)          << cullModeBL.shift)
            | (uint32_t(key_.depthEnable)   << depthEnableBL.shift)
            | (uint32_t(key_.depthTest)     << depthTestBL.shift);

        return packedKey;
    }

};