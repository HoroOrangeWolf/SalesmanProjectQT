#include "algorithms.h"
#include <QDebug>
#include <cmath>
Algorithms::Algorithms()
{

}

unsigned long long Algorithms::silnia(int n){

    if(n==0)
            return 1;
    else
    {
        unsigned long long number=1L;

        for(int i=1;i<=n;i++)
            number*=i;

        return number;
    }
}

double Algorithms::computeDistance(Road *road){
    double distance = 0.f;
    for(int i = 0; i < road->count - 1; ++i){
        Point p1 = road->points[road->computedRoad[i]];
        Point p2 = road->points[road->computedRoad[i + 1]];
        distance += sqrt((p1.getX() - p2.getX())*(p1.getX() - p2.getX()) + (p1.getY() - p2.getY())*(p1.getY() - p2.getY()));
    }

    return distance;
}

void Algorithms::next_permutation(int *first, int n){
    int i=n-2;

    while(i>=0 && first[i+1]<= first[i])
    {
        i--;
    }

    if(i>=0)
    {
        int j=n-1;
        while(j>=0 && first[j]<=first[i])
            j--;
        swap1(first,i,j);
    }

    reverse(first,i+1,n-1);
}

void Algorithms::swap1(int *a, int i, int j){
    int buff=a[i];
    a[i]=a[j];
    a[j]=buff;
}

void Algorithms::reverse(int *first, int i, int j){
    while(i<j)
    {
        swap1(first,i,j);
        i++;
        j--;
    }
}

void Algorithms::BruteForce(Road *road){

       unsigned long long N = (unsigned long long) road->count;
       Point *tab = road->points;
       int *computedRoad=road->computedRoad;

       unsigned long long  siln=silnia(N-1);

       double **distance = new double * [N];

       unsigned long long  i = 0, q = 0;

       for (i = 0; i < N; i++)
           distance[i] = new double [N];

       for (i = 0; i < N && road->work; i++)
           for (q = 0; q < N; q++)
               distance[i][q] = sqrt((tab[i].getX() - tab[q].getX())*(tab[i].getX() - tab[q].getX()) + (tab[i].getY() - tab[q].getY())*(tab[i].getY() - tab[q].getY()));

       if(!road->work)
       {
           for(i=0;i<N;i++)
                delete [] distance[i];

           delete [] distance;
           return;
       }

       long double total_distance = 0;

       int *visted = new int [N];

       int *road_b = new int [N];

       for (i = 0; i < N; i++)
       {
           *(visted + i) = i;
           *(road_b + i) = i;
       }

       for (i = 0; i < N - 1; i++)
           total_distance += distance[i][i + 1];

       long double total_distance2 = 0;

       for(q=0;q<siln && road->work;q++)
       {
           next_permutation(visted+1, N-2);

           total_distance2 = 0;

           for (i = 0; i < N - 1; i++)
               total_distance2 += distance[visted[i]][visted[i + 1]];

           if (total_distance2 < total_distance)
           {
               total_distance = total_distance2;
               for (i = 0; i < N; i++)
                   *(road_b + i) = *(visted + i);
           }
       }

       if(!road->work)
       {
           for(i=0;i<N;i++)
                delete [] distance[i];

           delete [] road_b;
           delete [] visted;
           delete [] distance;
           return;
       }

       for (i = 0; i < N; i++)
       {
           *(computedRoad + i) = *(road_b + i);
       }


       for(i=0;i<N;i++)
           delete [] distance[i];

       delete [] road_b;
       delete [] visted;
       delete [] distance;
       road->isDone = true;
}
