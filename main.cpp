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

    int string_shown = 0;

    int string_will_shown = 0;

    bool is_escaped = 0;

    Text menu_label;
    menu_label.setString("MENU");
    menu_label.setCharacterSize(40);
    menu_label.setFont(fonts["arial"]);
    menu_label.setColor(sf::Color::Black);
    menu_label.setPosition(100,70);

    Text menu_exit;
    menu_exit.setString("exit");
    menu_exit.setCharacterSize(30);
    menu_exit.setFont(fonts["arial"]);
    menu_exit.setColor(sf::Color::Black);
    menu_exit.setPosition(120,120);

    Text menu_load;
    menu_load.setString("load");
    menu_load.setCharacterSize(30);
    menu_load.setFont(fonts["arial"]);
    menu_load.setColor(sf::Color::Black);
    menu_load.setPosition(120,150);

    Text menu_save;
    menu_save.setString("save");
    menu_save.setCharacterSize(30);
    menu_save.setFont(fonts["arial"]);
    menu_save.setColor(sf::Color::Black);
    menu_save.setPosition(120,180);

    while(window.isOpen()){
        sf::Event event;
        int64_t now_time = timeSinceEpochMillisec();

        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed){
                window.close();
            }

            if ((current_screen.type == "monolog") && (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){
                if(current_screen.child == "-1") window.close();
                current_screen = screens[current_screen.child];
                is_changed = 1;
                textstart_time = now_time + 100;
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
                is_escaped = 1 - is_escaped;
                is_changed = 1;
            }

        }

        string_will_shown = min((int)(now_time - textstart_time) / 100, (int)strings[current_screen.say].size());
        if(string_will_shown != string_shown){
            is_changed = 1;
            string_shown = string_will_shown;
        }

        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));


        // hit test
        if(is_escaped) {
            sf::FloatRect bounds_exit = menu_exit.getGlobalBounds();
            if (bounds_exit.contains(mouse)){ if(menu_exit.getColor() == Color::Black) is_changed = 1; menu_exit.setColor(Color::Red);}
            else { if(menu_exit.getColor() == Color::Red) is_changed = 1; menu_exit.setColor(Color::Black);}

            sf::FloatRect bounds_load = menu_load.getGlobalBounds();
            if (bounds_load.contains(mouse)){ if(menu_load.getColor() == Color::Black) is_changed = 1; menu_load.setColor(Color::Red);}
            else { if(menu_load.getColor() == Color::Red) is_changed = 1; menu_load.setColor(Color::Black);}

            sf::FloatRect bounds_save = menu_save.getGlobalBounds();
            if (bounds_save.contains(mouse)){ if(menu_save.getColor() == Color::Black) is_changed = 1; menu_save.setColor(Color::Red);}
            else { if(menu_save.getColor() == Color::Red) is_changed = 1; menu_save.setColor(Color::Black);}
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // transform the mouse position from window coordinates to world coordinates
                if (bounds_exit.contains(mouse)) {
                    window.close();
                }
                if (bounds_load.contains(mouse)) {
                    ifstream in("save.txt");
                    string s;
                    in >> s;
                    current_screen = screens[s];
                    is_escaped = 0;
                    is_changed = 1;
                }
                if (bounds_save.contains(mouse)) {
                    ofstream out("save.txt");
                    out << current_screen.name;
                    is_escaped = 0;
                    is_changed = 1;
                }
            }
        }

        if(is_changed) {
            if(is_escaped == 0) {
                window.clear(Color::Black);

                Sprite background = sprites[current_screen.background];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    screenSize.y / background.getLocalBounds().height);

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


                window.display();
                is_changed = 0;
            } else {
                window.clear(Color::Black);

                Sprite background = sprites["escmenu"];
                background.setScale(screenSize.x / background.getLocalBounds().width,
                                    screenSize.y / background.getLocalBounds().height);

                window.draw(background);


                window.draw(menu_label);
                window.draw(menu_exit);
                window.draw(menu_load);
                window.draw(menu_save);

                window.display();
                is_changed = 0;
            }
        }

    }
    return 0;
}