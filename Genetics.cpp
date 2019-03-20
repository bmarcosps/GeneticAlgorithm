//
// Created by bruno on 12/03/2019.
//

#include "Genetics.h"

Genetics::Genetics(int degree)
{
    populationCurrent.resize(NUM_INDIV);
    populationNew.resize(NUM_INDIV);

    this->degree = degree;
}

int Genetics::initializePopulation()
{
    int i;
    for(i = 0; i < populationCurrent.size(); i++)
    {
        populationCurrent[i] = new Individual(degree);
        populationNew[i] = new Individual(degree);

        populationCurrent[i]->initializeChromossomeRangeFloat(-10,10);
    }
}

void Genetics::printCurrentPopulation()
{
    int i;
    for(i = 0; i < populationCurrent.size(); i++)
    {
        std::cout << "[" << std::setw(3) << i << "] ";
        populationCurrent[i]->printIndividual();
    }
}

void Genetics::printNewPopulation()
{
    int i;
    for(i = 0; i < populationNew.size(); i++)
    {
        std::cout << "[" << std::setw(3) << i << "] ";
        populationNew[i]->printIndividual();
    }
}

void Genetics::readInputFile(const char * inputFile)
{
    std::fstream dataFile;
    dataFile.open(inputFile, std::ios::in);

    int numData;
    dataFile >> numData;

    int i;
    char label;
    double x, y;
    int posCount, negCount;
    posCount = 0;
    negCount = 0;

    for(i = 0; i < numData; i++)
    {
        dataFile >> label;
        dataFile >> x;
        dataFile >> y;
        //std::cout << i << " "<< x << " " << y << std::endl;
        if(label == 'P')
        {
            //std::cout << "Readind positive..." << std::endl;
            positive.emplace_back(std::vector<double>());
            positive[posCount].emplace_back(x);
            positive[posCount].emplace_back(y);
            posCount++;
        }
        else if (label == 'N')
        {
            //std::cout << "Readind negative..." << std::endl;
            negative.emplace_back(std::vector<double>());
            negative[negCount].emplace_back(x);
            negative[negCount].emplace_back(y);
            negCount++;
        }
    }
}

void Genetics::printDataSet()
{
    std::cout << "Positive set: "<< std::endl;
    for(int j = 0; j < positive.size(); j++){
        for(int k = 0; k < positive[j].size(); k++){
            std::cout << positive[j][k] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Negative set: "<< std::endl;
    for(int j = 0; j < negative.size(); j++){
        for(int k = 0; k < negative[j].size(); k++){
            std::cout << negative[j][k] << " ";
        }
        std::cout << std::endl;
    }
}

void Genetics::evaluatePopulation()
{
    double x, y;
    double f;

    int i, j;
    for(i = 0; i < populationCurrent.size(); i++)
    {
        populationCurrent[i]->setFitness(0);
        for(j = 0; j < positive.size(); j++)
        {
            populationCurrent[i]->evaluateIndividual(positive[j], 'P');
        }
        //std::cout << j << std::endl;
        for(j = 0; j < negative.size(); j++)
        {
            populationCurrent[i]->evaluateIndividual(negative[j], 'N');
        }
    }
}

void Genetics::mutation(int index)
{
    populationNew[index]->mutate();
}

void Genetics::crossOver(int indexA, int indexB)
{
    populationNew[indexA]->crossover(populationNew[indexB]);
}

void Genetics::orderElite(int cont)
{
    //Individual auxIndividual(this->degree);
    int i, j;
    int indexBest;

    for(i = 0; i < cont; i++)
    {
        indexBest = i;
        for(j = i + 1; j < NUM_INDIV; j++)
        {
            if(populationCurrent[j]->getFitness() > populationCurrent[indexBest]->getFitness()){
                indexBest = j;
            }
        }
        std::swap(populationCurrent[i], populationCurrent[indexBest]);
        //aux = pop[i];
        //pop[i] = pop[indiceMelhor];
        //pop[indiceMelhor] = aux;
    }
}

int Genetics::selectElite()
{
    int i;
    int cont = (int)(ELITISM * NUM_INDIV);
   // std::cout << cont << std::endl;
    if(cont % 2 != 0)
        cont++;

    orderElite(cont);
    for(i = 0; i < cont; i++)
    {
        populationNew[i]->copy(populationCurrent[i]);

    }
    return cont;
}

int Genetics::tournament()
{
    int indexBest = rand() % NUM_INDIV;
    int index;
    int i;
    for(i = 0; i < NUM_TOURNAMENT-1; i++)
    {
        index = rand() % NUM_INDIV;
        if(populationCurrent[index]->getFitness() > populationCurrent[indexBest]->getFitness())
        {
            indexBest = index;
        }
    }
    return indexBest;
}

void Genetics::selection(int index)
{
    int indexA = tournament();
    int indexB = tournament();

    populationNew[index]->copy(populationCurrent[indexA]);
    populationNew[index + 1]->copy(populationCurrent[indexB]);
}

void Genetics::overwriteCurrent()
{
    int i;
    for(i = 0; i < populationCurrent.size(); i++)
    {
        populationCurrent[i]->copy(populationNew[i]);
    }
}

void Genetics::printBestIndividual()
{
    int i;
    float bestFit = populationCurrent[0]->getFitness();
    int bestIndex = 0;
    for(i = 1; i < populationCurrent.size(); i++)
    {
        if(populationCurrent[i]->getFitness() > bestFit) {
            bestFit = populationCurrent[i]->getFitness();
            bestIndex = i;
        }
    }
    std::cout << "Best fit individual: " << std::endl;
    populationCurrent[bestIndex]->printIndividual();
    return;
}
