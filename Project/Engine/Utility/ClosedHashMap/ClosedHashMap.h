#pragma once


//オープンアドレッシング・ハッシュテーブル法で、高速にValueType検索するためのツール
template<typename ValueType>
class ClosedHashMap
{

private:

    static constexpr uint32_t InvalidKey = 0xffffffff;

    struct Slot
    {
        enum Status
        {
            kEmpty,
            kOccupied
        }status = kEmpty;

        uint32_t key = InvalidKey;
        ValueType value;
    };

    inline uint32_t Hash(uint32_t key_)const
    {
        key_ ^= key_ >> 16;
        key_ *= 0x7feb352d;
        key_ ^= key_ >> 15;
        key_ *= 0x846ca68b;
        key_ ^= key_ >> 16;

        return key_;
    }

    inline uint32_t NextSlot(uint32_t curSlotIndex_) const
    {
        //インデックスがオーバーしてる場合は巡回する
        return (curSlotIndex_ + 1) & mask;
    }

public:

    ClosedHashMap(uint32_t slotSize_)
        :kSizeOfSlots(slotSize_)
    {
        ErrorMessageOutput::Assert::DetectError(kSizeOfSlots >= 2, "kSizeOfSlots < 2", "ClosedHashMap.h");
        ErrorMessageOutput::Assert::DetectError
        (
            (kSizeOfSlots & (kSizeOfSlots - 1)) == 0,
            "マスクの値が不適切になってしまう",
            "ClosedHashMap.h"
        );

        mask = kSizeOfSlots - 1;
        slots.resize(kSizeOfSlots);
    }

    ///検索。登録してあるものは間違い無い前提。
    inline ValueType FindValueFast(uint32_t key_) const
    {
        uint32_t index = Hash(key_) & mask;
        ValueType value;

        uint32_t loopNum{};
        while (true)
        {
            const Slot& slot = slots[index];

            //発見
            if (slot.key == key_)
            {
                value = slot.value;
                break;
            }

            //スロットが空の場合は見つからなかった証拠
            ErrorMessageOutput::Assert::DetectError
            (
                (slot.status == Slot::kOccupied),
                "データがないです",
                "ClosedHashMap.h"
            );


            //無限ループ制限
            ErrorMessageOutput::Assert::DetectError
            (
                (++loopNum < kSizeOfSlots),
                "スロットオーバーです",
                "ClosedHashMap.h"
            );

            index = NextSlot(index);
        }

        return value;
    }

    ///挿入
    ///先にCheckDuplicationで空きスロットを探してください
    void Insert(uint32_t dstFreeSlotIndex_, uint32_t key_,ValueType value_)
    {
        //CheckDuplication()で空きスロットのインデックスは特定されているのでそこに入れる
        Slot& slot = slots[dstFreeSlotIndex_];
        slot.key = key_;
        slot.value = value_;
        slot.status = Slot::kOccupied;
    }

    ///入力されたキーが過去に生成しているものとかぶったかどうかチェックし、
    ///存在していたらそのValueを返し、
    ///なければ挿入すべき場所のindexを返す
    [[nodiscard]] std::pair<std::optional<ValueType>, std::optional<uint32_t>> CheckDuplication(uint32_t key_)
    {
        std::pair<std::optional<ValueType>, std::optional<uint32_t>> value_index = { std::nullopt, std::nullopt };

        uint32_t index = Hash(key_) & mask;

        uint32_t loopNum{};
        while (true)
        {
            const Slot& slot = slots[index];

            //発見
            if (slot.key == key_ )
            {
                value_index.first = slot.value;
                break;
            }

            //スロットが空の場合は見つからなかった証拠
            if (slot.status == Slot::kEmpty)
            {
                value_index.second = index;
                break;
            }

            //次へ
            index = NextSlot(index);

            //無限ループ制限
            ErrorMessageOutput::Assert::DetectError
            (
                (++loopNum < kSizeOfSlots),
                "スロットオーバーです",
                "ClosedHashMap.h"
            );
        }

        return value_index;
    }


private:

    uint32_t kSizeOfSlots{};
    std::vector<Slot> slots;
    uint32_t mask{};

};