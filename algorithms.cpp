#include "algorithms.h"
#include <QDebug>
#include <cmath>
Algorithms::Algorithms()
{

}

bool Algorithms::contain(const int q, int *visited, const int n)
{
    int i;

    for (i = 0; i < n; i++)
        if (*(visited+i) == q)
            return true;

    return false;
}

void Algorithms::TSP(bool *visited, int &shptr, int n, double **W, double &dh, double &d, int &sptr, Road *road, int *S, int *Sh, int v)
{
    if(!road->work)
        return;

    int u;

    Sh[shptr++] = v;

    if (shptr < n)
    {
        visited[v] = true;
        for (u = 0; u < n; u++)
            if (!visited[u])
            {
                dh += W[v][u];
                TSP(visited, shptr, n, W, dh, d, sptr, road, S, Sh, u);
                dh -= W[v][u];
            }
        visited[v] = false;
    }
    else
    {
        dh += W[v][0];
        if (dh < d)
        {
            d = dh;
            for (u = 0; u < shptr; u++)
                S[u] = Sh[u];
            sptr = shptr;
        }
        dh -= W[v][0];
    }
    shptr--;
}

void Algorithms::swap(int *i, int *q){
    int buffor=*i;
    *i=*q;
    *q=buffor;
}

int Algorithms::compare(const void *a, const void *b){
    double omega=((struct array_struct *)a)->distance;
    double alfa=((struct array_struct *)b)->distance;

    return (omega>alfa) - (omega<alfa);
}

void Algorithms::Genetic(Road *road){
    qDebug() << "3";

    unsigned long long N = (unsigned long long) road->count;

    Point *tab = road->points;

    const int genetic=15;
    struct array_struct array_struct[15];
    unsigned long long q=0;
    unsigned long long i=0;
    int c=0;
    int ls=0;
    srand(time(NULL));
    double **distance = new double * [N];

    int *tester=NULL;

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

    int **points = new int * [genetic];

    for (i = 0; i < genetic; i++)
    {
        points[i] = new int [N];
    }

    if(!road->work)
    {
        for(i=0;i<N;i++)
            delete [] distance[i];
        for(i=0;i<genetic;i++)
            delete [] points[i];

        delete [] points;
        delete [] distance;
        return;
    }

    tester = new int [N];

    for(i=0;i<genetic-3 && (road->work);i++)
    {
        for(q=0;q<N && (road->work);q++)
            tester[q]=q;

        points[i][0]=0;

        for(q=1;q<N && (road->work);q++)
        {
            unsigned long long n=rand()%(N-q+1);
            if(n==0)
                n=1;
            points[i][q]=tester[n];
            if(n==(N-q))
                tester[n]=NULL;
            else
                tester[n]=tester[N-q];

        }
        if(!road->work)
        {
            for(i=0;i<N;i++)
                delete [] distance[i];
            for(i=0;i<genetic;i++)
                delete [] points[i];
            delete [] points;
            delete [] tester;
            delete [] distance;
            return;
        }
    }

    if(!road->work)
    {
        for(i=0;i<N;i++)
            delete [] distance[i];
        for(i=0;i<genetic;i++)
            delete [] points[i];
        delete [] points;
        delete [] tester;
        delete [] distance;
        return;
    }

    delete [] tester;

    int counter = 0;

    for(; counter<15 && (road->work); counter++)
    {
        i=12;
        for(;i<genetic && (road->work);i++)
        {
            ls=rand()%i;
            c=rand()%i;
            while(c==ls )
                c=rand()%i;

            for(q=0;q<(unsigned long long)(N/2) && (road->work);q++)
                points[i][q]=points[ls][q];

            if(!road->work)
            {
                for(i=0;i<N;i++)
                    delete [] distance[i];
                for(i=0;i<genetic;i++)
                    delete [] points[i];
                delete [] points;
                delete [] distance;
                return;
            }

            unsigned long long ctd;
            unsigned long long cts;
            for(q=(int)(N/2) && (road->work);q<N;q++)
            {
               for(ctd=1;ctd<N && (road->work);ctd++)
               {
                   for(cts=1;cts<q && (road->work);cts++)
                      if(points[c][ctd]==points[i][cts])
                        break;
                    if(!road->work)
                    {
                        for(i=0;i<N;i++)
                            delete [] distance[i];
                        delete [] distance;
                        return;
                    }

                   if(cts==q)
                     points[i][q]=points[c][ctd];
               }
               if(!road->work)
               {
                   for(i=0;i<N;i++)
                       delete [] distance[i];
                   delete [] distance;
                   return;
               }

            }

            if(!road->work)
            {
                for(i=0;i<N;i++)
                    delete [] distance[i];
                for(i=0;i<genetic;i++)
                    delete [] points[i];
                delete [] points;
                delete [] distance;
                return;
            }
        }

        i=rand()%genetic;
        swap(&points[i][rand()%(N-1)+1],&points[i][rand()%(N-1)+1]);

        for(i=0;i<genetic && (road->work);i++)
        {
            double ualk=0;
            array_struct[i].i=points[i];

            for(q=0;q<N-1 && (road->work);q++)
                ualk+=distance[points[i][q]][points[i][q+1]];

            array_struct[i].distance=ualk;
        }

        qsort(&array_struct,15,sizeof(struct array_struct),compare);

        for(i=0;i<12 && (road->work);i++)
            for(q=0;q<N && (road->work);q++)
                points[i][q]=array_struct[i].i[q];

        if(!road->work)
        {
            for(i=0;i<N;i++)
                delete [] distance[i];
            for(i=0;i<genetic;i++)
                delete [] points[i];
            delete [] points;
            delete [] distance;
            return;
        }

    }

    if(!road->work)
    {
        for(i=0;i<N;i++)
            delete [] distance[i];
        for(i=0;i<genetic;i++)
            delete [] points[i];
        delete [] points;
        delete [] distance;
        return;
    }

    for (i = 0; i < N && (road->work); i++){
        qDebug() << array_struct[0].i[i];
        (road)->computedRoad[i] = array_struct[0].i[i];
    }

    if(!road->work)
    {
        for(i=0;i<N;i++)
            delete [] distance[i];
        for(i=0;i<genetic;i++)
            delete [] points[i];
        delete [] points;
        delete [] distance;
        return;
    }

    qDebug() << "2";

    for(i=0;i<N;i++)
        delete [] distance[i];

    for(i=0;i<genetic;i++)
        delete [] points[i];

    delete [] points;
    delete [] distance;

    road->isDone = true;
}


