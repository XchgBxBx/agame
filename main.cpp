//
// main.cpp
// 2017-09-21
//

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

#define NUM_LINES   8
#define NUM_COLS    64

#define NUM_TREES       80
#define IT_PER_DAY      2
#define MSECS_PER_IT    500
#define IT_PER_GROW     5
#define MAX_GROW        5

vector<vector<char>> matrix(NUM_LINES, vector<char>(NUM_COLS));

enum dayState
{
    DAY,
    NIGHT
};

struct Lumberjack
{
    int hutPosI = -1;
    int hutPosJ = -1;
};

int currentDay = 0;
dayState currentDayState = DAY;
Lumberjack lumberjack;


/////////////////////////////////////////////////////////////////////////////

void initMatrix()
{
    for(auto& line : matrix)
        for(auto it = line.begin(); it != line.end(); ++it)
            *it = '.';
}

/////////////////////////////////////////////////////////////////////////////

void printMatrix()
{
    for(auto line : matrix)
    {
        for(auto c: line)
            cout << c;

        cout << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////

void initTrees()
{
    int trees = 0;

    while(trees != NUM_TREES)
    {
        int i = rand() % NUM_LINES;
        int j = rand() % NUM_COLS;
        if(matrix[i][j] == '.')
        {
            matrix[i][j] = (rand() % MAX_GROW) + '1';
            trees++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////

void initLumberjack()
{
    bool hasPlace = false;

    while(!hasPlace)
    {
        int i = rand() % NUM_LINES;
        int j = rand() % NUM_COLS;

        if(matrix[i][j] != '.')
            continue;

        // check the neighborhood
        if(i)
        {
            if(matrix[i-1][j] != '.')
                continue;
        }
        if(i < (NUM_LINES - 1))
        {
            if(matrix[i+1][j] != '.')
                continue;
        }
        if(j)
        {
            if(matrix[i][j-1] != '.')
                continue;
        }
        if(j < (NUM_COLS - 1))
        {
            if(matrix[i][j+1] != '.')
                continue;
        }

        lumberjack.hutPosI = i;
        lumberjack.hutPosJ = j;
        matrix[lumberjack.hutPosI][lumberjack.hutPosJ] = 'H';

        hasPlace = true;
    }
}

/////////////////////////////////////////////////////////////////////////////

void changeDayState()
{
    if(currentDayState == NIGHT)
    {
        currentDay++;
        currentDayState = DAY;
    }
    else
        currentDayState = NIGHT;
}

/////////////////////////////////////////////////////////////////////////////

void growTrees()
{
    for(auto& line : matrix)
        for(auto it = line.begin(); it != line.end(); ++it)
            if(*it > '0' && *it < (MAX_GROW + '0'))
                (*it)++;
}

/////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(time(NULL));

    // clear the ground
    initMatrix();

    // spawn some trees
    initTrees();

    initLumberjack();

    unsigned int iteration = 0;

    while(true)
    {
        cout << "---------------------------" << endl;
        printMatrix();

        cout << " > Current iteration: " << iteration << endl;
        cout << " > Day #: " << currentDay << endl;
        cout << " > State: " << (currentDayState == DAY ? "DAY" : "NIGHT") << endl;

        iteration++;
        if(iteration % IT_PER_DAY == 0)
            changeDayState();
        if(iteration % IT_PER_GROW == 0)
            growTrees();

        this_thread::sleep_for(chrono::milliseconds(MSECS_PER_IT));
    }

    return 0;
}
