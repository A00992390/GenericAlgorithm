#include "genetic_op.hpp"

// main class for Genetic Algorithm

int main() {
    int num_cities, population_size;
    genetic_op genetic_algo;
    cout << "How many cities in the tour? ";
    cin >> num_cities;
    cout << "\nHow many candidate tours? ";
    cin >> population_size;
    // perform operation
    genetic_algo.perform(num_cities, population_size);
    return 0;
}