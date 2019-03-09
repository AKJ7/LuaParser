//
// Created by HP Pavilion on 09.03.2019.
//

#ifndef LUAPARSER_LUAPARSER_HPP
#define LUAPARSER_LUAPARSER_HPP

#include <iostream>
#include <vector>
#include <string>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
};

class LuaParser {
private:
    lua_State* L;
    int level = 0;
    std::string fileName;

public:
    explicit LuaParser(const std::string& fileName);
    void printError(const std::string& variableName, const std::string& reason);
    template <typename T> T get(const std::string& variableName)
    {
        if (!L) {
            printError(variableName, "Script was not loaded");
            return lua_getdefault<T>();
        }

        T result;
        if (lua_gettostack(variableName)) {
            result = lua_get<T>(variableName);
        } else {
            result = lua_getdefault<T>();
        }
        lua_pop(L, level + 1);
        return result;
    };

    bool lua_gettostack(const std::string& variableName);

    template <typename T>
    T lua_get(const std::string& variableName)
    {
        return 0;
    };

    template<typename T>
    T lua_getdefault() {
        return 0;
    }
    ~LuaParser();
};

template<>
inline bool LuaParser::lua_get(const std::string &variableName) {
    return static_cast<bool>(lua_toboolean(L, -1));
}

template<>
inline float LuaParser::lua_get(const std::string &variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return static_cast<float>(lua_tonumber(L, -1));
}

template<>
inline int LuaParser::lua_get(const std::string &variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return static_cast<int>(lua_tonumber(L, -1));
}

template<>
inline std::string LuaParser::lua_get(const std::string &variableName) {
    std::string s = "null";
    if (lua_isstring(L, -1)) {
        s = std::string(lua_tostring(L, -1));
    } else {
        printError(variableName, "Not a string");
    }
    return s;
}

template<>
inline std::string LuaParser::lua_getdefault<std::string>() {
    return "null";
}



#endif //LUAPARSER_LUAPARSER_HPP
