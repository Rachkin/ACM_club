//
// Created by Vladimir Rachkin on 25/11/2019.
//

#include "renderer.hpp"

#include<iostream>


void TextBox::setString(std::string s){
    std::string t;
    std::string res = "    ";

    int len = 4;
    for(auto c : s){
        if(c == ' '){

            if(len == 0){
                len = t.size();
            }else{
                sf_text.setString(res + " " + t);
               // std::cout << sf_text.getLocalBounds().width << std::endl;
                if(sf_text.getLocalBounds().width > max_width){
                    res += "\n";
                }else{
                    res += " ";
                }
                /*
                if(len + t.size() + 1 > max_len){
                    res += "\n";
                    len = t.size();
                }else{
                    res += " ";
                    len += t.size() + 1;
                }
                 */
            }
            res += t;

            t = "";
        } else t += c;
    }
    if(len != 0)
        if(len + t.size() + 1 > max_len){
            res += "\n";
        }else{
            res += " ";
        }
    res += t;
    str = res;
  //  std::cout << std::endl<< std::endl<< std::endl<< std::endl<< std::endl << std::endl;
   // std::cout << str << std::endl;
    sf_text.setString(str);
}



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
    UI_game["menu_button"].setCharacterSize(20);
    UI_game["menu_button"].setPosition(20, screenSize.y - 35);

    ///////////////////

    UI_lobby["new_game"].setString("new game");
    UI_lobby["new_game"].setCharacterSize(40);
    UI_lobby["new_game"].setPosition(100, 200);
/*
    UI_lobby["settings"].setString("settings");
    UI_lobby["settings"].setCharacterSize(40);
    UI_lobby["settings"].setPosition(100, 240);
*/
    ////////////////// Setting

    UI_settings["cancel"].setString("cancel");
    UI_settings["cancel"].setCharacterSize(30);
    UI_settings["cancel"].setPosition(120,120);

    UI_settings["apply"].setString("apply");
    UI_settings["apply"].setCharacterSize(30);
    UI_settings["apply"].setPosition(240,120);

    if (env->settings.is_fullscreen == 0) UI_settings["fullscreen"].setString("border");
    else                                  UI_settings["fullscreen"].setString("fullscreen");
    UI_settings["fullscreen"].setCharacterSize(30);
    UI_settings["fullscreen"].setPosition(120,150);

    UI_settings["screen_resolution"].setString(string_of_screen_resolution[env->settings.screen_resolution]);
    UI_settings["screen_resolution"].setCharacterSize(30);
    UI_settings["screen_resolution"].setPosition(120,210);

    //////////////////////////
    UI_homework["check"].setString("Check");
    UI_homework["check"].setCharacterSize(30);
    UI_homework["check"].setPosition(20, screenSize.y - 50);

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

    for(auto &p : UI_homework){
        p.second.setFont(env->fonts["arial"]);
        p.second.setFillColor(sf::Color::Black);
    }
}

Renderer::Renderer(Environment* _env){
    env = _env;
    settings_update();
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

        dialog.setScale(window.getSize().x/ dialog.getLocalBounds().width,
                        (dialog_size.y) / dialog.getLocalBounds().height);
        dialog.setPosition(0, window.getSize().y - dialog_size.y);

        window.draw(dialog);

        sf::Text speaker;
        speaker.setString(env->screen.speaker);
        speaker.setCharacterSize(30);
        speaker.setFont(env->fonts["arial"]);
        speaker.setFillColor(sf::Color::Black);
        speaker.setPosition(120,
                            window.getSize().y - dialog_size.y);
        window.draw(speaker);

        TextBox say = TextBox();
       // say.setString(env->screen.say.substr(0, env->string_shown));
      //  sf::Text say;
        say.setCharacterSize(18);
        say.sf_text.setFont(env->fonts["arial"]);
        say.setFillColor(sf::Color::Black);
     // - say.getGlobalBounds().height/2
        say.setWidth(window.getSize().x - 140 * 2);
        say.setString(env->screen.say);
        say.setCountChar(env->string_shown);
        say.setPosition(140,
                        window.getSize().y - 90);
       // std::cout << say.sf_text.getString().toAnsiString() << std::endl;

       // window.draw(say.sf_text);
        window.draw(say.getSFText());

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
        name_of_game.setString("Programing Club");
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
    }else if(env->render_type == RenderType::Homework) {

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
        name.setString("Your homework to today");
        name.setCharacterSize(40);
        name.setFont(env->fonts["arial"]);
        name.setFillColor(sf::Color::Black);
        name.setPosition(30,
                            30);
        window.draw(name);

        for(int i = 0; i < env->homework.size(); i++){
            sf::Text id;
            id.setString(std::to_string(env->homework[i].contest_id));
            id.setCharacterSize(20);
            id.setFont(env->fonts["arial"]);
            id.setFillColor(sf::Color::Black);
            id.setPosition(50,
                             100 + i * 20);
            window.draw(id);

            sf::Text letter;
            id.setString(env->homework[i].letter);
            id.setCharacterSize(20);
            id.setFont(env->fonts["arial"]);
            id.setFillColor(sf::Color::Black);
            id.setPosition(120,
                           100 + i * 20);
            window.draw(id);

            sf::Text name;
            name.setString(env->homework[i].name);
            name.setCharacterSize(20);
            name.setFont(env->fonts["arial"]);
            name.setFillColor(sf::Color::Black);
            name.setPosition(160,
                             100 + i * 20);
            window.draw(name);

            sf::Text status;
            if(env->homework[i].status == SolveResult::OK){
                status.setString("OK");
                status.setFillColor(sf::Color::Green);
            }else if(env->homework[i].status == SolveResult::NO){
                status.setString("NO");
                status.setFillColor(sf::Color::Red);
            }else{
                status.setString("?");
                status.setFillColor(sf::Color::Blue);
            }
            status.setCharacterSize(20);
            status.setFont(env->fonts["arial"]);
            status.setPosition(500,
                             100 + i * 20);
            window.draw(status);
        }


        for(auto &p : UI_homework)
            window.draw(p.second);

    }

    window.display();
}

void Renderer::settings_update(){
    if(env->settings.is_fullscreen){
        screenSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
        window.create(sf::VideoMode(screenSize.x, screenSize.y), window_name, sf::Style::Fullscreen);
        initTexts();
        return;
    }
    if(env->settings.screen_resolution == ScreenResolution::qHDScreen)      screenSize = screenQHD;
    if(env->settings.screen_resolution == ScreenResolution::HDScreen)       screenSize = screenHD;
    if(env->settings.screen_resolution == ScreenResolution::HDPlusScreen)   screenSize = screenHDPlus;
    if(env->settings.screen_resolution == ScreenResolution::FHDScreen)      screenSize = screenFHD;

    window.create(sf::VideoMode(screenSize.x, screenSize.y), window_name, sf::Style::Titlebar | sf::Style::Close);
    initTexts();
}

void Renderer::make_defaultscreen(){

}

void Renderer::make_fullscreen(){

}

void Renderer::make_fullscreen_bordered(){
    screenSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    window.create(sf::VideoMode(screenSize.x, screenSize.y), window_name);
    initTexts();
}
