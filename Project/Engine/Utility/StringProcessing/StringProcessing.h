#pragma once

namespace StringProcessing
{
	///文字列の中の特定の文字の後ろの文字列を返す
    inline std::string SkipFetch(std::string const& dstString_ , char const signalChar_)
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

	///引数のファイル指定子かどうかをチェック
    inline bool CheckFileExtension(std::string const& path_, std::string const& extension_)
	{
        ErrorMessageOutput::Assert::DetectError
        (
            path_.size() > extension_.size(),
            path_ + "のファイル指定子に" + extension_ + "なくね？",
            "StringProcessing.h"
        );

        size_t const extensionStart = path_.size() - extension_.size();

		std::string extension = path_.substr(extensionStart);

		return extension == extension_;
	}

    ///ファイル指定子を消す
    static std::string RemoveFileExtension(std::string const& path_)
    {
        std::size_t const dotPos = path_.find_last_of('.');

        if (dotPos == std::string::npos)
        {
            return path_;
        }

        return path_.substr(0, dotPos);
    }

    ///けつからn番目の文字をカットする
    inline std::string Cut(std::string const dstString_, size_t const removeStartPos_)
    {
        auto const stringEndPos = dstString_.size() - removeStartPos_;

        return dstString_.substr(0, stringEndPos);
    }

}

