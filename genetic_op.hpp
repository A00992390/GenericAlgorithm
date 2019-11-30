//
// Created by KANG Wang on 11/30/2019.
// Perform Genetic algorithm to find the fitness and improvement of a list of Tours that have as list of Cities
//

#ifndef GENERICALGORITHM_GENETIC_OP_HPP
#define GENERICALGORITHM_GENETIC_OP_HPP

#include "Tour.hpp"
#include <ctime>
#include <random>
#include <algorithm>
#include <iostream>

class genetic_op {
private:
    // number of cities we are using in each simulation
    int CITIES_IN_TOUR;
    // number of candidate tours in our population
    int POPULATION_SIZE;
    // minimum number of times the algorithm should iterate
    const int ITERATIONS = 1000;
    // the largest legal coordinate
    const int MAP_BOUNDARY = 1000;
    // number of members randomly selected from the population
    const int PARENT_POOL_SIZE = 5;
    // rate of mutation
    const double MUTATION_RATE = 0.15;
    // num of ELITES
    const int NUMBER_OF_ELITES = 1;
    // percentage that indicates what percent the new elite fitness needs to improve
    const double improvement_factor = 0.15;
    //by scalar
    const double scalar = 10000.0;
private:
    /**
     * shuffle cities in tour
     * @param t
     */
    void shuffle_cities(Tour &t);

    /**
     * get distance between cities
     * @param t
     * @return
     */
    double get_distance_between_cities(Tour &t);

    /**
     * get tour distance for a tour
     * @param t
     * @return
     */
    double get_tour_distance(Tour &t);

    /**
     * populate the tours
     * @return vector<Tour>
     */
    vector<Tour> populateTours();

    /**
     * determine fitness for a tour
     * @param t
     * @return
     */
    double determine_fitness(Tour &t);

    /**
     * creates a new Tour by patent Tours
     * @param t1
     * @param t2
     * @return
     */
    Tour crossover(Tour& t1, Tour& t2);

    /**
     * mutate population
     * @param p
     */
    void mutate(vector<Tour>&p);

    /**
     * check if a tour contains a city by name
     * @param t
     * @param c
     * @return
     */
    bool contains_city(Tour &t, City &c);

    /**
    * get parent group
    * @param p
    * @return
    */
    vector<Tour> getParentGroup(vector<Tour> &p);

    /**
      * get crosses (a vector of tours)
      * @param population
      * @return
      */
    vector<Tour> getCrosses(vector<Tour> & population);

    /**
     * put elite to first
     * @param population
     * @param bestIndex
     */
    void putEliteToFirst(vector<Tour> & p);

    /**
     * print tour
     * @param t
     */
    void printTour(Tour&  t);
public:
    // default constructor
    genetic_op() = default;
    /**
     * perform algo
     */
    void perform(int n1, int n2);
};


#endif //GENERICALGORITHM_GENETIC_OP_HPP
