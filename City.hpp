//
// Created by Kang Wang on 11/28/2019.
// City class that has a name(char) and x,y coords
//

#ifndef GENERICALGORITHM_CITY_HPP
#define GENERICALGORITHM_CITY_HPP

#include <iostream>
using namespace std;
class City {
private:
    char name;
    int x, y;
public:
    // default constructor
    City() = default;
    // constructing a city with name, and x y coordinates
    City(char name, int x, int y);
    //getters for name
    char getName();
    //getters for x
    int getX();
    //getters for y
    int getY();
};


#endif //GENERICALGORITHM_CITY_HPP
