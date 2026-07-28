#include "LoadRegistry.h"



std::unordered_map<std::string, std::string > LoadRegistry::Load(std::string const kRegistryFileName_)
{
    std::unordered_map<std::string, std::string > modelFileName_pathLib;
    std::ifstream file(kRegistryFileName_);

    ErrorMessageOutput::Abort::DetectError
    (
        file.is_open(),
        kRegistryFileName_ + "このパス無くない？",
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

    Logger::Log("Load: " + kRegistryFileName_, "ModelRegistryLoader.h");
    return modelFileName_pathLib;
}
