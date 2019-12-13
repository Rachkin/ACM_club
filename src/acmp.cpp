//
// Created by Vladimir Rachkin on 25/11/2019.
//

#include "acmp.hpp"

bool copyFile(std::string SRC, std::string DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}

std::string TestingSystem::convert(std::string program){
    while(program.find("print")){
        int b = program.find("print");
        int e = program.find("print")+ 6;
        program = program.substr(0, b) + "OUTPUT += " + program.substr(e);
    }

    while(program.find("io.write")){
        int b = program.find("io.write");
        int e = program.find("io.write") + 6;
        program = program.substr(0, b) + "OUTPUT += " + program.substr(e);
    }
}


std::string TestingSystem::Test(std::string program, std::string task_name){
    std::ofstream solution_file("polygone/solution.lua");
    solution_file << program;

    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, "scripts/tasks/list.lua");

    luabridge::LuaRef task = luabridge::getGlobal(L, ("task_list[" + task_name + "]").c_str());

    copyFile(task["path"].cast<std::string>() + "/" + (task["test_gen"].isNil()    ? task["test_gen"].cast<std::string>()    : "test_gen.lua")   , "polygone/test_gen.lua");
    copyFile(task["path"].cast<std::string>() + "/" + (task["description"].isNil() ? task["description"].cast<std::string>() : "description.lua"), "polygone/description.lua");
    copyFile(task["path"].cast<std::string>() + "/" + (task["checker"].isNil()     ? task["checker"].cast<std::string>()     : "checker.lua")    , "polygone/checker.lua");

    L = luaL_newstate();
    luaL_openlibs(L);


}
