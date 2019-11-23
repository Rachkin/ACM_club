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
    std::string name;
    ScreenType  type;
    std::string speaker;
    std::string say;
    std::string background;
    std::vector<std::string> characters;
    Screen();
    Screen(std::string, ScreenType,
           std::string, std::string, std::string);
};

enum class RenderType {
    Lobby, Game, Pause
};

struct Environment {
    RenderType render_type;

    Screen screen;
    std::map<std::string, sf::Font>    fonts;
    std::map<std::string, std::string> strings;
    std::map<std::string, sf::Image>   images;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite>  sprites;
    std::map<std::string, Character>   characters;

    Environment();

private:
    void initTexts();
    void initSprites();
    void initCharacters();
};

#endif