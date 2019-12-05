#ifndef ACM_CLUB_SCRIPT_H
#define ACM_CLUB_SCRIPT_H

#endif //ACM_CLUB_SCRIPT_H

#include <string>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "env.hpp"

const int MAX_VARIABLE_COUNT = 2048;

struct Script {
    Environment* env;
    Script(Environment*);
    lua_State* L;

    void import(std::string);

    // Global variables
    std::string gv_str[MAX_VARIABLE_COUNT];
    int         gv_int[MAX_VARIABLE_COUNT];

    void new_game();
    void next(int);
    void enter(const std::string&);
};
