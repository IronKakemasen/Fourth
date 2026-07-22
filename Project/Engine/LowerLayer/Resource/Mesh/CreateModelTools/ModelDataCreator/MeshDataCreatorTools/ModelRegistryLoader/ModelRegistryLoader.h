#pragma once
#include "../../ModelDataCreator.h"

class MeshContext::ModelDataCreator::ModelRegistryLoader
{
    static inline const std::string kRegistryFileName = "Assets/Registry/ModelFiles.txt";

    friend class MeshContext::ModelDataCreator;

    static std::unordered_map<std::string, std::string > Load()
    {
        std::unordered_map<std::string, std::string > modelFileName_pathLib;
        std::ifstream file(kRegistryFileName);

        ErrorMessageOutput::Abort::DetectError
        (
            file.is_open(),
            kRegistryFileName + "このパス無くない？",
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

        Logger::Log("Load: " + kRegistryFileName, "ModelRegistryLoader.h");
        return modelFileName_pathLib;
    }
};

