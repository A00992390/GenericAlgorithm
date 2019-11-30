//
// Created by Kang Wang on 11/30/2019.
//

#include "genetic_op.hpp"
/**
 * print tour
 * @param t
 */
void genetic_op::printTour(Tour& t){
    for (unsigned int i = 0; i <t.cities.size() ; ++i) {
        cout << t.cities[i].getName();
    }
    cout << "\tfitness: " << t.getFitness() << "\tdistance: " << get_tour_distance(t) << endl;
}

/**
 * populate the tours
 * @return vector<Tour>
 */
vector<Tour> genetic_op::populateTours(){
    vector<Tour> population;
    // random name and X Y
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Tour tour;
        for (int j = 0; j < CITIES_IN_TOUR; ++j) {
            // random x
            int x =  rand() % (MAP_BOUNDARY + 1);
            // random y
            int y =  rand() % (MAP_BOUNDARY + 1);
            // name A,B,C,D ...
            char name = (char)(j+65);
            // constructing city
            City city{name, x, y};
            // store city in tour
            tour.cities.push_back(city);
        }
        shuffle_cities(tour);
        tour.setFitness(determine_fitness(tour));
        population.push_back(tour);

    }
    return population;
}

/**
 * check if tour contain a city by name
 * @param t
 * @param c
 * @return
 */
bool genetic_op::contains_city(Tour& t, City& c){
    for (unsigned int i = 0; i < t.cities.size() ; ++i) {
        if(t.cities[i].getName() == c.getName()
            && t.cities[i].getX() == c.getX()
                && t.cities[i].getY() == c.getY()){
            return true;
        }
    }
    return false;
}

/**
 * get distance between cities
 * @param t
 * @return
 */
double genetic_op::get_distance_between_cities(Tour &t){
    double distance = 0;
    for (int i = 0; i < CITIES_IN_TOUR - 1; ++i){
        double x = pow(t.cities[i].getX() - t.cities[i+1].getX(),2);
        double y = pow(t.cities[i].getY() - t.cities[i+1].getY(),2);
        double cityDistance = sqrt(x + y);
        distance += cityDistance;
    }
    return distance;
}

/**
 * get tour distance for a tour
 * @param t
 * @return
 */
double genetic_op::get_tour_distance(Tour &t) {
    return get_distance_between_cities(t);
}

/**
 * creates a new Tour by patent Tours
 * @param t1
 * @param t2
 * @return
 */
Tour genetic_op::crossover(Tour& t1, Tour& t2){
    // child tour
    Tour childTour;

    int k = rand() % CITIES_IN_TOUR;

    for (int i = 0; i < k ; ++i) {
        childTour.cities.push_back(t1.cities[i]);
    }

    for (int i = 0; i < CITIES_IN_TOUR ; ++i) {
        if(k >= CITIES_IN_TOUR)
            break;

        if(!contains_city(childTour, t2.cities[i])){
            childTour.cities.push_back(t2.cities[i]);
            k++;
        }
    }
    return childTour;
}

/**
 * get crosses (a vector of tours)
 * @param population
 * @return
 */
vector<Tour> genetic_op::getCrosses(vector<Tour>& population){
    vector<Tour> crosses;
    for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE ; ++i) {
        // parent tour 1
        vector<Tour> parentGroup1 = getParentGroup(population);
        // parent tour 2
        vector<Tour> parentGroup2 = getParentGroup(population);
        // put first
        putEliteToFirst(parentGroup1);
        // put first
        putEliteToFirst(parentGroup2);

        Tour parent1 = parentGroup1[0];

        Tour parent2 = parentGroup2[0];

        // child tour
        Tour childTour = crossover(parent1, parent2);
        // calculate fitness
        childTour.setFitness(determine_fitness(childTour));
        crosses.push_back(childTour);
    }
    return crosses;
}

/**
 * determine fitness for a tour
 * @param t
 * @return
 */
double genetic_op::determine_fitness(Tour &t) {
    return scalar / get_tour_distance(t);
}

