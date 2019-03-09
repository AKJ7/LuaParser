message(STATUS "LuaParser found!")

add_library(luaparser
            luaParser.cpp
            luaParser.hpp
            )

include_directories(luaparser ${PROJECT_SOURCE_DIR}/include/luaparser)