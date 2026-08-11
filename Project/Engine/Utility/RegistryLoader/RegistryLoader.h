#pragma once

class RegistryLoader
{
public:

    enum class RegistryFileType
    {
        kMSFiles,
        kPSFiles,
        kCSFiles,
        kModelFiles,
        kJsonFiles



        , kCount
    };

private:

    template<RegistryFileType fileType>
    static std::string FilePathtable()
    {
        static std::string const commonTo = "Assets/Registry/";
        static std::string const commonFormat = ".txt";

        static const std::string pathTable[(UINT)RegistryFileType::kCount]
        {
            "MSFiles",
            "PSFiles",
            "CSFiles",
            "ModelFiles",
            "JsonFiles"
        };

        return commonTo + pathTable[(UINT)fileType] + commonFormat;
    }

public:
    
    ///キーとバリューを取得
    template<RegistryFileType fileType>
    static std::unordered_map<std::string, std::string > Load()
    {
        std::string const registryFilePath = FilePathtable<fileType>();

        std::unordered_map<std::string, std::string > modelFileName_pathLib;
        std::ifstream file(registryFilePath);

        ErrorMessageOutput::Abort::DetectError
        (
            file.is_open(),
            registryFilePath + "このパス無くない？",
            "ModelRegistryLoader.h"
        );

        std::string line;

        while (std::getline(file, line))
        {
            constexpr std::string_view keyToken = "key: \"";
            constexpr std::string_view valueToken = "value: \"";

            auto keyStart = line.find(keyToken);
            if (keyStart == std::string::npos)
            {
                continue;
            }


            keyStart += keyToken.size();

            auto keyEnd = line.find("\"", keyStart);
            if (keyEnd == std::string::npos)
            {
                continue;
            }


            std::string key = line.substr
            (
                keyStart,
                keyEnd - keyStart
            );


            auto valueStart = line.find(valueToken);
            if (valueStart == std::string::npos)
            {
                continue;
            }

            valueStart += valueToken.size();

            auto valueEnd = line.find("\"", valueStart);
            if (valueEnd == std::string::npos)
            {
                continue;
            }

            std::string value = line.substr
            (
                valueStart,
                valueEnd - valueStart
            );

            modelFileName_pathLib.emplace(key, value);
        }

        Logger::Log("Load: " + registryFilePath, "RegistryLoader.h");
        return modelFileName_pathLib;
    }

    ///キーのみ取得
    template<RegistryFileType fileType>
    static std::vector<std::string> LoadRegistryKeys()
    {
        std::string const registryFilePath = FilePathtable<fileType>();

        std::vector<std::string> keys;
        std::ifstream file(registryFilePath);

        ErrorMessageOutput::Abort::DetectError
        (
            file.is_open(),
            registryFilePath + "このパス無くない？",
            "ModelRegistryLoader.h"
        );

        std::string line;

        while (std::getline(file, line))
        {
            constexpr std::string_view keyToken = "key: \"";

            auto keyStart = line.find(keyToken);
            if (keyStart == std::string::npos)
            {
                continue;
            }

            keyStart += keyToken.size();

            auto keyEnd = line.find("\"", keyStart);
            if (keyEnd == std::string::npos)
            {
                continue;
            }

            std::string key = line.substr
            (
                keyStart,
                keyEnd - keyStart
            );


            keys.emplace_back(key);
        }

        return keys;
    }

};



