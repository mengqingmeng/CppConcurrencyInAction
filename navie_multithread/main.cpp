#include <iostream>

static const int MAX = 10e8;
static double sum = 0;

void worker(int min,int max){
    for(int i=min;i<=max;++i){
        sum += sqrt(i);
    }
}