//
// Created by Vladimir Rachkin on 25/11/2019.
//

#ifndef __RENDERER_H
#define __RENDERER_H

#endif //ACM_CLUB_RENDERER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "env.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct TextBox{
    std::string str;
    sf::Text sf_text;
    int max_len = 100;
    int max_width = 100;
    void setWidth(int w){
        max_len = w / sf_text.getCharacterSize() * 2;
      //  std::cout << max_len << std::endl;
        max_width = w;
    }

    sf::Text getSFText(){
        return sf_text;
    }

    void setCountChar(unsigned long k){
        std::string res;
        for(auto c : str){
            res += c;
            if(c != ' ' && c != '\n') k--;
            if(k <= 0) break;
        }
        sf_text.setString(res);
    }
    void setString(std::string);
    void setFont(sf::Font f){
        sf_text.setFont(f);
    }
    void setCharacterSize(int s){
        sf_text.setCharacterSize(s);
    }
    void setFillColor(sf::Color c){
        sf_text.setFillColor(c);
    }
    void setPosition(int x, int y){
        sf_text.setPosition(x, y);
    }
    TextBox(){
        sf_text.setCharacterSize(10);
        sf_text.setString("Hello, world!");
    }
};

struct Renderer{

    sf::Vector2f screenQHD    = sf::Vector2f(960.0f, 540.0f);
    sf::Vector2f screenHD     = sf::Vector2f(1280.0f, 720.0f);
    sf::Vector2f screenHDPlus = sf::Vector2f(1600.0f, 900.0f);
    sf::Vector2f screenFHD    = sf::Vector2f(1920.0f, 1080.0f);
    sf::Vector2f screenDefault= screenQHD;
    sf::Vector2f screenSize   = screenQHD;
    sf::Vector2f dialog_size  = sf::Vector2f(800.0f, 130.0f);

    Environment* env;

    sf::RenderWindow window;

    bool is_fullscreen = 0;

    std::string window_name = "ACM club in PhMS";

    std::map < std::string, sf::Text > UI_pause, UI_game, UI_lobby, UI_settings, UI_acmp;
    std::map < ScreenResolution, std::string > string_of_screen_resolution = {
            {ScreenResolution::qHDScreen,    "960x540"},
            {ScreenResolution::HDScreen,     "1280x720"},
            {ScreenResolution::HDPlusScreen, "1600x900"},
            {ScreenResolution::FHDScreen,    "1920x1080"},
    };
    std::map < ScreenResolution, ScreenResolution > next_screen_resolution= {
            {ScreenResolution::qHDScreen,    ScreenResolution::HDScreen},
            {ScreenResolution::HDScreen,     ScreenResolution::HDPlusScreen},
            {ScreenResolution::HDPlusScreen, ScreenResolution::FHDScreen},
            {ScreenResolution::FHDScreen,    ScreenResolution::qHDScreen},
    };

    Renderer(Environment*);

    void initTexts();

    void draw();

    void make_fullscreen();
    void make_defaultscreen();
    void make_fullscreen_bordered();

    void settings_update();
};
