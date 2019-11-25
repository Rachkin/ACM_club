//
// Created by Vladimir Rachkin on 25/11/2019.
//

#include "renderer.hpp"

Renderer::Renderer(sf::Vector2f _screenSize, Environment* _env){
    env = _env;
    screenSize = _screenSize;
    window.create(sf::VideoMode(screenSize.x, screenSize.y,32), "ACM club)");

    UI_esc["menu_label"].setString("MENU");
    UI_esc["menu_label"].setCharacterSize(40);
    UI_esc["menu_label"].setPosition(100,70);


    UI_esc["menu_resume"].setString("resume");
    UI_esc["menu_resume"].setCharacterSize(30);
    UI_esc["menu_resume"].setPosition(120,120);

    for(int i = 1; i <= 3; i++){
        UI_esc["menu_load" + std::to_string(i)].setString("load" + std::to_string(i));
        UI_esc["menu_load" + std::to_string(i)].setCharacterSize(30);
        UI_esc["menu_load" + std::to_string(i)].setPosition(120,150 + (i - 1) * 30);
    }

    for(int i = 1; i <= 3; i++) {
        UI_esc["menu_save" + std::to_string(i)].setString("save" + std::to_string(i));
        UI_esc["menu_save" + std::to_string(i)].setCharacterSize(30);
        UI_esc["menu_save" + std::to_string(i)].setPosition(300, 150 + (i - 1) * 30);
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

    for(auto &p : UI_lobby){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }

}

void Renderer::draw(){

    window.clear(sf::Color::Black);

    if(env->render_type == RenderType::Game) {
        sf::Sprite background = env->sprites[env->screen.background];
        background.setScale(screenSize.x / background.getLocalBounds().width,
                            (screenSize.y-130) / background.getLocalBounds().height);

        window.draw(background);

        int i = 0;

        for(auto c : env->screen.characters){
            sf::Sprite character = env->sprites[c];
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

        sf::Sprite dialog = env->sprites["dialog"];
        dialog.setScale(screenSize.x / dialog.getLocalBounds().width,
                        (130) / dialog.getLocalBounds().height);
        dialog.setPosition(0, screenSize.y - 130);

        window.draw(dialog);

        sf::Text speaker;
        speaker.setString(env->characters[env->screen.speaker].fullname);
        speaker.setCharacterSize(30);
        speaker.setFont(env->fonts["arial"]);
        speaker.setFillColor(sf::Color::Black);
        speaker.setPosition(100,
                            window.getSize().y - 120);
        window.draw(speaker);

        sf::Text say;
        say.setString(env->strings[env->screen.say].substr(0, env->string_shown));
        say.setCharacterSize(20);
        say.setFont(env->fonts["arial"]);
        say.setFillColor(sf::Color::Black);
        say.setPosition(120,
                        window.getSize().y - 80); // - say.getGlobalBounds().height/2
        window.draw(say);

        for(auto &p : UI_dialog)
            window.draw(p.second);
    }
    else if(env->render_type == RenderType::Pause) {
        sf::Sprite background = env->sprites["escmenu"];
        background.setScale(screenSize.x / background.getLocalBounds().width,
                            screenSize.y / background.getLocalBounds().height);
        window.draw(background);

        for(int i = 1; i <= 3; i++) {
            std::ifstream in("saves/save" + std::to_string(i) + ".txt");
            std::string s;
            in >> s;
            UI_esc["menu_load" + std::to_string(i)].setString("load" + std::to_string(i) + "(" + s + ")");
        }

        for(auto &p : UI_esc)
            window.draw(p.second);
    }
    else if(env->render_type == RenderType::Lobby) {
        // TODO: Generate okay lobby
        std::cout << "lobby" << std::endl;
        sf::Sprite background = env->sprites["lobby"];
        background.setScale(screenSize.x / background.getLocalBounds().width,
                            screenSize.y / background.getLocalBounds().height);
        window.draw(background);

        sf::Text name_of_game;
        name_of_game.setString("ACM club in SFU");
        name_of_game.setCharacterSize(50);
        name_of_game.setPosition(70, 100);
        name_of_game.setFont(env->fonts["arial"]);
        name_of_game.setFillColor(sf::Color::Black);
        window.draw(name_of_game);

        for(auto &p : UI_lobby)
            window.draw(p.second);
    }

    window.display();
}