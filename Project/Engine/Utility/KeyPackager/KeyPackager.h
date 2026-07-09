#pragma once

class KeyPackager
{
private:

    struct BitAndLocation
    {
        uint32_t shift{};

        inline void Init(uint32_t count_, uint32_t shift_)
        {
            //必要ビット数を計算
            CalcBitWidth(count_);
            //スタート地点を記録
            CalcShiftNum(shift_);

            ErrorMessageOutput::Assert::DetectError((EndLocation() <= 32), "GraphicsPSO_Keyのサイズ超過", "GraphicsPSO_KeyPackager.h");
        }

        uint32_t EndLocation() { return shift + bits; }

    private:

        uint32_t bits{};

        inline void CalcBitWidth(uint32_t count_) { bits = count_ <= 1 ? 1 : std::bit_width(count_ - 1); }
        inline void CalcShiftNum(uint32_t shift_) { shift = shift_; }
    };

    std::vector<BitAndLocation> bitAndLocationContainer;

public:

    ///シーケンス注意
    //それぞれのキーのサイズやパッキング位置を設定する
    template<typename... Keys>
    KeyPackager(Keys... sizeOfKeys_)
    {
        uint8_t length = sizeof...(sizeOfKeys_);
        uint32_t arr[] = { uint32_t(sizeOfKeys_)... };

        bitAndLocationContainer.resize(length);

        bitAndLocationContainer.at(0).Init(arr[0], 0);

        for (int i = 1;i < length;++i)
        {
            bitAndLocationContainer.at(i).Init(arr[i], bitAndLocationContainer.at(i - 1).EndLocation());
        }

    }

    ///キー生成
    template<typename... Keys>
    [[nodiscard]] uint32_t Pack(Keys... keys_)
    {
        auto const sizeContainer = bitAndLocationContainer.size();
        auto const keysLength = sizeof...(keys_);
        uint32_t keyArr[] = { uint32_t(keys_)... };

        ErrorMessageOutput::Assert::DetectError
        (
            sizeContainer == keysLength,
            "初期設定のキーの設定数と、入力数が合わない",
            ""
        );

        uint32_t packedKey{};
        for (size_t i = 0;i < sizeContainer;++i)
        {
            packedKey |= uint32_t(keyArr[i] << bitAndLocationContainer.at(i).shift);
        }

        return packedKey;
    }


};