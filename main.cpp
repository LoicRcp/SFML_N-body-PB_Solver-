#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

struct Point {
    double x;
    double y;
    double velx;
    double vely;
};

void movePoints(Point &p, bool MOVE_POINTS){
    p.x += p.velx * MOVE_POINTS;
    p.y += p.vely * MOVE_POINTS;
}

void handleBorders(Point &p, int width, int height){
    if (p.x > width || p.x < 0) p.velx *=-1;
    if (p.y > height || p.y < 0) p.vely *=-1;
}

int main() {
    int WIDTH = 800;
    int HEIGHT = 600;


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");

    int nbPoints = 30000;
    Point* points[nbPoints];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1, 1);

    for (int i = 0; i<nbPoints; i++){
        auto* p = static_cast<Point *>(malloc(sizeof(Point)));

        double r = 100 * sqrt(std::abs(dis(gen)));
        double theta = std::abs(dis(gen)) * 2 * M_PI;

        p->x = WIDTH/2.0 + r * cos(theta);
        p->y = HEIGHT/2.0 + r * sin(theta);

        p->velx = dis(gen);
        p->vely = dis(gen);
        points[i] = p;
    }

    bool MOVE_POINTS = false;


    sf::CircleShape shape(1.f);
    shape.setFillColor(sf::Color(100, 216, 255, 200));
    while (window.isOpen()){
        window.clear(sf::Color::Black);

        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    MOVE_POINTS = !MOVE_POINTS;
                }
            }
        }

        for (int i = 0; i < nbPoints; i++){
            movePoints(*points[i], MOVE_POINTS);
            handleBorders(*points[i], WIDTH, HEIGHT);
            shape.setPosition(points[i]->x, points[i]->y);
            window.draw(shape);
        }





        window.display();
    }
    return 0;
}
