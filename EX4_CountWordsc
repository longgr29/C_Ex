#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*==============INITIALIZE GLOBAL VARIABLE==============*/
char string[] = "Mot hai ba bon nam sau bay tam chin mot hai ba bon mot hai nam sau chin";

// size of array *wordArr[] - dynamic array
int wordArrSize = 0;

/*==============INITIALIZE FUNCTION==============*/
void add_element(char*** arr, char* input);
void get_word(char inputStr[], char ***outputArr);
int compare_words(char* x, char* y);
void freq_words(char** arr);

/*==============USER CODE==============*/
int main() {
    // make an dynamic array to store words and change size of array
    char **wordArr = malloc(0 * sizeof(char*));
    get_word(string, &wordArr);
    freq_words(wordArr);
    return 0;
}

/*==============FUNCTION==============*/
// add word to array *wordArr[] 
void add_element(char*** arr, char* input)
{
    wordArrSize++; 
    *arr = (char **)realloc(*arr ,wordArrSize * sizeof(char *));
    (*arr)[wordArrSize - 1] = input;
}

// take each word in string[] to (char *)wordArr
void get_word(char inputStr[], char ***outputArr){
    char *word = strtok(inputStr, " ");
    while (word != NULL) {
        add_element(outputArr, word);
        word = strtok(NULL, " ");
    }
}

// compare two words
int compare_words(char* x, char* y) {
    while(*x != '\0' || *y != '\0') {
        if (*x != *y) {
            return -1; // Unequal words
        }
        x++;
        y++;
    }
    return 0; // Equal words
}

// count freq of word in string
void freq_words(char** arr){
    int freq[wordArrSize];
    for(int i = 0; i < wordArrSize; i++){
        freq[i] = -1;
    }
    for(int i = 0; i < wordArrSize; i++){
        // not count arr[i] which have freq[i] == 0
        if(freq[i] == -1){
            freq[i] = 1;
            for(int j = i + 1; j < wordArrSize; j++){
                // if arr[i] == arr[j] then increase freq[i] and won't count arr[j] in future 
                if(compare_words(*(arr + i), *(arr + j)) == 0){
                    freq[i]++;
                    freq[j] = 0;
                }
            }
        }
        if(freq[i] > 1){
            printf("\n \"%s\" occurs %d times", *(arr + i), freq[i]);
        }
    }
}


