//
// Created by bruno on 12/03/2019.
//

#ifndef GENETICALGORITHM_GENETICS_H
#define GENETICALGORITHM_GENETICS_H

#include "Individual.h"
#include <fstream>

class Genetics {
    std::vector<Individual*> populationCurrent;
    std::vector<Individual*> populationNew;

    int degree;

    std::vector<std::vector<double>> positive;
    std::vector<std::vector<double>> negative;


public:
    Genetics(int degree);

    int initializePopulation();
    void evaluatePopulation();

    void mutation(int index);
    void crossOver(int indexA, int indexB);

    void orderElite(int cont);
    int selectElite();

    void selection(int index);

    int tournament();

    void readInputFile(const char * inputFile);


    void overwriteCurrent();
    void printCurrentPopulation();
    void printNewPopulation();
    void printDataSet();
    void printBestIndividual();
};


#endif //GENETICALGORITHM_GENETICS_H
