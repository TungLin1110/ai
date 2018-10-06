#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <bits/stdc++.h>
#define SIZE 50

int answers[SIZE] = {};
int count = 0;

int length(int array[])
{
    int i = 0;
    while (array[i] != -1)
        i++;
    return i;
}



void printArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
        printf("(%i,%i)", i, array[i]);
}



int getWeight(int array[])
{
    int weight = 0;
    int queen;
    for (queen = 0; queen < SIZE; queen++)
    { //for each queen
        int nextqueen;
        for (nextqueen = queen + 1; nextqueen < SIZE; nextqueen++)
        { //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
            if (array[queen] == array[nextqueen] || abs(queen - nextqueen) == abs(array[queen] - array[nextqueen]))
            { 
                weight++;
            }
        }
    }
    return weight;
}

void hillClimbing(int array[])
{
    int weight = getWeight(array);
    if (weight == 0)
    {
        printf("direct success: ");
        printArray(array);
        printf("  attacks 0  ->success\n");
        exit(0);
    }
    else
    {
        int nextrow[] = {-1};
        int nextcol[] = {-1};
        int nextweight = weight;
        int queen;
        for (queen = 0; queen < SIZE; queen++)
        {                               //for each queen/row            
            int origcol = array[queen]; //save the original column       
            int validcol;               //searching the whole board
            for (validcol = 0; validcol < SIZE; validcol++)
            { //for each valid column          |
                if (validcol != origcol)
                {                                     
                    array[queen] = validcol;          //place the queen in the next column
                    int newweight = getWeight(array); //get the weight of the modified board
                    if (newweight < nextweight)
                    { //if it's a better move
                        int i;
                        for (i = 0; i < length(nextrow); i++)
                        { //clear the boards
                            nextrow[i] = (int)NULL;
                            nextcol[i] = (int)NULL;
                        }
                        nextrow[0] = queen;
                        nextrow[1] = -1;
                        nextcol[0] = validcol;
                        nextcol[1] = -1;
                        nextweight = newweight;
                        count++;
                        hillClimbing(array);
                    }
                    else if (newweight == nextweight)
                    {
                        int len = length(nextrow);
                        nextrow[len] = queen;
                        nextrow[len + 1] = -1;
                        nextcol[len] = validcol;
                        nextcol[len + 1] = -1;
                    }
                }
            }
            array[queen] = origcol;
        }
        //once we're done searching the board
        if (nextcol[0] != -1 && nextrow[0] != -1)
        { //if we've found a better move
            int i;
            for (i = 0; i < length(nextrow); i++)
            {                                   //for each nextmove that will yield a better weight
                array[nextrow[i]] = nextcol[i]; //make it
                count++;                        //increase the count
                printf("count: %i\n", count);
                hillClimbing(array); //recurse
                count--;             
            }
        }
        else
        {
            printf("after hc: ");
            printArray(array);
            printf("  attacks %d \n",getWeight(array)); 
            exit(0);
           
        }
    }
}

int main(int argc, const char *argv[])
{
    if(argc<2)
    {printf("error");}
    int seed=atoi(argv[1]);
    srandom(seed); //seed random
    
    for (int i = 0; i < SIZE; i++)
        answers[i] = random() % SIZE;
    printf("origin:   ");
    printArray(answers);
    printf("\n");
    hillClimbing(answers);
    
    
    return 0;
}