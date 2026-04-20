//
// Created by pedro-souza on 20/04/2026.
//
#include "JsonUtil.h"
#include <fstream>
#include <SDL2/SDL_log.h>

bool JsonUtil::LoadAndValidate(const std::string &fileName, const std::vector<std::string> &requiredFields, json &outJson) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        SDL_Log("[JsonUtil] Failed to open file %s", fileName.c_str());
        return false;
    }

    try {
        file >> outJson;

        if (!outJson.is_object()) {
            SDL_Log("[JsonUtil] Not a valid object %s", fileName.c_str());
            return false;
        }

        for (const auto& field: requiredFields){
            if (!outJson.contains(field)) {
                SDL_Log("[JsonUtil] Required field '%s' not found", field.c_str());
                return false;
            }
        }
    }catch (const json::parse_error &e) {
        SDL_Log("[JsonUtil] Syntax Error in json file %s", fileName.c_str());
        return false;
    } catch (const std::exception& e) {
        SDL_Log("[JsonUtil] Error in json file %s", fileName.c_str());
        return false;
    }

    return true;
}
