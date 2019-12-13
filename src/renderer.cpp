//
// Created by Vladimir Rachkin on 25/11/2019.
//

#include "renderer.hpp"

void Renderer::initTexts(){
    UI_pause["resume"].setString("resume");
    UI_pause["resume"].setCharacterSize(30);
    UI_pause["resume"].setPosition(120,120);

    UI_pause["settings"].setString("settings");
    UI_pause["settings"].setCharacterSize(30);
    UI_pause["settings"].setPosition(120,150);

    for(int i = 1; i <= 3; i++){
        UI_pause["load" + std::to_string(i)].setString("load" + std::to_string(i));
        UI_pause["load" + std::to_string(i)].setCharacterSize(30);
        UI_pause["load" + std::to_string(i)].setPosition(120,150 + (i) * 30);
    }

    for(int i = 1; i <= 3; i++) {
        UI_pause["save" + std::to_string(i)].setString("save" + std::to_string(i));
        UI_pause["save" + std::to_string(i)].setCharacterSize(30);
        UI_pause["save" + std::to_string(i)].setPosition(300, 150 + (i) * 30);
    }

    UI_pause["exit"].setString("!exit game!");
    UI_pause["exit"].setCharacterSize(30);
    UI_pause["exit"].setPosition(120,300);

    ///////////////////

    UI_game["menu_button"].setString("menu");
    UI_game["menu_button"].setCharacterSize(30);
    UI_game["menu_button"].setPosition(20, screenSize.y - 50);

    ///////////////////

    UI_lobby["new_game"].setString("new game");
    UI_lobby["new_game"].setCharacterSize(40);
    UI_lobby["new_game"].setPosition(100, 200);
/*
    UI_lobby["settings"].setString("settings");
    UI_lobby["settings"].setCharacterSize(40);
    UI_lobby["settings"].setPosition(100, 240);
*/
    //////////////////

    UI_settings["resume"].setString("resume");
    UI_settings["resume"].setCharacterSize(30);
    UI_settings["resume"].setPosition(120,120);

    UI_settings["fullscreen"].setString("fullscreen");
    UI_settings["fullscreen"].setCharacterSize(30);
    UI_settings["fullscreen"].setPosition(120,150);

    UI_settings["fullscreen_bordered"].setString("fullscreen(bordered)");
    UI_settings["fullscreen_bordered"].setCharacterSize(30);
    UI_settings["fullscreen_bordered"].setPosition(120,180);

    UI_settings["defaultscreen"].setString("default screen");
    UI_settings["defaultscreen"].setCharacterSize(30);
    UI_settings["defaultscreen"].setPosition(120,210);

    for(auto &p : UI_pause){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }

    for(auto &p : UI_game){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }

    for(auto &p : UI_lobby){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }

    for(auto &p : UI_settings){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }

    for(auto &p : UI_acmp){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }
}

Renderer::Renderer(Environment* _env){
    env = _env;
    make_defaultscreen();
    initTexts();
}

sf::Sprite get_sptite(std::string path){
    sf::Image image;
    image.loadFromFile(path);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}