void Algorithms::NearestNeighbor(Road *road) {
    qDebug() << "3";

    unsigned long long N = (unsigned long long) road->count;
    Point *tab = road->points;

    double **distance = new double * [N];

    unsigned long long  i = 0, q = 0;

    for (i = 0; i < N; i++)
        distance[i] = new double [N];

    qDebug() << "1";

    if(!road->work)
    {
        for(i=0;i<N;i++)
             delete [] distance[i];

        delete [] distance;
        return;
    }

    qDebug() << "2";

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

    int *visited = new int [N];

    for (i = 0; i < N; i++){
        *(visited + i) = 0;
    }

    if(!road->work)
    {
        for(i=0;i<N;i++)
             delete [] distance[i];

        delete [] visited;
        delete [] distance;
        return;
    }

    for (i = 0; i < N && road->work; i++) {
        double najmniejsze = 0;
        int bmc = 0;
        for (q = 1; q < N; q++)
        {
            if (!Algorithms::contain(q, visited, N))
            {
                bmc = q;
                break;
            }
            else
                bmc = q;
        }

        najmniejsze = distance[bmc][visited[i]];
        visited[i + 1] = bmc;

        for (q = 1; q < N; q++)
        {
            if (contain(q, visited, N))
                continue;
            if (najmniejsze > distance[q][visited[i]])
            {
                najmniejsze = distance[q][visited[i]];
                visited[i + 1] = q;
            }
        }
    }

    for (i = 0; i < N; i++) {
        *(road->computedRoad + i) = *(visited + i);
    }

    delete [] visited;

    for(i=0;i<N;i++)
        delete [] distance[i];

    delete [] distance;

    road->isDone = true;
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
           next_permutation(visted + 1, N - 1);

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

void Algorithms::TSPPrint(Road *road){

    unsigned long long N = (unsigned long long) road->count;

    Point *tab = road->points;
    int *computedRoad=road->computedRoad;
    double **distance = new double * [N];
    bool *visited = new bool[N];
    int *s = new int[N];
    int *sh = new int[N];

    unsigned long long  i = 0, q = 0;

    for (i = 0; i < N; i++)
        distance[i] = new double [N];

    for (i = 0; i < N && road->work; i++)
        for (q = 0; q < N; q++)
            distance[i][q] = sqrt((tab[i].getX() - tab[q].getX())*(tab[i].getX() - tab[q].getX()) + (tab[i].getY() - tab[q].getY())*(tab[i].getY() - tab[q].getY()));

    int sptr = 0, shptr = 0;
    double dh = 0, d = std::numeric_limits<double>::max();

    if(!road->work)
    {
        for(i=0;i<N;i++)
            delete [] distance[i];

        delete [] distance;
        delete [] s;
        delete [] sh;
        delete [] visited;
        return;
    }

    TSP(visited, shptr, (int)N, distance,dh, d,sptr, road,s, sh, 0);

    if(road->work)
        for(int i =0; i < N; ++i)
            computedRoad[i] = s[i];

    for(i=0;i<N;i++)
        delete [] distance[i];

    delete [] distance;
    delete [] s;
    delete [] sh;
    delete [] visited;

    road->isDone = true;

}
