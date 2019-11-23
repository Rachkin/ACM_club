#include "env.hpp"

#include <fstream>

Screen::Screen() { }
Screen::Screen(std::string name, ScreenType type, 
    std::string speaker, std::string say, std::string background) :
    name(name), type(type), speaker(speaker), say(say), background(background) { }

Character::Character() { }
Character::Character(std::string name, std::string fullname) :
    name(name), fullname(fullname) { }

static void _readUntilSpace(const std::string& src, std::string& dst, int& pos) {
    while(pos < src.size() && src[pos] != ' ') dst.push_back(src[pos++]);
}

static void _readUntilEOL(const std::string& src, std::string& dst, int& pos) {
    while(pos < src.size()) dst.push_back(src[pos++]);
}

Environment::Environment() : render_type(RenderType::Game) {
    initTexts(), initSprites(), initCharacters();
}

void Environment::initTexts() {
    using namespace std;
    fonts["arial"].loadFromFile("fonts/arial.ttf");
    vector<string> text_files = {"texts/ui.txt", "texts/dialogs.txt"};
    for(const auto& file : text_files) {
        ifstream in(file);
        string s;
        while (getline(in, s)) {
            if (s[0] == '#') continue; // python-like comments
            string name;
            int i = 0;
            _readUntilSpace(s, name, i); ++i;

            string text;
            for(; i < s.size(); i++) {
                if(s[i] == '\\') { 
                    if(i + 1 < s.size() && s[i] == 'n')
                        text.push_back('\n'); i++;
                }
                else text.push_back(s[i]);
            }

            strings[name] = text;
        }
    }
}

void Environment::initSprites() {
    std::ifstream in("data/images.txt"); // (!) './images.txt' moved to './data'
    std::string s;
    while(std::getline(in, s)) {
        if(s.empty() || s.front() == '#') continue; // skip empty lines and python-like commented lines
        int i = 0;
        std::string name, link;
        _readUntilSpace(s, name, i); ++i;
        _readUntilSpace(s, link, i);

        images[name].loadFromFile("images/" + link);
        textures[name].loadFromImage(images[name]);
        sprites[name].setTexture(textures[name]);
    }
}

void Environment::initCharacters() {
    std::ifstream in("data/characters.txt"); // (!) './characters.txt' moved to './data'
    std::string s;
    while(std::getline(in, s)) {
        if (s.empty() || s.front() == '#') continue; // skip empty lines and python-like commented lines
        int i = 0;
        std::string name, fullname;
        _readUntilSpace(s, name, i);   ++i;
        _readUntilEOL(s, fullname, i); ++i;
        characters[name] = Character(name, fullname);
    }
}