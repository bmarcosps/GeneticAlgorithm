//
// Created by bruno on 07/03/2019.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H


#include "random"
#include "constants.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "bitset"
#include "Bitwise.h"

class Individual {
private:
    std::vector<int> chromossome;
    int size;
    double fitness;

public:

    virtual ~Individual();

    Individual(int ArgSize);
    Individual(const Individual& i);

    Individual& operator =(const Individual& i);

    void setFitness(double fitness) {
        Individual::fitness = fitness;
    }

    double getFitness() const {
        return fitness;
    }

    const std::vector<int> &getChromossome() const {
        return chromossome;
    }

    void setChromossome(int index, int value) {
        chromossome[index] = value;
    }

    int initializeChromossomeRandom();
    int initializeChromossomeRange(int lower, int upper);
    int initializeChromossomeRangeFloat(float lower, float upper);

    void initializeChromossomeParameters(std::vector<int> coef);

    void mutate();
    void crossover(Individual* ind);

    void evaluateIndividual(std::vector<double> point, char type);

    void printIndividual();

    void copy(Individual *i);

};


#endif //GENETICALGORITHM_INDIVIDUAL_H
