//
// Created by Vladimir Rachkin on 25/11/2019.
//

#include "script.hpp"

static Script* __script = nullptr;
Script::Script(Environment* env) : env(env) {

}

static std::string _lua_gets(int id) {
    return __script->gv_str[id];
}

static void _lua_sets(int id, std::string s) {
    __script->gv_str[id] = s;
}

static int _lua_geti(int id) {
    return __script->gv_int[id];
}

static void _lua_seti(int id, int s) {
    __script->gv_int[id] = s;
}

void Script::new_game() {
    gv_str[0] = "wry";

    L = luaL_newstate();
    luaL_openlibs(L);

    std::string path = "scripts/globals.lua";
    if(luaL_dofile(L, path.c_str())){
        std::cout << "error: script " + path + " not found" << std::endl;
        std::cout << lua_tostring(L, -1) << std::endl;
        return;
    }

    luabridge::getGlobalNamespace(L)
            .addFunction("glob_gets", _lua_gets)
            .addFunction("glob_sets", _lua_sets)
            .addFunction("glob_geti", _lua_geti)
            .addFunction("glob_seti", _lua_seti);

    enter("sample");
}

void Script::next(int variant) {
    __script = this;

    luabridge::LuaRef f_next = luabridge::getGlobal(L, "next");
    luabridge::LuaRef res = f_next(variant);
    std::string s = res.cast<std::string>();
    std::cout << "Next room is #" << s << std::endl;
    enter(s);
}

void Script::enter(const std::string& s) {
    __script = this;

    std::string path = "scripts/" + s + ".lua";
    if(luaL_dofile(L, path.c_str())){
        std::cout << "error: script " + path + " not found" << std::endl;
        std::cout << lua_tostring(L, -1) << std::endl;
        return;
    }

    luabridge::LuaRef f_enter = luabridge::getGlobal(L, "enter");
    if(f_enter.isNil()) {
        std::cout << "error: f_enter not found in " + s << std::endl;
        return;
    }
    luabridge::LuaRef room = f_enter();

    env->screen.background = room["background"].cast<std::string>();
    env->screen.say        = room["say"].cast<std::string>();
    env->screen.speaker    = room["speaker"].cast<std::string>();

    luabridge::LuaRef tmp = room["characters"]; env->screen.characters.clear();
    if(tmp.isTable()) {
        for (size_t i = 1, n = (size_t)tmp.length(); (i <= n && !tmp[i].isNil()); i++)
            env->screen.characters.push_back(tmp[i].cast<std::string>());
    }
}
