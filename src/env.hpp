#ifndef __ENV_H__
#define __ENV_H__

#include <string>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

struct Character {
    std::string name;
    std::string fullname;
    Character();
    Character(std::string, std::string);
};

enum class ScreenType {
    Monolog, Variant
};

struct Screen {
    std::string name = "Pupa and Lupa";
    ScreenType  type;
    std::string speaker;
    std::string say;
    std::string background;
    std::vector<std::string> characters;

    std::string description;
    std::string input;
    std::string output;

    std::string text;
    int cursor_pos = 0;

    Screen();
    Screen(std::string, ScreenType,
           std::string, std::string, std::string);
};

enum class RenderType {
    Lobby, Game, Pause, Acmp, Settings
};

struct Environment {
    RenderType render_type;
    RenderType pre_render_type;

    Screen screen;
    std::map<std::string, sf::Font>    fonts;
    std::map<std::string, std::string> strings;
    std::map<std::string, sf::Image>   images;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite>  sprites;
    std::map<std::string, Character>   characters;
    int64_t string_shown;

    Environment();
    Environment(RenderType);

private:
    void initTexts();
    void initSprites();
    void initCharacters();
};

#endif
