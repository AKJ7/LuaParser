cmake_minimum_required(VERSION 3.10)
project(LuaParser)

set(CMAKE_CXX_STANDARD 11)
set(LuaParserVERSION_MAJOR 1)

include_directories(LuaParser
        deps/lua-5.3.5/src
        )

add_subdirectory(deps/lua-5.3.5/)
add_subdirectory(include/luaparser)

add_executable(LuaParser
                src/main.cpp
        )
target_link_libraries(LuaParser luaparser lua)