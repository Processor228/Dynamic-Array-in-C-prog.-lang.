// TODO mergesort function

#include <stdio.h>
#include <stdlib.h>
#define SIZEBATCH 20
#define BATCHDIFF 40

typedef struct dynamicArray{
    // memory is for knowing how many memory array occupies, size is for how many integers are in array already.
    int memory;
    int * containerP;
    int size;
} vector;

void printArray(struct dynamicArray *);
void append(struct dynamicArray *, int);
int pos(struct dynamicArray *, int);
int replace(struct dynamicArray*, int, int);
int search(struct dynamicArray*, int);
int pop(struct dynamicArray*);
void quickSort(struct dynamicArray *);
static void swap(int*, int*);

int main(){
    vector v1;
    for (int i = 0; i < 10; i++) {
        int num;
        scanf("%d", &num);
        append(&v1, num);
    }
    printArray(&v1);
    quickSort(&v1);
    printArray(&v1);
    return 0;
}

void append(struct dynamicArray* v,int num){
    if (v->size == v->memory){
        v->memory += SIZEBATCH;
        int *newPointerToContainer = (int*)malloc(v->memory*sizeof(int));
        for(int i=0; i < v->size; i++){
            *(newPointerToContainer+i) = *(v->containerP+i);
        }
        v->containerP = newPointerToContainer;
    }
    *(v->containerP + v->size) = num;
    v->size += 1;
}

int pos(struct dynamicArray *v, int position){
    if(position < 0 || position > v->size){ printf("ERROR: NO SUCH INDEX: %d \n", position); return -1; }
    return *((v->containerP)+position);
}

int replace(struct dynamicArray* v, int position, int number){
    if(position >= v->size || position < 0) return -1; // error
    *(v->containerP + position) = number;
    return 0;  // no error
}

int search(struct dynamicArray *v, int num){
    for(int i=0; i < v->size; i++){
        if(pos(v, i) == num) return i;
    }
    return -1;
}

int pop(struct dynamicArray *v){
    int poppedNumber = pos(v, v->size-1);
    *(v->containerP + v->size-1) = 0;
    v->size -= 1;
    if(v->memory - v->size > BATCHDIFF){
        v->memory -= SIZEBATCH;
        int *newPointerToContainer = (int*)malloc(v->memory*sizeof(int));
        for(int i=0; i < v->size; i++){
            *(newPointerToContainer+i) = *(v->containerP+i);
        }
        v->containerP = newPointerToContainer;
    }
    return poppedNumber;
}

void printArray(struct dynamicArray * v){
    printf("[ ");
    for(int i = 0; i < v->size; i++) {
        printf("%d ", pos(v, i));
    }
    printf("]\n");
}

void swap(int * a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void q_SortHelper(struct dynamicArray* v, int start, int end){
    if(start >= end) return;
    int pivot = pos(v, (start + end)/2);
    int R = end;
    int L = start;
    while (R > L){
        if(pos(v, L) >= pivot && pivot >= pos(v,R)){
            int temp = pos(v, L);
            replace(v, L, pos(v, R));
            replace(v, R, temp);
            R--;
            L++;
        }
        if(pos(v, R) >= pivot) R -= 1;
        if(pos(v, L) <= pivot) L += 1;
    }
    while(pos(v, R) > pivot) R--;

    q_SortHelper(v, start, R);
    q_SortHelper(v, R + 1, end);
}

void quickSort(struct dynamicArray * v){
    q_SortHelper(v, 0, v->size-1);
}
