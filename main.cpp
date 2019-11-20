#include <SFML/Graphics.hpp>
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

struct Screen{
    string name;
    string type;
    string child;
    string speaker;
    string say;
    string background;
    Screen(){}
    Screen(string name, string type, string child, string speaker, string say, string background):
    name(name),type(type),child(child),speaker(speaker),say(say),background(background){}
};

struct Character{
    string name;
    string fio;
    Character(){}
    Character(string name, string fio):name(name),fio(fio){}
};

RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y,32),"ACM club)");

map<string, Font> fonts;
map<string, string> strings;

map<string, Image> images;
map<string, Texture> textures;
map<string, Sprite> sprites;

map<string, Screen> screens;

map<string, Character> characters;

void initTexts(){

    fonts["arial"].loadFromFile("fonts/arial.ttf");

    vector < string > text_files = {"texts/ui.txt"};

    for(auto file : text_files) {
        ifstream in(file);
        string s;
        while (getline(in, s)) {
            if (s[0] == '/') continue;
            string name;
            int i = 0;
            for (; s[i] != ' ' && i < s.size(); i++) {
                name += s[i];
            }
            i++;
            /////////
            string text;
            for(; i < s.size(); i++){
                if(s[i] == '\\' && s[i+1] == 'n') {text += '\n'; i++;}
                else text += s[i];
            }

            strings[name] = text;
           // cout << text;
        }
    }



}

void initSprites(){

    ifstream in("images.txt");
    string s;
    while(getline(in, s)){
        int i = 0;
        string name;
        for(; s[i] != ' '; i++) name += s[i];
        i++;
        string link;
        for(; i < s.size(); i++) link += s[i];
        images[name].loadFromFile("images/" + link);

        textures[name].loadFromImage(images[name]);

        sprites[name].setTexture(textures[name]);
    }

}

void initScreens(){
    ifstream in2("screens.txt");
    string s;
    while(getline(in2, s)){
        if (s[0] == '/') continue;
        int i = 0;
        string name;
        for(; s[i] != ' ' && i < s.size(); i++){
            name += s[i];
        }
        i++;
        ///////////////
        string type;
        for(; s[i] != ' ' && i < s.size(); i++){
            type += s[i];
        }
        i++;
        ///////////////
        string child;
        for(; s[i] != ' ' && i < s.size(); i++){
            child += s[i];
        }
        i++;
        ///////////////
        string speaker;
        for(; s[i] != ' ' && i < s.size(); i++){
            speaker += s[i];
        }
        i++;
        ///////////////
        string say;
        for(; s[i] != ' ' && i < s.size(); i++){
            say += s[i];
        }
        i++;
        string background;
        for(; s[i] != ' ' && i < s.size(); i++){
            background += s[i];
        }
        i++;
        screens[name] = Screen(name, type, child, speaker, say, background);
        //cout << name << " " << type << endl;
    }
}

void initCharacters(){
    ifstream in("characters.txt");
    string s;
    while(getline(in, s)){
        if (s[0] == '/') continue;
        int i = 0;
        string name;
        for(; s[i] != ' ' && i < s.size(); i++){
            name += s[i];
        }
        i++;
        string fio;
        for(; i < s.size(); i++){
            fio += s[i];
        }
        i++;
        characters[name] = Character(name, fio);
        cout << fio;
    }
}

