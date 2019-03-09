//
// Created by HP Pavilion on 09.03.2019.
//

#include "luaParser.hpp"


LuaParser::LuaParser(const std::string &fileName)
{
    L = luaL_newstate();
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        throw std::runtime_error("Script: " + fileName + " could not be loaded");
    }
}

void LuaParser::printError(const std::string &variableName, const std::string &reason)
{
    std::cerr << "Could not get: \'" << variableName << "\'. " << reason << '\n';
}

bool LuaParser::lua_gettostack(const std::string &variableName)
{
    level = 0;
    std::string var;
    for (size_t i = 0; i < variableName.size(); i++){
        if (variableName.at(i) == '.'){
            if (level == 0){
                lua_getglobal(L, var.c_str());
            } else{
                lua_getfield(L, -1, var.c_str());
            }

            if (lua_isnil(L, -1)){
                printError(variableName, var + " is not defined");
                return false;
            } else{
                var = "";
                level++;
            }
        } else{
            var += variableName.at(i);
        }
    }
    if (level == 0){
        lua_getglobal(L, var.c_str());
    } else{
        lua_getfield(L, -1, var.c_str());
    }
    if (lua_isnil(L, -1)){
        printError(variableName, var + " is not defined");
        return false;
    }
    return true;
}


void LuaParser::clean()
{
    int n = lua_gettop(L);
    lua_pop(L, n);
}


std::vector<int> LuaParser::getIntVector(const std::string &name)
{
    std::vector<int> v;
    lua_getglobal(L, name.c_str());
    if (lua_isnil(L, -1)){
        return v;
    }
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        v.push_back(static_cast<int>(lua_tonumber(L, -1)));
        lua_pop(L, -1);
    }
    clean();
    return v;
}

LuaParser::~LuaParser()
{
    if (L)
        lua_close(L);
}
