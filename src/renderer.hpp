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
#include "env.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Renderer{

    sf::Vector2f screen800 = sf::Vector2f(800.0f, 600.0f);
    sf::Vector2f screenSize = sf::Vector2f(800.0f, 600.0f);

    Environment* env;

    sf::RenderWindow window;

    bool is_fullscreen = 0;

    std::string window_name = "ACM club in PhMS";

    std::map < std::string, sf::Text > UI_pause, UI_game, UI_lobby, UI_settings, UI_acmp;

    Renderer(Environment*);

    void initTexts();

    void draw();

    void make_fullscreen();
    void make_defaultscreen();
    void make_fullscreen_bordered();
};
