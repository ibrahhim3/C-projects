#include<stdio.h>
#include <math.h>

int charToIndex(char c) {
    if (c == ' ' || c == '\n') {
        return 26; // Index for space and newline characters
    } else {
        return c - 'a'; // Index for lowercase letters
    }
}

void calculateRatios(float array[27][27], int totalBiGrams) {
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 27; ++j) {
            if(totalBiGrams==0){
                array[i][j] = totalBiGrams;

            }else{
            array[i][j] /= totalBiGrams;
            }
        }
    }
    
}

void processFile(const char *filename, float language[27][27], int *totalBiGrams) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int prevChar = fgetc(file); // Initialize with the first character
    int currentChar;
    while ((currentChar = fgetc(file)) != EOF) {
        // Check if the character is a lowercase letter space or newline
        if ((currentChar >= 'a' && currentChar <= 'z') || currentChar == ' ' || currentChar == '\n') {
            // Update bi-gram array
            if (!((prevChar == ' ' && (currentChar == ' ' || currentChar == '\n'))||(prevChar=='\n'&&(currentChar==' '||currentChar=='\n')))) {
                language[charToIndex(prevChar)][charToIndex(currentChar)]++; 
                 (*totalBiGrams)++;
                
            }
        }
        prevChar = currentChar;
    }
    fclose(file);
}


float dissimilarity(float array1[27][27], float array2[27][27]) {
    float dissimilarity = 0.0;

    // to calculate dissimilarity 
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 27; ++j) {
            dissimilarity += fabs(array1[i][j] - array2[i][j]);
        }
    }

    return dissimilarity;
}

int main(){

    float language_x[27][27] = {0};
    float language_1[27][27] = {0};
    float language_2[27][27] = {0};
    float language_3[27][27] = {0};
    float language_4[27][27] = {0};
    float language_5[27][27] = {0};

    int totalBiGrams_x = 0;
    int totalBiGrams_1 = 0;
    int totalBiGrams_2 = 0;
    int totalBiGrams_3 = 0;
    int totalBiGrams_4 = 0;
    int totalBiGrams_5 = 0;

    processFile("language_x.txt", language_x, &totalBiGrams_x);
    processFile("language_1.txt", language_1, &totalBiGrams_1);
    processFile("language_2.txt", language_2, &totalBiGrams_2);
    processFile("language_3.txt", language_3, &totalBiGrams_3);
    processFile("language_4.txt", language_4, &totalBiGrams_4);
    processFile("language_5.txt", language_5, &totalBiGrams_5);

    calculateRatios(language_x, totalBiGrams_x);
    calculateRatios(language_1, totalBiGrams_1);
    calculateRatios(language_2, totalBiGrams_2);
    calculateRatios(language_3, totalBiGrams_3);
    calculateRatios(language_4, totalBiGrams_4);
    calculateRatios(language_5, totalBiGrams_5);

    printf("%lf\n", dissimilarity(language_x, language_1));
    printf("%lf\n", dissimilarity(language_x, language_2));
    printf("%lf\n", dissimilarity(language_x, language_3));
    printf("%lf\n", dissimilarity(language_x, language_4));
    printf("%lf\n", dissimilarity(language_x, language_5));
          
}