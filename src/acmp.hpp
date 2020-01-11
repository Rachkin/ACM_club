#ifndef ACM_CLUB_ACMP_H
#define ACM_CLUB_ACMP_H

#endif //ACM_CLUB_ACMP_H

#include<string>
#include<fstream>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "env.hpp"

struct TestingSystem{
    Environment* env;

    void upload_task(std::string);

    std::string input_path;
    std::string output_path;

    std::string convert(std::string program);

    std::string Test(std::string, std::string);
    TestingSystem(Environment* env):env(env){}
};