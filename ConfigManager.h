#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <map>
#include <functional>

#include "json.hpp"

class ConfigManager
{
public:
    using Json = nlohmann::json;

private:
    struct Serializer
    {
        std::function<void (Json &json)> ToJson;
        std::function<void (const Json &json)> FromJson;
    };

    ConfigManager(const ConfigManager&) = default;
    ConfigManager(const ConfigManager&&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

public:
    ConfigManager() {}

    void loadJson(const Json &json)
    {
        _loadJson(Params, json);
    }
    Json dumpJson()
    {
        return _dumpJson(Params);
    }

private:
    Json _dumpJson(const std::map<std::string, Serializer> &map)
    {
        Json json;
        for(const auto &it: map)
        {
            it.second.ToJson(json);
        }
        return json;
    }
    void _loadJson(const std::map<std::string, Serializer> &map, const Json &json)
    {
        for(auto &it: map)
        {
            it.second.FromJson(json);
        }
    }

public:
    void Register(const std::string &name, ConfigManager &config)
    {
        Serializer serializer;
        serializer.ToJson = [this, name, config](Json &json)
        {
            json[name] = _dumpJson(config.Params);
        };
        serializer.FromJson = [this, name, config](const Json &json)
        {
            _loadJson(config.Params, json);
        };
        Params[name] = serializer;
    }

    template<typename T>
    void Register(const std::string &name, T *param, T defaultVal)
    {
        Serializer serializer;
        serializer.ToJson = [name, param](Json &json)
        {
            json[name] = *param;
        };
        serializer.FromJson = [name, param, defaultVal](const Json &json)
        {
            *param = json.contains(name)? json[name].get<T>() : defaultVal;
        };
        Params[name] = serializer;
    }

    template<typename T, typename _>
    void Register(const std::string &name, T *param, _ defaultVal)
    {
        Register<T>(name, param, T(defaultVal));
    }

    template<typename T>
    void Register(const std::string &name, T *param)
    {
        Register<T>(name, param, T());
    }

private:
    std::map<std::string, Serializer> Params;
};

#endif
