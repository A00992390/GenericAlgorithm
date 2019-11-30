//
// Created by Kang Wang on 11/30/2019.
// Tour class that has a list of cities and fitness
//

#ifndef GENERICALGORITHM_TOUR_HPP
#define GENERICALGORITHM_TOUR_HPP

#include "City.hpp"
#include <vector>
class Tour {
private:
    double fitness;     // fitness of the tour
public:
    Tour() = default;
    vector<City> cities;    // list of cities in the tour
    // get fitness
    double getFitness();
    // set fitness
    void setFitness(double f);
};


#endif //GENERICALGORITHM_TOUR_HPP
