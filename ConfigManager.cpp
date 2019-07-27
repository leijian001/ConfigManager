#include "ConfigManager.h"


decltype(ConfigManager::VariantFromJson) ConfigManager::VariantFromJson;
decltype(ConfigManager::VariantToJson) ConfigManager::VariantToJson;


void ConfigManager::_loadJson(VariantMap &map, const Json &json, VariantMap &dMap)
{
    for(auto &it: map)
    {
        auto key = it.first;
        auto val = it.second;

        auto converter = VariantFromJson.find(val.type().name());
        if (converter != VariantFromJson.end())
        {
            bool exist = json.contains(key);
            converter->second(val, exist, exist? json[key] : JsonVal(), dMap[key]);
        }   
    }
}

ConfigManager::Json ConfigManager::_dumpJson(const VariantMap &map)
{
    Json json;

    for(const auto &it: map)
    {
        auto key = it.first;
        auto val = it.second;

        auto converter = VariantToJson.find(val.type().name());
        if (converter != VariantToJson.end())
        {
            converter->second(json, key, val);
        }   
    }

    return json;
}
