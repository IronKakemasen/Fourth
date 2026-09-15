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
        kJsonFiles,
        kTextureFiles

        , kCount
    };

    template<RegistryFileType type>
    struct RegistryFileTypeTraits;

private:

    //レジストリーファイルのテーブル
    template<RegistryFileType fileType>
    static std::string FilePathtable()
    {
        return RegistryFileTypeTraits<fileType>::kFilePath;
    }

public:
    
    ///キーとバリューを取得
    template<RegistryFileType fileType>
    static std::unordered_map<std::string, std::string > Load()
    {
        std::string const registryFilePath = FilePathtable<fileType>();

        std::unordered_map<std::string, std::string > keyToPath;
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

            keyToPath.emplace(key, value);
        }

        Logger::Log("Load: " + registryFilePath , "RegistryLoader.h\n");
        return keyToPath;
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

    //バリューからキーを検索
    template<RegistryFileType fileType>
    static std::string ValueToKey(std::string const value_)
    {

        std::string filekKey;

        //レジストリファイルを読み込む
        std::unordered_map<std::string, std::string> const keyToPath = Load<fileType>();

        // キーとバリューを検索
        for (auto const& [key, value] : keyToPath)
        {
            if (value == value_)
            {
                filekKey = key;
                break;
            }
        }

        return filekKey;
    }

};


template<>
struct RegistryLoader::RegistryFileTypeTraits<RegistryLoader::RegistryFileType::kJsonFiles>
{
    static inline std::string const kFilePath = "Assets/Registry/JsonFiles.txt";
};

template<>
struct RegistryLoader::RegistryFileTypeTraits<RegistryLoader::RegistryFileType::kMSFiles>
{
    static inline std::string const kFilePath = "Assets/Registry/MSFiles.txt";
};

template<>
struct RegistryLoader::RegistryFileTypeTraits<RegistryLoader::RegistryFileType::kPSFiles>
{
    static inline std::string const kFilePath = "Assets/Registry/PSFiles.txt";
};

template<>
struct RegistryLoader::RegistryFileTypeTraits<RegistryLoader::RegistryFileType::kCSFiles>
{
    static inline std::string const kFilePath = "Assets/Registry/CSFiles.txt";
};

template<>
struct RegistryLoader::RegistryFileTypeTraits<RegistryLoader::RegistryFileType::kModelFiles>
{
    static inline std::string const kFilePath = "Assets/Registry/ModelFiles.txt";
};

template<>
struct RegistryLoader::RegistryFileTypeTraits<RegistryLoader::RegistryFileType::kTextureFiles>
{
    static inline std::string const kFilePath = "Assets/Registry/TextureFiles.txt";
};


