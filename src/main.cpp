#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdint>

using namespace std;
using namespace sf;

sf::Vector2f screenSize(800.0f, 600.0f);

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
}

struct Screen {
    std::string name;
    std::string type;
    std::string child;
    std::string speaker;
    std::string say;
    std::string background;
    std::vector<std::string> characters;
    Screen() { }
    Screen(string name, string type, string child, string speaker, string say, string background) :
        name(name), type(type), child(child), speaker(speaker), say(say), background(background) { }
};

struct Character {
    std::string name;
    std::string fullname;
    Character() { }
    Character(string name, string fullname) :
        name(name), fullname(fullname) { }
};

sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y,32), "ACM club)");

std::map<string, Font> fonts;
std::map<string, string> strings;
std::map<string, Image> images;
std::map<string, Texture> textures;
std::map<string, Sprite> sprites;
std::map<string, Screen> screens;
std::map<string, Character> characters;

static void _readUntilSpace(const std::string& src, std::string& dst, int& pos) {
    while(pos < src.size() && src[pos] != ' ') dst.push_back(src[pos++]);
}

static void _readUntilEOL(const std::string& src, std::string& dst, int& pos) {
    while(pos < src.size()) dst.push_back(src[pos++]);
}

void initTexts() {
    fonts["arial"].loadFromFile("fonts/arial.ttf");
    std::vector<string> text_files = {"texts/ui.txt", "texts/dialogs.txt"};
    for(const auto& file : text_files) {
        std::ifstream in(file);
        std::string s;
        while (std::getline(in, s)) {
            if (s[0] == '#') continue; // python-like comments
            std::string name;
            int i = 0;
            _readUntilSpace(s, name, i); ++i;

            std::string text;
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

void initSprites() {
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

void initScreens(){
    std::ifstream in2("data/screens.txt"); // (!) './screens.txt' moved to './data'
    std::string s;
    while(std::getline(in2, s)) {
        if (s.empty() || s.front() == '#') continue; // skip empty lines and python-like commented lines
        int i = 0;

        std::string name, type, child, speaker, say, background;
        _readUntilSpace(s, name, i);       ++i;
        _readUntilSpace(s, type, i);       ++i;
        _readUntilSpace(s, child, i);      ++i;
        _readUntilSpace(s, speaker, i);    ++i;
        _readUntilSpace(s, say, i);        ++i;
        _readUntilSpace(s, background, i); ++i;
        screens[name] = Screen(name, type, child, speaker, say, background);
        string character;
        while(i < s.size()){
            _readUntilSpace(s, character, i); ++i;
            screens[name].characters.push_back(character);
            character = "";
        }
    }
}

void initCharacters() {
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

int main() {
    // Load data files
    initTexts();
    initSprites();
    initScreens();
    initCharacters();

    Screen current_screen = screens["main"];
    bool is_changed = 1;

    int64_t start_time        = timeSinceEpochMillisec();
    int64_t textstart_time    = timeSinceEpochMillisec();
    int64_t next_time         = timeSinceEpochMillisec();
    int64_t d_next            = 200;
    int text_speed = 50;
    int64_t string_shown      = 0;
    int64_t string_will_shown = 0;
    bool is_escaped = false;

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
        p.second.setFont(fonts["arial"]);
        p.second.setColor(sf::Color::Black);
    }

    for(auto &p : UI_dialog){
        p.second.setFont(fonts["arial"]);
        p.second.setColor(sf::Color::Black);
    }


    while(window.isOpen()) {
        sf::Event event;
        int64_t now_time = timeSinceEpochMillisec();

        while(window.pollEvent(event)) {

            string_will_shown = min((int64_t)(now_time - textstart_time) / text_speed, (int64_t)strings[current_screen.say].size());
            if(next_time <= now_time) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                    if (string_will_shown == (int) strings[current_screen.say].size()) {
                        if (current_screen.child == "-1") window.close();
                        current_screen = screens[current_screen.child];
                        textstart_time = now_time + d_next;
                    } else {
                        textstart_time = -10000000;
                    }
                    is_changed = 1;

                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                    is_escaped = 1 - is_escaped;
                    is_changed = 1;
                }
                next_time = now_time + d_next;
            }

        }
        string_will_shown = min((int64_t)(now_time - textstart_time) / text_speed, (int64_t)strings[current_screen.say].size());

        string_will_shown = max(0ll, string_will_shown);

        if(string_will_shown != string_shown){
            is_changed = 1;
            string_shown = string_will_shown;
        }

        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // hit test6
        if(is_escaped) {
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
                for(int i = 1; i <= 3; i++) {
                    if (UI_esc["menu_load" + to_string(i)].getGlobalBounds().contains(mouse)) {
                        ifstream in("saves/save" + to_string(i) + ".txt");
                        string s;
                        in >> s;
                        current_screen = screens[s];
                        is_escaped = 0;
                        is_changed = 1;
                    }
                }
                for(int i = 1; i <= 3; i++) {
                    if (UI_esc["menu_save" + to_string(i)].getGlobalBounds().contains(mouse)) {
                        ofstream out("saves/save" + to_string(i) + ".txt");
                        out << current_screen.name;
                        is_escaped = 0;
                        is_changed = 1;
                    }
                }
                if (UI_esc["menu_resume"].getGlobalBounds().contains(mouse)) {
                    is_escaped = 0;
                    is_changed = 1;
                }
            }
        }
        if(is_escaped == 0) {
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
                    is_escaped = 1;
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
            if(is_escaped == 0) {
                window.clear(Color::Black);

                Sprite background = sprites[current_screen.background];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    (screenSize.y-130) / background.getLocalBounds().height);

                window.draw(background);

                int i = 0;

                for(auto c : current_screen.characters){
                    Sprite character = sprites[c];
                    double k = 0;
                    if(c == current_screen.speaker) k = 0.8;
                        else k = 0.7;
                    character.setScale(screenSize.y / character.getLocalBounds().height * k,
                                       screenSize.y / character.getLocalBounds().height * k);
                    character.setPosition((i+1) * screenSize.x / (current_screen.characters.size()+1) - character.getGlobalBounds().width/2,
                            screenSize.y/2 - character.getGlobalBounds().height/2);
                    window.draw(character);
                    i++;
                }

                Sprite dialog = sprites["dialog"];
                dialog.setScale(screenSize.x / dialog.getLocalBounds().width,
                                (130) / dialog.getLocalBounds().height);
                dialog.setPosition(0, screenSize.y - 130);

                window.draw(dialog);

                Text speaker;
                speaker.setString(characters[current_screen.speaker].fullname);
                speaker.setCharacterSize(30);
                speaker.setFont(fonts["arial"]);
                speaker.setColor(sf::Color::Black);
                speaker.setPosition(100,
                                    window.getSize().y - 120);
                window.draw(speaker);

                Text say;
                say.setString(strings[current_screen.say].substr(0, string_shown));
                say.setCharacterSize(20);
                say.setFont(fonts["arial"]);
                say.setColor(Color::Black);
                say.setPosition(120,
                                window.getSize().y - 80); // - say.getGlobalBounds().height/2
                window.draw(say);

                for(auto &p : UI_dialog) {
                    window.draw(p.second);
                }

                window.display();
                is_changed = 0;
            } if(is_escaped == 1) {
                window.clear(Color::Black);

                Sprite background = sprites["escmenu"];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    screenSize.y / background.getLocalBounds().height);

                window.draw(background);

                for(int i = 1; i <= 3; i++) {

                    ifstream in("saves/save" + to_string(i) + ".txt");
                    string s;
                    in >> s;
                    UI_esc["menu_load" + to_string(i)].setString("load" + to_string(i) + "(" + s + ")");
                }

                for(auto &p : UI_esc) {
                    window.draw(p.second);
                }

                window.display();
                is_changed = 0;
            }
        }

    }
    return 0;
}