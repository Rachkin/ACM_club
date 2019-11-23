#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdint>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "env.hpp"

using namespace std;
using namespace sf;

sf::Vector2f screenSize(800.0f, 600.0f);

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
}

sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y,32), "ACM club)");

int main() {
    Environment* env = new Environment();

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
    int64_t string_shown      = 0;
    int64_t string_will_shown = 0;
    map < string, Text > UI_esc, UI_dialog;

    UI_esc["menu_label"].setString("MENU");
    UI_esc["menu_label"].setCharacterSize(40);
    UI_esc["menu_label"].setPosition(100,70);


    UI_esc["menu_resume"].setString("resume");
    UI_esc["menu_resume"].setCharacterSize(30);
    UI_esc["menu_resume"].setPosition(120,120);

    for(int i = 1; i <= 3; i++){
        UI_esc["menu_load" + to_string(i)].setString("load" + to_string(i));
        UI_esc["menu_load" + to_string(i)].setCharacterSize(30);
        UI_esc["menu_load" + to_string(i)].setPosition(120,150 + (i - 1) * 30);
    }

    for(int i = 1; i <= 3; i++) {
        UI_esc["menu_save" + to_string(i)].setString("save" + to_string(i));
        UI_esc["menu_save" + to_string(i)].setCharacterSize(30);
        UI_esc["menu_save" + to_string(i)].setPosition(300, 150 + (i - 1) * 30);
    }

    UI_esc["menu_exit"].setString("!exit game!");
    UI_esc["menu_exit"].setCharacterSize(30);
    UI_esc["menu_exit"].setPosition(120,300);


    UI_dialog["menu_botton"].setString("menu");
    UI_dialog["menu_botton"].setCharacterSize(30);
    UI_dialog["menu_botton"].setPosition(20,window.getSize().y - 50);


    for(auto &p : UI_esc){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }

    for(auto &p : UI_dialog){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }


    while(window.isOpen()) {
        sf::Event event;
        int64_t now_time = timeSinceEpochMillisec();

        while(window.pollEvent(event)) {

            string_will_shown = min((int64_t)(now_time - textstart_time) / text_speed, (int64_t)env->strings[env->screen.say].size());
            if(next_time <= now_time) {
                if (event.type == sf::Event::Closed) {
                    window.close();
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

        if(string_will_shown != string_shown){
            is_changed = 1;
            string_shown = string_will_shown;
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
            window.clear(Color::Black);

            if(env->render_type == RenderType::Game) {
                Sprite background = env->sprites[env->screen.background];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    (screenSize.y-130) / background.getLocalBounds().height);

                window.draw(background);

                int i = 0;

                for(auto c : env->screen.characters){
                    Sprite character = env->sprites[c];
                    double k = 0;
                    if(c == env->screen.speaker) k = 0.8;
                        else k = 0.7;
                    character.setScale(screenSize.y / character.getLocalBounds().height * k,
                                       screenSize.y / character.getLocalBounds().height * k);
                    character.setPosition((i+1) * screenSize.x / (env->screen.characters.size()+1) - character.getGlobalBounds().width/2,
                            screenSize.y/2 - character.getGlobalBounds().height/2);
                    window.draw(character);
                    i++;
                }

                Sprite dialog = env->sprites["dialog"];
                dialog.setScale(screenSize.x / dialog.getLocalBounds().width,
                                (130) / dialog.getLocalBounds().height);
                dialog.setPosition(0, screenSize.y - 130);

                window.draw(dialog);

                Text speaker;
                speaker.setString(env->characters[env->screen.speaker].fullname);
                speaker.setCharacterSize(30);
                speaker.setFont(env->fonts["arial"]);
                speaker.setFillColor(sf::Color::Black);
                speaker.setPosition(100,
                                    window.getSize().y - 120);
                window.draw(speaker);

                Text say;
                say.setString(env->strings[env->screen.say].substr(0, string_shown));
                say.setCharacterSize(20);
                say.setFont(env->fonts["arial"]);
                say.setFillColor(Color::Black);
                say.setPosition(120,
                                window.getSize().y - 80); // - say.getGlobalBounds().height/2
                window.draw(say);

                for(auto &p : UI_dialog)
                    window.draw(p.second);
            } 
            else if(env->render_type == RenderType::Pause) {
                Sprite background = env->sprites["escmenu"];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    screenSize.y / background.getLocalBounds().height);
                window.draw(background);

                for(int i = 1; i <= 3; i++) {
                    ifstream in("saves/save" + to_string(i) + ".txt");
                    string s;
                    in >> s;
                    UI_esc["menu_load" + to_string(i)].setString("load" + to_string(i) + "(" + s + ")");
                }

                for(auto &p : UI_esc) 
                    window.draw(p.second);
            }
            else if(env->render_type == RenderType::Lobby) {
                // TODO: Generate okay lobby
                window.display();
            }

            is_changed = false;
            window.display();
        }

    }
    return 0;
}