int main() {

    initTexts();
    initSprites();
    initScreens();
    initCharacters();

    Screen current_screen = screens["main"];

    bool is_changed = 1;

    int64_t start_time = timeSinceEpochMillisec();

    int64_t textstart_time = timeSinceEpochMillisec();

    int64_t next_time = timeSinceEpochMillisec();
    int64_t d_next = 200;

    int64_t string_shown = 0;

    int64_t string_will_shown = 0;

    bool is_escaped = 0;

    map < string, Text > UI_esc, UI_dialog;

    UI_esc["menu_label"].setString("MENU");
    UI_esc["menu_label"].setCharacterSize(40);
    UI_esc["menu_label"].setPosition(100,70);


    UI_esc["menu_resume"].setString("resume");
    UI_esc["menu_resume"].setCharacterSize(30);
    UI_esc["menu_resume"].setPosition(120,120);

    UI_esc["menu_load1"].setString("load1");
    UI_esc["menu_load1"].setCharacterSize(30);
    UI_esc["menu_load1"].setPosition(120,150);

    UI_esc["menu_load2"].setString("load2");
    UI_esc["menu_load2"].setCharacterSize(30);
    UI_esc["menu_load2"].setPosition(120,180);

    UI_esc["menu_load3"].setString("load3");
    UI_esc["menu_load3"].setCharacterSize(30);
    UI_esc["menu_load3"].setPosition(120,210);

    UI_esc["menu_save1"].setString("save1");
    UI_esc["menu_save1"].setCharacterSize(30);
    UI_esc["menu_save1"].setPosition(300,150);

    UI_esc["menu_save2"].setString("save2");
    UI_esc["menu_save2"].setCharacterSize(30);
    UI_esc["menu_save2"].setPosition(300,180);

    UI_esc["menu_save3"].setString("save3");
    UI_esc["menu_save3"].setCharacterSize(30);
    UI_esc["menu_save3"].setPosition(300,210);

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


    while(window.isOpen()){
        sf::Event event;
        int64_t now_time = timeSinceEpochMillisec();

        while(window.pollEvent(event)) {

            string_will_shown = min((int64_t)(now_time - textstart_time) / 100, (int64_t)strings[current_screen.say].size());
            if(next_time <= now_time) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                    if (string_will_shown == (int) strings[current_screen.say].size()) {
                        if (current_screen.child == "-1") window.close();
                        current_screen = screens[current_screen.child];
                        textstart_time = now_time + 100;
                    } else {
                     //   string_will_shown = (int) strings[current_screen.say].size();
                        textstart_time = -10000000;
                    }
                    is_changed = 1;
                    cout << string_will_shown << endl;
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                    is_escaped = 1 - is_escaped;
                    is_changed = 1;
                }
                next_time = now_time + d_next;
            }

        }
        string_will_shown = min((int64_t)(now_time - textstart_time) / 100, (int64_t)strings[current_screen.say].size());

        if(string_will_shown != string_shown){
            is_changed = 1;
            string_shown = string_will_shown;
        }

        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // hit test
        if(is_escaped) {
            for(auto &p : UI_esc) {
                sf::FloatRect bounds = p.second.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    if (p.second.getColor() == Color::Black) is_changed = 1;
                    p.second.setColor(Color::Red);
                }
                else {
                    if (p.second.getColor() == Color::Red) is_changed = 1;
                    p.second.setColor(Color::Black);
                }

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // transform the mouse position from window coordinates to world coordinates
                if (UI_esc["menu_exit"].getGlobalBounds().contains(mouse)) {
                    window.close();
                }
                if (UI_esc["menu_load1"].getGlobalBounds().contains(mouse)) {
                    ifstream in("save.txt");
                    string s;
                    in >> s;
                    current_screen = screens[s];
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (UI_esc["menu_load2"].getGlobalBounds().contains(mouse)) {
                    ifstream in("save2.txt");
                    string s;
                    in >> s;
                    current_screen = screens[s];
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (UI_esc["menu_load3"].getGlobalBounds().contains(mouse)) {
                    ifstream in("save3.txt");
                    string s;
                    in >> s;
                    current_screen = screens[s];
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (UI_esc["menu_save1"].getGlobalBounds().contains(mouse)) {
                    ofstream out("save.txt");
                    out << current_screen.name;
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (UI_esc["menu_save2"].getGlobalBounds().contains(mouse)) {
                    ofstream out("save2.txt");
                    out << current_screen.name;
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (UI_esc["menu_save3"].getGlobalBounds().contains(mouse)) {
                    ofstream out("save3.txt");
                    out << current_screen.name;
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (UI_esc["menu_resume"].getGlobalBounds().contains(mouse)) {
                    is_escaped = 0;
                    is_changed = 1;
                }

            }
        }
        if(is_escaped == 0){

            for(auto &p : UI_dialog) {
                sf::FloatRect bounds = p.second.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    if (p.second.getColor() == Color::Black) is_changed = 1;
                    p.second.setColor(Color::Red);
                }
                else {
                    if (p.second.getColor() == Color::Red) is_changed = 1;
                    p.second.setColor(Color::Black);
                }

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (UI_dialog["menu_botton"].getGlobalBounds().contains(mouse)) {
                    is_escaped = 1;
                    is_changed = 1;
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


                Sprite dialog = sprites["dialog"];
                dialog.setScale(screenSize.x / dialog.getLocalBounds().width,
                                (130) / dialog.getLocalBounds().height);
                dialog.setPosition(0, screenSize.y - 130);

                window.draw(dialog);
                // sprites["backgrounds/back"].setScale(screenSize.x / sprites["backgrounds/back"].getLocalBounds().width, screenSize.y / sprites["backgrounds/back"].getLocalBounds().height);
                //cout << current_screen.name;
                Text speaker;
                speaker.setString(characters[current_screen.speaker].fio);
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
            } else {
                window.clear(Color::Black);

                Sprite background = sprites["escmenu"];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    screenSize.y / background.getLocalBounds().height);

                window.draw(background);

                ifstream in("save.txt");
                string s;
                in >> s;
                UI_esc["menu_load1"].setString("load1(" + s + ")");

                ifstream in2("save2.txt");
                string s2;
                in2 >> s2;
                UI_esc["menu_load2"].setString("load2(" + s2 + ")");

                ifstream in3("save3.txt");
                string s3;
                in3 >> s3;
                UI_esc["menu_load3"].setString("load3(" + s3 + ")");

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