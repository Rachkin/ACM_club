//
// Created by Vladimir Rachkin on 25/11/2019.
//

#include "script.hpp"

static Script* __script = nullptr;
Script::Script(Environment* env, TestingSystem* test_sys) : env(env), test_sys(test_sys) {

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

static RenderType _lua_to_render_type(std::string s){
    if(s == "Game") return RenderType::Game;
    if(s == "Lobby") return RenderType::Lobby;
    if(s == "Acmp") return RenderType::Acmp;
}

void Script::import(std::string path){
    if(luaL_dofile(L, path.c_str())){
        __make_error("script " + path + " not found");
     //   std::cout << lua_tostring(L, -1) << std::endl;
        return;
    }
}

void Script::new_game() {
    gv_str[0] = "wry";

    L = luaL_newstate();
    luaL_openlibs(L);

    import("scripts/__globals.lua");
    import("scripts/_init_characters.lua");
    import("scripts/_init_backgrounds.lua");

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
        __make_error("script " + path + " not found");
        //std::cout << lua_tostring(L, -1) << std::endl;
        return;
    }

    luabridge::LuaRef f_enter = luabridge::getGlobal(L, "enter");
    if(f_enter.isNil()) {
        __make_error("f_enter not found in " + s);
        return;
    }
    luabridge::LuaRef room = f_enter();

    env->screen.background = room["background"].cast<std::string>();
    env->screen.say        = room["say"].cast<std::string>();
    env->screen.speaker    = room["speaker"].cast<std::string>();
    if(!room["type"].isNil())
        env->render_type =  _lua_to_render_type(room["type"].cast<std::string>());

    if(env->render_type == RenderType::Acmp){
        test_sys->upload_task("a+b");
    }

    luabridge::LuaRef tmp = room["characters"]; env->screen.characters.clear();
    if(tmp.isTable()) {
        for (size_t i = 1, n = (size_t) tmp.length(); (i <= n && !tmp[i].isNil()); i++)
            env->screen.characters.push_back(tmp[i].cast<std::string>());
    }

}