void Renderer::draw(){

    window.clear(sf::Color::Black);

    if(env->render_type == RenderType::Game) {
        sf::Image image;
        image.loadFromFile("images/backgrounds/" + env->screen.background);
        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite background;
        background.setTexture(texture);
        background.setScale(screenSize.x / background.getLocalBounds().width,
                            (screenSize.y-130) / background.getLocalBounds().height);

        window.draw(background);

        int i = 0;

        for(auto c : env->screen.characters){
            sf::Image image;
            image.loadFromFile("images/characters/" + c);
            sf::Texture texture;
            texture.loadFromImage(image);
            sf::Sprite character;
            character.setTexture(texture);
            double k = 0;
            if(c.find(env->screen.speaker) != c.size()) k = 0.8;
            else k = 0.7;
            character.setScale(window.getSize().y / character.getLocalBounds().height * k,
                               window.getSize().y / character.getLocalBounds().height * k);
            character.setPosition((i+1) * window.getSize().x / (env->screen.characters.size()+1) - character.getGlobalBounds().width/2,
                                  window.getSize().y/2 - character.getGlobalBounds().height/2);
            window.draw(character);
            i++;
        }

        sf::Sprite dialog = env->sprites["dialog"];
        dialog.setScale(screenSize.x / dialog.getLocalBounds().width,
                        (130) / dialog.getLocalBounds().height);
        dialog.setPosition(0, window.getSize().y - 130);

        window.draw(dialog);

        sf::Text speaker;
        speaker.setString(env->screen.speaker);
        speaker.setCharacterSize(30);
        speaker.setFont(env->fonts["arial"]);
        speaker.setFillColor(sf::Color::Black);
        speaker.setPosition(100,
                            window.getSize().y - 120);
        window.draw(speaker);

        sf::Text say;
        say.setString(env->screen.say.substr(0, env->string_shown));
        say.setCharacterSize(20);
        say.setFont(env->fonts["arial"]);
        say.setFillColor(sf::Color::Black);
        say.setPosition(120,
                        window.getSize().y - 80); // - say.getGlobalBounds().height/2
        window.draw(say);

        for(auto &p : UI_game)
            window.draw(p.second);
    }
    else if(env->render_type == RenderType::Pause) {
        sf::Sprite background = env->sprites["escmenu"];
        background.setScale(screenSize.x / background.getLocalBounds().width,
                            screenSize.y / background.getLocalBounds().height);
        window.draw(background);

        sf::Text label;
        label.setString("MENU");
        label.setCharacterSize(40);
        label.setPosition(100,70);
        label.setFont(env->fonts["arial"]);
        label.setFillColor(sf::Color::Black);
        window.draw(label);

        for(int i = 1; i <= 3; i++) {
            std::ifstream in("saves/save" + std::to_string(i) + ".txt");
            std::string s;
            in >> s;
            UI_pause["load" + std::to_string(i)].setString("load" + std::to_string(i) + "(" + s + ")");
        }

        for(auto &p : UI_pause)
            window.draw(p.second);
    }
    else if(env->render_type == RenderType::Lobby) {
        // TODO: Generate okay lobby
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
    }else if(env->render_type == RenderType::Settings) {
        // TODO: Generate okay settings
        sf::Sprite background = env->sprites["lobby"];
        background.setScale(screenSize.x / background.getLocalBounds().width,
                            screenSize.y / background.getLocalBounds().height);
        window.draw(background);

        sf::Text label;
        label.setString("SETTINGS");
        label.setCharacterSize(40);
        label.setPosition(100,70);
        label.setFont(env->fonts["arial"]);
        label.setFillColor(sf::Color::Black);
        window.draw(label);

        for(auto &p : UI_settings)
            window.draw(p.second);
    }else if(env->render_type == RenderType::Acmp) {

        // TODO: Generate okay acmp
        sf::Sprite background = env->sprites["acmp_left"];
        background.setScale(screenSize.x / background.getLocalBounds().width/2,
                            screenSize.y / background.getLocalBounds().height);
        background.setPosition(0, 0);
        window.draw(background);

        background = env->sprites["acmp_right"];
        background.setScale(screenSize.x / background.getLocalBounds().width/2,
                            screenSize.y / background.getLocalBounds().height);
        background.setPosition(screenSize.x/2, 0);
        window.draw(background);

        sf::Text name;
        name.setString(env->screen.name);
        name.setCharacterSize(30);
        name.setFont(env->fonts["arial"]);
        name.setFillColor(sf::Color::Black);
        name.setPosition(screenSize.x / 4 - name.getLocalBounds().width/2,
                            30);
        window.draw(name);

        sf::Text description;
        description.setString(env->screen.description);
        description.setCharacterSize(30);
        description.setFont(env->fonts["arial"]);
        description.setFillColor(sf::Color::Black);
        description.setPosition(30,
                         30);
        window.draw(name);

        for(auto &p : UI_acmp)
            window.draw(p.second);
    }

    window.display();
}

void Renderer::make_defaultscreen(){
    screenSize = screen800;
    window.create(sf::VideoMode(screenSize.x, screenSize.y), window_name);
    initTexts();
}

void Renderer::make_fullscreen(){
    screenSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    window.create(sf::VideoMode(screenSize.x, screenSize.y), window_name, sf::Style::Fullscreen);
    initTexts();
}

void Renderer::make_fullscreen_bordered(){
    screenSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    window.create(sf::VideoMode(screenSize.x, screenSize.y), window_name);
    initTexts();
}
