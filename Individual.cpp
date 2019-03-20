//
// Created by bruno on 07/03/2019.
//

#include "Individual.h"


Individual::Individual(int ArgSize)
{
    this->size = ArgSize;
    this->fitness = -1;

    chromossome.resize(this->size);
}

Individual::Individual(const Individual& i)
{
    chromossome = i.chromossome;
    size = i.size;
    fitness = i.fitness;
}

Individual::~Individual()
{
    chromossome.clear();
}

int Individual::initializeChromossomeRandom()
{
    int i;
    for(i = 0; i < chromossome.size(); i++)
    {
        chromossome[i] = rand();
    }
    return 0;
}

int Individual::initializeChromossomeRange(int lower, int upper)
{
    int i;
    for(i = 0; i < chromossome.size(); i++)
    {
        int random = rand();
        chromossome[i] = (random % (upper + 1 - lower)) + lower;
    }
    return 0;
}

int Individual::initializeChromossomeRangeFloat(float lower, float upper)
{
    int i;
    for(i = 0; i < chromossome.size(); i++)
    {
        float random = lower + rand()/(RAND_MAX/(upper-lower));
        std::cout << random << std::endl;
        chromossome[i] = floatToInt(random);
    }
    return 0;
}

void Individual::printIndividual() {
    int i = 0;

    std::cout  << "(" << std::setw(PRINT_FORMAT) << intToFloat(chromossome[i]) << ")" << " + ";
    for(i = 1; i < chromossome.size()-1; i++)
    {
        std::cout  << "(" << std::setw(PRINT_FORMAT) << intToFloat(chromossome[i]) << ") x" << i << " + ";
    }
    std::cout << "(" << std::setw(PRINT_FORMAT) <<  intToFloat(chromossome[i]) << ") x" << i << " | Fitness = " << fitness << std::endl;

}
double calculateDistance(std::vector<double> point, double x, double y)
{
    double x2 = pow(x - point[0], 2);
    double y2 = pow(y - point[1], 2);
    return sqrt(x2+y2);
}

void Individual::evaluateIndividual(std::vector<double> point, char type) {
    //evaluate indiv

    int i;
    double result = 0;
    for (i = 0; i < chromossome.size(); i++) {
        result += intToFloat(chromossome[i]) * pow(point[0], i);
        //std::cout << pow(point[0], i) << std::endl;
    }
    //double dist = calculateDistance(point, point[0], result);
    if ((type == 'P' && result <= point[1]) || (type == 'N' && result > point[1]))
    {
        fitness ++;
    }
}


float randomProbability()
{
    return (float)(rand())/(float)(RAND_MAX +1);
}

void Individual::mutate()
{
    int i, j;
    float probMut;
    for (i = 0; i < chromossome.size(); i++) {
        for(j = 0; j < 5; j++)
        {
            probMut = randomProbability();
            if(probMut <= PROB_MUT)
            {
                //std::cout << chromossome[i] << std::endl;
                chromossome[i] ^= (1 << j);
                //std::cout << chromossome[i] << std::endl;
            }
        }
        probMut = randomProbability();
        if(probMut <= PROB_MUT)
        {
            //std::cout << chromossome[i] << std::endl;
            chromossome[i] = ~chromossome[i] + 1;
            //std::cout << chromossome[i] << std::endl;
        }
    }
}

void Individual::crossover(Individual *ind)
{
    int i, j;
    int mask1, mask2;
    int out1, out2;
    float probCross;
    int positionCross;
    std::vector<int> indBChromossome = ind->getChromossome();

    for (i = 0; i < chromossome.size(); i++) {
        probCross = randomProbability();
        if(probCross <= PROB_CROSS)
        {
            positionCross = rand()%6 +1;
            mask1 = ((0xffffffff >> positionCross) << positionCross);
            mask2 = 0xffffffff ^ mask1;
            out1 = (chromossome[i] & mask1) ^ (indBChromossome[i] & mask2);
            out2 = (chromossome[i] & mask2) ^ (indBChromossome[i] & mask1);

            //std::cout << std::bitset<32>(mask1) << std::endl << std::bitset<32>(mask2) << std::endl;
            //std::cout << std::bitset<32>(chromossome[i]) << " " << std::bitset<32>(indBChromossome[i]) << std::endl;
            //std::cout << std::bitset<32>(out1) << " " << std::bitset<32>(out2) << std::endl;

            chromossome[i] = out1;
            ind->setChromossome(i, out2);
        }
    }
}

Individual& Individual::operator =(const Individual& i)
{
    if(this != &i)
    {
        for(int k = 0; k < chromossome.size(); k++)
            chromossome[k] = i.chromossome[k];
        size = i.size;
        fitness = i.fitness;
    }
    return *this;
}

void Individual::copy(Individual *i)
{
    for(int k = 0; k < i->chromossome.size(); k++)
        chromossome[k] = i->chromossome[k];

    size = i->size;
    fitness = i->fitness;
}

void Individual::initializeChromossomeParameters(std::vector<int> coef)
{
    int i;
    for(i = 0; i < coef.size(); i++)
    {
        chromossome[i] = coef[i];
    }
}


