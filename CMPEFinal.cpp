// CMPEFinal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
    
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void PrintMatrix(int mat[8][8]);
void MoveBeetle(int mat[8][8], int initialI, int initialJ);
bool IsBoundary(int i, int j);
bool IsVisitedAll(int mat[8][8]);
void FourDirectionCounter(int,int,int*,int*,int*,int*);
void CalculateProbability(int left, int right, int up, int down, int border, int all);

int main()
{
    srand(time(NULL));

    int newI = 0;
    int newJ = 0;
    int tiles[8][8] = { 0 };

    printf("Please enter initial locations of beetle on tiles (Between 0 & 7): ");
    scanf("%d %d", &newI, &newJ);
    tiles[newI][newJ]++;

    MoveBeetle(tiles, newI, newJ);

    PrintMatrix(tiles);
}

void PrintMatrix(int mat[8][8])
{
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d\t", mat[i][j]);
        }

        printf("\n");
    }
}

void MoveBeetle(int mat[8][8], int initialI, int initialJ)
{
    int newI = initialI;
    int newJ = initialJ;
    bool seenAll = false;

    int left = 0, right = 0, up = 0, down = 0, border = 0, all = 0;

    while (!seenAll)
    {
        int addI = -1 + rand() % 3;
        int addJ = -1 + rand() % 3;

        if (addI != 0 || addJ != 0)
        {
            all++;

            bool isBoundary = IsBoundary(newI + addI, newJ + addJ);

            if (!isBoundary)
            {
                FourDirectionCounter(addI, addJ, &left, &right, &up, &down);
                newI += addI;
                newJ += addJ;
                mat[newI][newJ]++;
            }
            else
            {
                border++;
            }
            seenAll = IsVisitedAll(mat);
        }
    }

    CalculateProbability(left, right, up, down, border, all);
}

bool IsBoundary(int i, int j)
{
    if (i > 7 || i < 0 || j >7 || j < 0)
    {
        return true;
    }

    return false;
}

bool IsVisitedAll(int mat[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (mat[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void FourDirectionCounter(int addI, int addJ, int* left , int* right, int* up, int* down)
{
    if (addI == 0 && addJ == -1)
    {
        *left+=1;
    }
    else if (addI == 0 && addJ == 1)
    {
        *right += 1;
    }
    else if (addI == -1 && addJ == 0)
    {
        *up += 1;
    }
    else if (addI == 1 && addJ == 0)
    {
        *down += 1;
    }
}

void CalculateProbability(int left, int right, int up, int down, int border, int all)
{
    printf("The probability of moving left: %.2f %%\n", (left * 1.0 / all) *100);
    printf("The probability of moving right: %.2f %%\n", (right * 1.0 / all) * 100);
    printf("The probability of moving up: %.2f %%\n", (up * 1.0 / all) * 100);
    printf("The probability of moving down: %.2f %%\n", (down * 1.0 / all) * 100);
    printf("The probability of moving out of border: %.2f %%\n", (border * 1.0 / all) * 100);
}

