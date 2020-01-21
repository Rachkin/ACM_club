//
// Created by Vladimir Rachkin on 20/01/2020.
//

#ifndef ACM_CLUB_HOMEWORK_HPP
#define ACM_CLUB_HOMEWORK_HPP

#endif //ACM_CLUB_HOMEWORK_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "env.hpp"

#include <stdio.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

using namespace rapidjson;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


struct Homework{
    Environment *env;
    Homework(Environment *env):env(env){}

    void reload(){
        for(auto &task : env->homework){
            task.status = SolveResult::UNDEFINED;
        }

        CURL* curl;
        CURLcode res;
        std::string txt;

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, "https://codeforces.com/api/user.status?handle=vovasher");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &txt);

        res = curl_easy_perform(curl);

        //std::cout << txt << std::endl;


        curl_easy_cleanup(curl);///*/


        Document d;

        d.Parse(txt.c_str());

        Value& result = d["result"];

        if(result.IsArray()){

        }

        for (rapidjson::SizeType i = 0; i < result.Size(); i++){
          //
            for(auto &task : env->homework){
                if(result[i]["problem"]["contestId"].GetInt() == task.contest_id && result[i]["problem"]["index"].GetString() == task.letter){
                    if( result[i]["verdict"].GetString() == std::string("OK")){
                        task.status = SolveResult::OK;
                      //  std::cout << "OK " << task.name << std::endl;
                    }
                    else if(task.status == SolveResult::UNDEFINED){
                        task.status = SolveResult::NO;
                     //   std::cout << "NO " << task.name << " " << result[i]["verdict"].GetString() << std::endl;
                    }
                 //   std::cout << result[i]["verdict"].GetString() << " " << result[i]["problem"]["contestId"].GetInt() << " " << result[i]["problem"]["index"].GetString() << std::endl;

                }
            }
        }
    }
};