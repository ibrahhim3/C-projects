#include <stdio.h>

int main() {
    int firstnum[100];
    int secondnum[100];
    int gramsCount[100];
    //open the input file for reading 
    FILE *inputfile = fopen("input.txt", "r");

    if (inputfile == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }

    int numPairs = 0;
    int prevNum;
    //scan the firs num and put it prevnum
    if (fscanf(inputfile, "%d", &prevNum) != 1) {
        printf("Error readin.\n");
        return 1;
    }
    
    while (fscanf(inputfile, "%d", &secondnum[numPairs]) == 1) {
        firstnum[numPairs] = prevNum;
        numPairs++;

        if (numPairs >= 100) {
            printf("Reached to the maximum \n");
            break;
        }

        prevNum = secondnum[numPairs - 1];
    }
    fclose(inputfile);

    // Count and print the 2grams
    for (int i = 0; i < numPairs; i++) {
        gramsCount[i] = 1;  

        for (int j = 0; j < i; j++) {
            if (firstnum[i] == firstnum[j] && secondnum[i] == secondnum[j]) {
                gramsCount[j]++;
                gramsCount[i] = 0;  // Mark the current pair for removal
                break;
            }
        }
    }

    // Open the output file for writing
    FILE *outputfile = fopen("output.txt", "w");

    if (outputfile == NULL) {
        printf("Error opening output.txt\n");
        return 1;
    }

    // Write unique 2grams and their counts to output.txt
    for (int i = 0; i < numPairs; i++) {
        if (gramsCount[i] > 0) {
            fprintf(outputfile, "%d %d: %d\n", firstnum[i], secondnum[i], gramsCount[i]);
        }
    }
    fclose(outputfile);

    printf("Check the output file (: \n");

    return 0;
}
