#ifndef __ENV_H__
#define __ENV_H__

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


static void __make_error(const std::string& s){
    std::cout << "ERROR: " << s << std::endl;
}

struct Character {
    std::string name;
    std::string fullname;
    Character();
    Character(std::string, std::string);
};

enum class ScreenType {
    Monolog, Variant
};

struct CodeForcesInfo{
    std::string username = "vovasher";
//  std::string password;
};

enum class SolveResult {
    UNDEFINED, OK, NO
};

struct Task{
    int contest_id;
    std::string letter;
    std::string name;
    SolveResult status;
    Task(int contest_id, std::string letter, std::string name):contest_id(contest_id),letter(letter),name(name){}
};

struct Screen {
    std::string name = "Pupa and Lupa";
    ScreenType  type;
    std::string speaker;
    std::string say;
    std::string background;
    std::vector<std::string> characters;

    std::string text;
    int cursor_pos = 0;

    Screen();
    Screen(std::string, ScreenType,
           std::string, std::string, std::string);
};

enum class RenderType {
    Lobby, Game, Pause, Homework, Settings
};

enum class ScreenResolution {
    qHDScreen, HDScreen, HDPlusScreen, FHDScreen
};

struct Settings {
    ScreenResolution screen_resolution = ScreenResolution::qHDScreen;
    bool is_fullscreen = 0;
};

struct Environment {
    RenderType render_type;
    RenderType pre_pause_render_type;
    RenderType pre_settings_render_type;

    Settings settings;
    Settings pre_settings;

    CodeForcesInfo cf_info;
    std::vector<Task> homework;
    Screen screen;

    std::map<std::string, sf::Font>    fonts;
    std::map<std::string, std::string> strings;
    std::map<std::string, sf::Image>   images;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite>  sprites;
    std::map<std::string, Character>   characters;
    int64_t string_shown;

    sf::Music music;

    Environment();
    Environment(RenderType);

private:
    void initTexts();
    void initSprites();
    void initCharacters();
};

#endif
