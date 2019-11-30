//
// Created by Kang Wang on 11/28/2019.
//

#include "City.hpp"
// constructing a city with name, and x y coordinates
City::City(char name, int x, int y): name{name} {
    // restricting x
    if(x >= 0 && x <= 1000) {
        this->x = x;
    } else {
        throw "x coord has to be within 0 - 1000";
    }
    // restricting y
    if(y >= 0 && y <= 1000) {
        this->y = y;
    } else {
        throw "y coord has to be within 0 - 1000";
    }
}
// name getter
char City::getName() {return name;}
// x coord getter
int City::getX() {return x;}
// y coord getter
int City::getY() {return y;}
