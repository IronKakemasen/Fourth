#pragma once
#include "../../PSO_PoolDispatcher.h"


class RenderContext::PSO_PoolDispatcher::GraphicsPSO_Index
{
public:

    static constexpr uint32_t InvalidIndex = 0xffffffff;

private:

    static constexpr uint32_t InvalidKey = 0xffffffff;

    struct Slot
    {
        uint32_t packedKey = InvalidKey;
        uint32_t psoIndex = InvalidIndex;
    };

    inline uint32_t Hash(uint32_t packedkey_)const
    {
        packedkey_ ^= packedkey_ >> 16;
        packedkey_ *= 0x7feb352d;
        packedkey_ ^= packedkey_ >> 15;
        packedkey_ *= 0x846ca68b;
        packedkey_ ^= packedkey_ >> 16;

        return packedkey_;
    }

    inline uint32_t NextSlot(uint32_t curSlotIndex_) const 
    {
        //インデックスがオーバーしてる場合は巡回する
        return (curSlotIndex_ + 1) & mask;
    }

public:

    GraphicsPSO_Index();

    ///検索
    inline uint32_t FindIndex(uint32_t packedKey_) const
    {
        uint32_t index = Hash(packedKey_) & mask;

        while (true)
        {
            const Slot& entry = slots[index];

            if (entry.packedKey == InvalidKey)
            {
                ErrorMessageOutput::Assert::DetectError(entry.packedKey != InvalidKey, "無効な読み取りです", "PSO_Cache.h");
                return InvalidIndex;
            }

            //発見
            if (entry.packedKey == packedKey_)
            {
                return entry.psoIndex;
            }

            index = NextSlot(index);
        }
    }

    ///挿入
    void Insert(uint32_t packedKey_, uint32_t pipelineIndex);

private:

    uint32_t const kSizeOfSlots = 2048;
    std::vector<Slot> slots;
    uint32_t mask{};

    void Initialize();

};