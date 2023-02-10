#include "../include/my_math.h"

float my_square(int num){
    int start = 0, end = num, mid = 0;
    float res;
    while(start <= end){
        mid = (start + end)/2;
        if(mid * mid == num){
            res = mid;
            break;
        }
        if(mid * mid < num){
            res = start;
            start = mid + 1;
        }else
            end = mid - 1;
    }
    float jump = 0.1;
    for(int i = 0; i < 5; i++){
        while(res * res <= num)
            res += jump;
        res = res - jump;
        jump /= 10;
    }
    return res;
}

long my_pow(int base, unsigned n){
    long res = 1L;
    for(unsigned i = 0; i < n; i++)
        res *= base;
    return res;
}