#include "PreCompileHeader.h"
#include "GraphicsPSO_Index.h"


namespace
{
    auto const fileName = "GraphicsPSO_Index.cpp";
}


RenderContext::PSO_PoolDispatcher::GraphicsPSO_Index::GraphicsPSO_Index()
{
    Initialize();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PSO_PoolDispatcher::GraphicsPSO_Index::Initialize()
{
    ErrorMessageOutput::Assert::DetectError(kSizeOfSlots >= 2, "kSizeOfSlots < 2", fileName);
    ErrorMessageOutput::Assert::DetectError
    (
        (kSizeOfSlots & (kSizeOfSlots - 1)) == 0, 
        "マスクの値が不適切になってしまう", 
        fileName
    );

    mask = kSizeOfSlots - 1;
    slots.resize(kSizeOfSlots);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderContext::PSO_PoolDispatcher::GraphicsPSO_Index::Insert(uint32_t packedKey_, uint32_t pipelineIndex)
{
    uint32_t index = Hash(packedKey_) & mask;

    uint32_t loopNum{};

    while (true)
    {
        Slot& slot = slots[index];

        //空席であれば
        if (slot.packedKey == InvalidKey)
        {
            slot.packedKey = packedKey_;
            slot.psoIndex = pipelineIndex;
            return;
        }

        //書き換え
        if (slot.packedKey == packedKey_)
        {
            slot.psoIndex = pipelineIndex;
            return;
        }

        //次の席へ
        index = NextSlot(index);

        //無限ループ制限
        ErrorMessageOutput::Assert::DetectError
        (
            (++loopNum < kSizeOfSlots),
            "スロットオーバーです",
            fileName
        );
    }
}