/**
 * get parent group
 * @param p
 * @return
 */
vector<Tour> genetic_op::getParentGroup(vector<Tour> &t){
    vector<Tour> parent_pool;
    for (int i = 0; i < PARENT_POOL_SIZE ; ++i) {
        int k= rand() % POPULATION_SIZE;
        parent_pool.push_back(t[k]);
    }

    return parent_pool;
}

/**
 * mutate population
 * @param p
 */
void genetic_op::mutate(vector<Tour>&p){
    // new double random
    default_random_engine generator(time(0));
    uniform_real_distribution<double> realDistribution(0,1);

    for (int i = 0; i < POPULATION_SIZE ; ++i) {
        for (int j = 0; j < CITIES_IN_TOUR ; ++j) {
            double rate=realDistribution(generator);
            if(rate <= MUTATION_RATE){
                if(j == CITIES_IN_TOUR - 1){
                    City temp = p[i].cities[j];
                    p[i].cities[j] = p[i].cities[0];
                    p[i].cities[0] = temp;
                }else{
                    City temp = p[i].cities[j];
                    p[i].cities[j] = p[i].cities[j+1];
                    p[i].cities[j+1] = temp;
                }
            }
        }
    }
}

/**
 * put elite to first
 * @param population
 * @param bestIndex
 */
void genetic_op::putEliteToFirst(vector<Tour> & t){
    int best = 0;
    for (unsigned int i = 0; i < t.size(); ++i) {
        if(t[i].getFitness() > t[best].getFitness()){
            best = i;
        }
    }

    if(best!= 0){
        Tour temp = t[0];
        t[0] = t[best];
        t[best] = temp;
    }
}

/**
 * shuffle cities
 * @param t
 */
void genetic_op::shuffle_cities(Tour &t){
    shuffle(begin(t.cities),end(t.cities),mt19937(random_device()()));
}

/**
 * perform genetic
 */
void genetic_op::perform(int n1, int n2){
    // setting
    CITIES_IN_TOUR = n1;
    POPULATION_SIZE = n2;

    srand(time(0));
    vector<Tour> population = populateTours();

    putEliteToFirst(population);
    double baseDistance= scalar / population[0].getFitness();
    double bestDistance = baseDistance;
    Tour baseTour = population[0];
    Tour bestTour = population[0];
    bool isAchieved = false;

    int i = 0;
    for (; i < ITERATIONS; ++i) {
        vector<Tour> crosses=getCrosses(population);

        for (int j = NUMBER_OF_ELITES; j < POPULATION_SIZE ; ++j) {
            population[j] = crosses[j - NUMBER_OF_ELITES];
        }

        mutate(population);

        for (int k = 0; k <POPULATION_SIZE ; ++k) {
            population[k].setFitness(determine_fitness(population[k]));
        }

        putEliteToFirst(population);

        double itDistance = scalar / population[0].getFitness();

        cout << "----------------------------------------" << endl;
        cout << "Iteration number: "<<i<<endl;
        cout << "Distance: "<<itDistance<<endl;
        if(itDistance<bestDistance){
            bestDistance=itDistance;
            bestTour=population[0];
        }
        cout<<"Best distance:  " << bestDistance<<endl;

        cout<<"Improvement Over Base:  "<< (baseDistance-bestDistance) / baseDistance<<endl;

        if((baseDistance-bestDistance) / baseDistance > improvement_factor){
            isAchieved = true;
            cout<<"Improvement Achieved Here"<<endl;
            break;
        }
    }
    cout << "----------------------------------------\n" << "Number of iterations " << i+1 << endl
        << "Base Distance: " << baseDistance << endl << "Best Distance: " << bestDistance << endl;

    if(isAchieved){
        cout<<"Improvement Achieved"<<endl;
    }else{
        cout<<"Improvement Not Achieved"<<endl;
    }

    cout<<"\n------------------- Base Route ------------------- "<<endl;
    printTour(baseTour);

    cout<<"\n------------------- Best Route -------------------"<<endl;
    printTour(bestTour);
}

