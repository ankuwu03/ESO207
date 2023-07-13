
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include<assert.h>
# define UPPER_LIMIT 10000000  //upperlimit
#define ITERATIONS 500    //no of iteration of code for time calculation
#define ARR_SIZE 100    //array size

int * merge(int * arr, int i, int mid, int k, int * fin) {  //algo same as class
    int p = i;
    int j = mid + 1;
    int r = 0;
    while (p <= mid && j <= k) {
        if (arr[p] < arr[j]) {
            fin[r] = arr[p];
            p++;
            r++;
        } 
        else {
            fin[r] = arr[j];
            j++;
            r++;
        }
    }
    while (p <= mid) {
        fin[r] = arr[p];
        p++;
        r++;
    }
    while (j <= k) {
        fin[r] = arr[j];
        j++;
        r++;
    }
    return fin;
}
void msort(int * arr, int i, int k) {
    if (i < k) {
        int mid = (i + k) / 2;
        msort(arr, i, mid);
        msort(arr, mid + 1, k);
        int * c; //create temporary array C and store the sorted data(index i to k) in it which we copy back to Arr later
        c = (int * ) malloc(sizeof(int) * (k - i + 1));
        merge(arr, i, mid, k, c);                             
        for (int b = i; b <= k; b++) {
            arr[b] = c[b - i]; //copy C back to arr
        }
        free(c);   //free teh allocated memory of C
    }
}

int partition(int * arr, int l, int h) {
    int pivot;
    pivot = arr[l];  //pivot is first element
    //if arr[i] < pivot we move on else we exchange with last element and move on
    int i = l;
    int j = h;
    while (i < j) {
        while (arr[i] <= pivot && i < h) {
            i++;
        }
        while (arr[j] >= pivot && j > l) {
            j--;
        }
        if (i < j) {
            int temp;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //lastly we move pivot b/w elements less than pivot and element more than pivot by swap operation
    //arr = [ {elements < Pivot} , Pivot , {elements> Pivot} ]
    int temp1;
    temp1 = arr[l];
    arr[l] = arr[j];
    arr[j] = temp1;
    return j;
}

void quicksort(int * arr, int l, int h) {
    if (l < h) {
        int i = partition(arr, l, h);
        quicksort(arr, l, i - 1);
        quicksort(arr, i + 1, h);
    }
}



int main() {
    srand(time(NULL));
    int n=ARR_SIZE;
    int arr[n];

    clock_t t ;
    clock_t time_taken ;
    double total_time=0;

    for(int i=0;i<ITERATIONS;i++){
        for (int i = 0; i < n; i++) {
            arr[i] = rand()%UPPER_LIMIT;
        }
        t = clock() ;

        msort(arr,0,n-1);  //merge sort
        quicksort(arr, 0, n - 1);  //quick sort

        time_taken = clock()-t;
        total_time = total_time + time_taken;
    }

    int time_us = ((double)total_time*1000000/(double)CLOCKS_PER_SEC);
    printf("TIME(us)= %d",time_us/ITERATIONS);
    return 0;
}