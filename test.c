#include<stdio.h>
#include<stdlib.h>
int *x;
int main(){
    x = malloc(sizeof(int));
    free(x);
    x = malloc(sizeof(int));
    free(x);
}