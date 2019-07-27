#ifndef __CONFIGMANAGER_H__
#define __CONFIGMANAGER_H__

#include <string>
#include <any>
#include <map>
#include <functional>

#include "json.hpp"

class ConfigManager
{
private:
    using Variant = std::any;
    using VariantMap = std::map<std::string, Variant>;

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager(const ConfigManager&&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

public:
    ConfigManager() {}

    using Json = nlohmann::json;
    using JsonVal = Json::value_type;

    void loadJson(const Json &json)
    {
        _loadJson(ParamMap, json, DefaultMap);
    }
    Json dumpJson()
    {
        return _dumpJson(ParamMap);
    }

private:
    void _loadJson(VariantMap &map, const Json &json, VariantMap &dMap);
    Json _dumpJson(const VariantMap &map);

public:
    void register_item(const std::string &name, ConfigManager &param)
    {
        ParamMap[name]   = param.ParamMap;
        DefaultMap[name] = param.DefaultMap;

        const std::string type = ParamMap[name].type().name();
        if (VariantFromJson.find(type) == VariantFromJson.end())
        {
            VariantFromJson[type] = [this](Variant &to, bool exist, const JsonVal &from, const Variant &defdefaultVal)
            {
                auto v = std::any_cast<VariantMap>(to);
                auto d = std::any_cast<VariantMap>(defdefaultVal);
                _loadJson(v, from, d);
            };
        }
        if (VariantToJson.find(type) == VariantToJson.end())
        {
            VariantToJson[type] = [this](Json &json, const std::string &key, const Variant &val)
            {
                json[key] = _dumpJson(std::any_cast<VariantMap>(val));
            };
        }
    }

    template<typename T>
    void register_item(const std::string &name, T *param, T defaultVal)
    {
        ParamMap[name]   = param;
        DefaultMap[name] = defaultVal;

        const std::string type = ParamMap[name].type().name();
        if (VariantFromJson.find(type) == VariantFromJson.end())
        {   // 不存在
            VariantFromJson[type] = [](Variant &to, bool exist, const JsonVal &from, const Variant &defaultVal)
            {
                *std::any_cast<T*>(to) = exist? from.get<T>() : std::any_cast<T>(defaultVal);
            };
        }
        if (VariantToJson.find(type) == VariantToJson.end())
        {   // 不存在
            VariantToJson[type] = [](Json &json, const std::string &key, const Variant &val)
            {
                json[key] = *std::any_cast<T*>(val);
            };
        }
    }

    template<typename T, typename _>
    void register_item(const std::string &name, T *param, _ defaultVal)
    {
        register_item<T>(name, param, T(defaultVal));
    }

    template<typename T>
    void register_item(const std::string &name, T *param)
    {
        register_item<T>(name, param, T());
    } 

private:
    VariantMap ParamMap;
    VariantMap DefaultMap;

    static std::map<std::string, std::function<void (Variant &to, bool exist, const JsonVal &from, const Variant &defaultVal)>> VariantFromJson;
    static std::map<std::string, std::function<void (Json &json, const std::string &key, const Variant &val)>> VariantToJson;
};

#endif