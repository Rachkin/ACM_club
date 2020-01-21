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

void TestingSystem::upload_task(std::string task_name){
    /*
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, "scripts/tasks/list.lua");

    luabridge::LuaRef task_list = luabridge::getGlobal(L, "task_list");

    if(task_list.isNil()){
        __make_error("Task list not found!");
        return;
    }

    luabridge::LuaRef task = task_list[task_name.c_str()];

    if(task.isNil()){
        __make_error("Task '" + task_name + "' not found!");
        return;
    }



    std::string path = "scripts/tasks/" + task["path"].cast<std::string>() + "/" + (task["description"].isNil() ? "description.lua" : task["description"].cast<std::string>());


    if(luaL_dofile(L, path.c_str())){
        __make_error("Task description file " + path + " not found");
        //std::cout << lua_tostring(L, -1) << std::endl;
        return;
    }

    luabridge::LuaRef description = luabridge::getGlobal(L, "description");
    luabridge::LuaRef sample_input = luabridge::getGlobal(L, "sample_input");
    luabridge::LuaRef sample_output = luabridge::getGlobal(L, "sample_output");
    luabridge::LuaRef input = luabridge::getGlobal(L, "input");
    luabridge::LuaRef output = luabridge::getGlobal(L, "output");
    luabridge::LuaRef name = luabridge::getGlobal(L, "name");

    if(name.isNil()){
        __make_error("Name of task '" + task_name + "' not found!");
        return;
    }


    if(!description.isNil())    env->task.description   = description.cast<std::string>();
    if(!name.isNil())           env->task.name          = name.cast<std::string>();
    if(!input.isNil())          env->task.input         = input.cast<std::string>();
    if(!output.isNil())         env->task.output        = output.cast<std::string>();

    env->task.sample_input.clear();
    if(!sample_input.isNil())   for(int i = 0; sample_input[i].isNil(); i++) env->task.sample_input.push_back(sample_input[i].cast<std::string>());
    env->task.sample_output.clear();
    if(!sample_output.isNil())  for(int i = 0; sample_output[i].isNil(); i++) env->task.sample_output.push_back(sample_output[i].cast<std::string>());

    std::cout << env->task.input << std::endl;
    */
}


std::string TestingSystem::Test(std::string program, std::string task_name){
    /*
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

*/
}
