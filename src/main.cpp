#include <iostream>

#include "../include/luaparser/luaParser.hpp"

int main()
{

    LuaParser luaParser("../test/script.lua");
    auto value = luaParser.get<std::string>("test");
    std::cout << value << std::endl;
    return 0;
}