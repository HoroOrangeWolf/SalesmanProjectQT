#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <thread>
#include "road.h"
#include <cmath>
#include <time.h>

class Algorithms
{
private:
    static unsigned long long silnia(int n);
    static void reverse(int *first, int i, int j);
    static void next_permutation(int *first, int n);
    static void swap1(int *a, int i, int j);
public:
    Algorithms();
    static void BruteForce(Road *road);
};

#endif // ALGORITHMS_H
