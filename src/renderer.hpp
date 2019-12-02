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

struct Renderer{
    sf::Vector2f screenSize;

    Environment* env;

    sf::RenderWindow window;

    std::map < std::string, sf::Text > UI_pause, UI_game, UI_lobby, UI_settings, UI_acmp;

    Renderer(sf::Vector2f, Environment*);

    void draw();
};
