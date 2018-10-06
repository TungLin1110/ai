#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <bits/stdc++.h>
#define SIZE 50
#define POP 8
//#define unattack (SIZE * (SIZE - 1)) / 2
#define unattack 1225
//#define probnum unattack *POP
#define probnum 9800
using namespace std;

int length(int array[])
{
    int i = 0;
    while (array[i] != -1)
        i++;
    return i;
}

int getRand(int mod)
{
    if (mod == 0)
        return 0;
    else
        return random() % mod;
}

void printArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
        printf("(%i,%i) ", i, array[i]);
    printf("\n");
}

int getWeight(int array[])
{

    int weight = unattack;
    for (int queen = 0; queen < SIZE; queen++)
    { //for each queen;
        for (int nextqueen = queen + 1; nextqueen < SIZE; nextqueen++)
        { //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
            if (array[queen] == array[nextqueen] || abs(queen - nextqueen) == abs(array[queen] - array[nextqueen]))
            { //if conflict
                weight--;
            }
        }
    }
    return weight;
}

void geneticAlgorithm()
{
    int population[POP][SIZE] = {};
    int children[POP][SIZE] = {};
    int weightProb[probnum] = {};
    int wpl = 0;         //weightProb length
    float mutProb = 0.1; //mutation probability
    int success = 0;
    int i;
    for (i = 0; i < POP; i++)
        for (int j = 0; j < SIZE; j++)
            population[i][j] = getRand(SIZE);
    printf("origin parents:\n");
    for (i = 0; i < POP; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%d ", population[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    while (success == 0)
    {
        for (i = 0; i < POP; i++)
        {
            if (getWeight(children[i]) == unattack)
            {
                printf("solution: ");
                printArray(children[i]);
                success = 1;
            }
        }

        for (i = 0; i < wpl; i++)weightProb[i] = (int)NULL; //clear
        wpl = 0;

        for (i = 0; i < POP; i++)
        {
            int w = getWeight(population[i]);
            for (int j = 0; j < w; j++)
            {
                weightProb[wpl] = i;
                wpl++;
            }
        }

        //reproduce
        for (i = 0; i < POP; i += 2)
        {
            int crossover1 = weightProb[getRand(wpl)];
            int crossover2 = weightProb[getRand(wpl)];
            int changpoint = getRand(SIZE);
            //crossover
            for (int j = 0; j < changpoint; j++)
            {
                children[i][j] = population[crossover1][j];
                children[i + 1][j] = population[crossover2][j];
            }
            for (int j = changpoint; j < SIZE; j++)
            {
                children[i][j] = population[crossover2][j];
                children[i + 1][j] = population[crossover1][j];
            }
            //mutation

            if (getRand(1000) <= mutProb * 1000)
            {
                    children[i][getRand(SIZE)] = getRand(SIZE);
            }
            if (getRand(1000) <= mutProb * 1000)
            {
                    children[i + 1][getRand(SIZE)] = getRand(SIZE);
            }

        }
        for (i = 0; i < POP; i++)
            for (int j = 0; j < SIZE; j++)
                population[i][j] = children[i][j];
        wpl = 0;
    }
}

int main(int argc, const char *argv[])
{
    int seed = atoi(argv[1]);
    srandom(seed);                     //seed random
    //srandom((unsigned int)time(NULL)); //seed random
    geneticAlgorithm();
    return 0;
}
