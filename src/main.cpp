#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdint>

//#include <Lua/lua.hpp>
//#include <LuaBridge/LuaBridge.h>

#include "env.hpp"
#include "renderer.hpp"

using namespace std;
using namespace sf;

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
}

sf::Vector2f screenSize(800.0f, 600.0f);


int main() {
    Environment* env = new Environment();
    Renderer* renderer = new Renderer(screenSize, env);

    env->screen.background = "front";
    env->screen.characters = {"dio"};
    env->screen.say        = "wry";
    env->screen.speaker    = "dio";
    env->screen.type       = ScreenType::Monolog;

    bool is_changed = 1;
    int64_t start_time        = timeSinceEpochMillisec();
    int64_t textstart_time    = timeSinceEpochMillisec();
    int64_t next_time         = timeSinceEpochMillisec();
    int64_t d_next            = 200;
    int text_speed            = 50;
    int64_t string_will_shown = 0;


    while(renderer->window.isOpen()) {
        sf::Event event;
        int64_t now_time = timeSinceEpochMillisec();

        while(renderer->window.pollEvent(event)) {

            string_will_shown = min((int64_t)(now_time - textstart_time) / text_speed, (int64_t)env->strings[env->screen.say].size());
            if(next_time <= now_time) {
                if (event.type == sf::Event::Closed) {
                    renderer->window.close();
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                    if (string_will_shown == (int) env->strings[env->screen.say].size()) {
                        // TODO: make LUA script
                        //if (env->screen.child == "-1") window.close();
                        //env->screen = screens[env->screen.child];
                        //textstart_time = now_time + d_next;
                    } else {
                        textstart_time = -10000000;
                    }
                    is_changed = 1;

                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                         if(env->render_type == RenderType::Pause) env->render_type = RenderType::Game;
                    else if(env->render_type == RenderType::Game)  env->render_type = RenderType::Pause;
                    is_changed = 1;
                }
                next_time = now_time + d_next;
            }
        }

        string_will_shown = min((int64_t)(now_time - textstart_time) / text_speed, (int64_t)env->strings[env->screen.say].size());
        string_will_shown = max(0ll, string_will_shown);

        if(string_will_shown != env->string_shown){
            is_changed = 1;
            env->string_shown = string_will_shown;
        }

        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // hit test6
        if(env->render_type == RenderType::Pause) {
            for(auto &p : UI_esc) {
                sf::FloatRect bounds = p.second.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    if (p.second.getFillColor() == Color::Black) is_changed = 1;
                    p.second.setFillColor(Color::Red);
                }
                else {
                    if (p.second.getFillColor() == Color::Red) is_changed = 1;
                    p.second.setFillColor(Color::Black);
                }

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // transform the mouse position from window coordinates to world coordinates
                if (UI_esc["menu_exit"].getGlobalBounds().contains(mouse)) {
                    window.close();
                }
                // TODO: Make saves for scripts
                /*
                for(int i = 1; i <= 3; i++) {
                    if (UI_esc["menu_load" + to_string(i)].getGlobalBounds().contains(mouse)) {
                        ifstream in("saves/save" + to_string(i) + ".txt");
                        string s;
                        in >> s;
                        env->screen = env->screens[s];
                        env->render_type = RenderType::Game;
                        is_changed = 1;
                    }
                }
                for(int i = 1; i <= 3; i++) {
                    if (UI_esc["menu_save" + to_string(i)].getGlobalBounds().contains(mouse)) {
                        ofstream out("saves/save" + to_string(i) + ".txt");
                        out << env->screen.name;
                        env->render_type = RenderType::Game;
                        is_changed = 1;
                    }
                }
                */

                if (UI_esc["menu_resume"].getGlobalBounds().contains(mouse)) {
                    env->render_type = RenderType::Game;
                    is_changed = 1;
                }
            }
        }
        else if(env->render_type == RenderType::Game) {
            for(auto &p : UI_dialog) {
                sf::FloatRect bounds = p.second.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    if (p.second.getFillColor() == Color::Black) is_changed = 1;
                    p.second.setFillColor(Color::Red);
                }
                else {
                    if (p.second.getFillColor() == Color::Red) is_changed = 1;
                    p.second.setFillColor(Color::Black);
                }

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (UI_dialog["menu_botton"].getGlobalBounds().contains(mouse)) {
                    env->render_type = RenderType::Pause;
                    is_changed = 1;
                   // sf::SoundBuffer buffer;
                  //  buffer.loadFromFile("sounds/classic_hurt.mp3");
                  //  sf::Sound sound;
                  //  sound.setBuffer(buffer);
                  //  sound.play();
                }
            }
        }

        if(is_changed) {
            renderer.draw();
            is_changed = 0;
        }

    }
    return 0;
}