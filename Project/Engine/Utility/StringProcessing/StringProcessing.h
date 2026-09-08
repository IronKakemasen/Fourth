#pragma once

namespace StringProcessing
{
    std::string SkipFetch(std::string const dstString_ , char const signalChar_)
    {
        auto pos = dstString_.find(signalChar_);

        ErrorMessageOutput::Assert::DetectError
        (
            pos != std::string::npos,
            dstString_ + "の中に" + signalChar_ + "という文字なくね？",
            "StringProcessing.h"
        );

        //シグナルの文字から隣の文字を返す
        return dstString_.substr(pos + 1);
    }

}

