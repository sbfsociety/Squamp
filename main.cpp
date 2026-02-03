#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>
bool ground = true;
using namespace std;


float dt;


float val = 0;
bool release = false;

struct Vec2{
    float x, y;
};

class Player{
private:
    bool alive = true;
    bool onGround = false;
    bool jump = false;
    int state = 0; // 0 - no, 1 - Left, 2 - Right

    float add;

    Vec2 save;

    Vec2 vel = {0.f, 0.f};
    Vec2 pos;
    Vec2 gravity = {0.f, 2.f};
    bool space = false;
public:
    Player(Vec2 _p) : pos(_p), save(_p){};

    Vec2 old = {pos.x, pos.y};

    Vec2 newPos = {pos.x, pos.y};

    void Move(){
        space = false;
        state = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){state = 1; pos.x -= 5.f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){state = 2; pos.x += 5.f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround){if (add < 1000) add++; space = true;}

        if (release && onGround) {
            vel.y = -0.1 * ::val; // negative = up
            add = 0;
            ::val = 0;
            release = false;
            onGround = false;
        }
    }

    void Update(){
        old = {pos.x, pos.y}; // save BEFORE anything moves

        Move();

        if (!onGround) {
            vel.y += gravity.y;  // gravity pulls down (positive y)
            pos.y += vel.y;      // move by velocity
        }

        if (pos.y > 800.f) { pos = {save.x, save.y}; vel = {0.f, 0.f}; }
    }

    void Draw(sf::RenderWindow& window){
        Vec2 playerSize = {20.f, 30.f};
        float small = 10;
        sf::ConvexShape player;
        player.setPointCount(4);
        if (!space) {
            player.setPoint(0, sf::Vector2f(pos.x - playerSize.x, pos.y - playerSize.y));
            player.setPoint(1, sf::Vector2f(pos.x, pos.y - playerSize.y));
        }
        else{
            player.setPoint(0, sf::Vector2f(pos.x - playerSize.x, pos.y - playerSize.y + small));
            player.setPoint(1, sf::Vector2f(pos.x, pos.y - playerSize.y + small));
        }
        player.setPoint(2, sf::Vector2f(pos.x, pos.y));
        player.setPoint(3, sf::Vector2f(pos.x - playerSize.x, pos.y));
        player.setFillColor(sf::Color::Red);
        player.setOutlineColor(sf::Color::Black);
        player.setOutlineThickness(2.f);
        window.draw(player);
    }





    float getAdd() const {return add;}

    bool Space() const {return space;}

    bool Ground() const {return onGround;}

    void Grounded(bool a){onGround = a;}

    int State() const {return state;}

    Vec2 get() const {return pos;}

    void set(Vec2 _p){pos = {_p.x, _p.y};}



};

class Line {
public:
    Vec2 begin, end;
    bool vertical = false;
    bool horizontal = false;
    bool diagonal = false;
    bool col = false;

    Line(Vec2 _b, Vec2 _e) : begin(_b), end(_e) {
        if (_b.x == _e.x){vertical = true; cout << "Vertical";}
        else if (_b.y == _e.y){horizontal = true; cout <<"Horizontal";}
        else {diagonal = true; cout << "Diagonal";}
    }

    void Collide(Player& player) {
        if (horizontal) {
            if ((player.old.y < begin.y && player.get().y > end.y) && (player.get().x > begin.x && player.get().x < end.x)) {
                player.Grounded(true);
                player.set({player.get().x, begin.y - 2});
                // std::cout << "Collided" << std::endl;
                // col = true;
            }
        }
        if (vertical){}
    }

    void floatato(Player& player) {
        if (!col){player.Grounded(false);}
    }


    void Draw(sf::RenderWindow& window) {
        sf::ConvexShape line;
        float width = 4;
        line.setPointCount(4);
        line.setPoint(0, {begin.x, begin.y + width});
        line.setPoint(1, {end.x, begin.y + width});
        line.setPoint(2, {end.x, end.y});
        line.setPoint(3, {begin.x, end.y});
        line.setFillColor(sf::Color::Red);
        line.setOutlineColor(sf::Color::Black);
        line.setOutlineThickness(2.f);
        window.draw(line);
    }


};

void Lines(sf::RenderWindow& window, vector<Line>& lines, Player& player) {
    // player.Grounded(false);
    int positive = 0;
    for (auto& line : lines) {
        line.Collide(player);
        line.Draw(window);
        // if (line.col){positive++;}
    }
    // if (positive != 0) {player.Grounded(false);}
}



int main(){
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Jump king");
    sf::Clock clock;
    window.setFramerateLimit(60);
    Player player({475.f, 400.f});
    //window.setFramerateLimit(60);


    //Line line1({100, 700}, {800, 700});

    vector<Line> lines;
    lines.push_back(Line({100, 700}, {800, 700}));




    while(window.isOpen()) {
        //sf::Time elapsed = clock.restart();
        ::dt = clock.restart().asSeconds();



        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                if (keyReleased->code == sf::Keyboard::Key::Space && player.Space() && player.Ground()) {
                    ::val = player.getAdd();
                    cout << player.getAdd() << endl;
                    ::release = true;
                }

            }
        }

        window.clear(sf::Color::White);


        //player.Move();
        player.Update();
        Lines(window, lines, player);
        player.Draw(window);

        window.display();
    }

    return 0;
}
