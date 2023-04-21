#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*==============INITIALIZE MACRO==============*/
#define LEN_ARRAY(arr) (sizeof(arr)/sizeof(arr[0]))

/*==============INITIALIZE GLOBAL VARIABLE==============*/
int unsortedArr[] = {1, 4, 5, 7, 2, 4, 1, 6, 3, 6, 7, 5, 2, 2, 7};

char charArr[] = {"Make no mistake All your attempts to create a chilling effect a throttling effect a strangulating effect on open fearless speech relating to public influence will not stop either Rahul Gandhi or the Congress Party"};

/*==============INITIALIZE FUNCTION==============*/
void sort_arr(int unsortedArr[], int size);
void print_arr(const int array[], int size);
void freq_in_arr(int arr[], int size);
void reverse_arr(const char arr[], int size);

/*==============USER CODE==============*/
void main(){
    sort_arr(unsortedArr, LEN_ARRAY(unsortedArr));
    print_arr(unsortedArr, LEN_ARRAY(unsortedArr));
    freq_in_arr(unsortedArr, LEN_ARRAY(unsortedArr));
    reverse_arr(charArr, LEN_ARRAY(charArr));
}

/*==============FUNCTION==============*/
//insertion sort
void sort_arr(int unsortedArr[], int size){
    for(int i = 1; i < size; i++){
        int selectedNum = unsortedArr[i];
        int j = i - 1;
        while (selectedNum < unsortedArr[j] && j >= 0) {
            unsortedArr[j + 1] = unsortedArr[j];
            j--;
        }
        unsortedArr[j + 1] = selectedNum;
    }
}

void print_arr(const int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// first, sort the array then count each element
void freq_in_arr(int arr[], int size){
    sort_arr(arr, size);
    int count = 1;
    for(int i = 0; i < size; i++){
        if(arr[i] == arr[i + 1]){
            count++;
        }
        else{
            printf("%d occurs %d times\n", arr[i], count);
            count = 1;
        }
    }
}

//read each word from right to left of array. if element is a space character, print that word
void reverse_arr(const char arr[], int size){
    char wordArr[20];
    int lenWord = 0;
    for(int i = size - 2; i >= -1; i--){ //i >= -1 for print arr[0]
        if(arr[i] == ' ' || i == -1){
            for(int j = lenWord - 1; j >= 0; j--){
                printf("%c", wordArr[j]);
            }
            printf(" ");
            lenWord = 0;
        }
        else{
            lenWord++;
            wordArr[lenWord - 1] = arr[i];
        }
    }
}
