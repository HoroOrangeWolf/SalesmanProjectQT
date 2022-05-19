#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <thread>
#include "road.h"
#include <cmath>
#include <time.h>
#include <vector>
#include <limits>

struct array_struct
{
    double distance;
    int *i;
};

class Algorithms
{
private:
    static unsigned long long silnia(int n);
    static void reverse(int *first, int i, int j);
    static void next_permutation(int *first, int n);
    static void swap1(int *a, int i, int j);
    static void swap(int *i, int *q);
    static int compare(const void *a, const void *b);
    static bool contain(const int q, int *visited, const int n);
    static void TSP(bool *visited, int &shptr, int n, double **W, double &dh, double &d, int &sptr, Road *road, int *S, int *Sh, int v);
public:
    Algorithms();
    static void BruteForce(Road *road);
    static void NearestNeighbor(Road *road);
    static void Genetic(Road *road);
    static double computeDistance(Road *road);
    static double computeDistanceBetweenStartAndEnd(Road *road);
    static void TSPPrint(Road *road);
};

#endif // ALGORITHMS_H
