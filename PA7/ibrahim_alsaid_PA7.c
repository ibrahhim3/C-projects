#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 1
#define AND 2
#define OR 3
#define NOT 4
#define FLIPFLOP 5
#define OUTPUT 6

struct gate {
    int type;
    char name[20];
    struct gate* inp1;
    struct gate* inp2;
    int output;
    int former_out;
};
    // here to connect the gates as required 
void establishConnection(struct gate* toGateptr, struct gate* fromGateptr) {
    if (toGateptr->type == AND || toGateptr->type == OR) {
        if (toGateptr->inp1 == NULL) {
            toGateptr->inp1 = fromGateptr; 
        } else if (toGateptr->inp2 == NULL) {
            toGateptr->inp2 = fromGateptr;
        } else {
            printf("WARNING Gate %s has more than 2 inputs\n", toGateptr->name);// the AND and OR gate has just 2 input 
            return ;
        }
    } else if (toGateptr->type == NOT || toGateptr->type == FLIPFLOP) {
        if (toGateptr->inp1 == NULL) {
            toGateptr->inp1 = fromGateptr;
        } else {
            printf("WARNING Gate %s has more than one input\n", toGateptr->name);// the NOT and FLIPFLOP gate has just ONE input 
            return ;
        }
    } else if (toGateptr->type == OUTPUT) {
        if (toGateptr->inp1 == NULL) {
            toGateptr->inp1 = fromGateptr;
        } else {
            printf("WARNING Output gate %s has more than one input\n", toGateptr->name);// the OUTPUT gate has just ONE input 
            return;
        }
    } else {
        printf("this type of gate was not found\n");
        return;
    }
    return;
}

//this function to find the adrese of thee gates 
struct gate* findGateByName(struct gate** gates, int numGates, const char* gateName) {
    for (int i = 0; i < numGates; ++i) {
        if (strcmp(gates[i]->name, gateName) == 0) {
            return gates[i];

        }
    }
    printf("Error: Gate %s not found\n", gateName);
    return NULL; // gate not found
}

int evaluateGate(struct gate* currentGate) {
    if (currentGate->type == INPUT) {
      //do no thing
    } else if (currentGate->type == AND) {
        if (currentGate->inp1 != NULL && currentGate->inp2 != NULL) {
            int input1 = evaluateGate(currentGate->inp1);
            int input2 = evaluateGate(currentGate->inp2);
            currentGate->output = input1 && input2;
        }
    } else if (currentGate->type == OR) {
        if (currentGate->inp1 != NULL && currentGate->inp2 != NULL) {
            int input1 = evaluateGate(currentGate->inp1);
            int input2 = evaluateGate(currentGate->inp2);
            currentGate->output = input1 || input2;
        }
    } else if (currentGate->type == NOT) {
        if (currentGate->inp1 != NULL) {
            currentGate->output = !evaluateGate(currentGate->inp1);
        }
    } else if (currentGate->type == FLIPFLOP) {
    if (currentGate->inp1 != NULL) {
        int input1 = evaluateGate(currentGate->inp1);
        
         //the form of the flipflop :)
        if (input1 == 0 && currentGate->former_out == 0) {
            currentGate->output = 0;
            currentGate->former_out=0;
        } else if (input1 == 0 && currentGate->former_out == 1) {
            currentGate->output = 1;
            currentGate->former_out=1;
        } else if (input1 == 1 && currentGate->former_out == 0) {
            currentGate->output = 1;
            currentGate->former_out=0;
        } else if (input1 == 1 && currentGate->former_out == 1) {
            currentGate->output = 0;
            currentGate->former_out=1;
        }

    }
}

    return currentGate->output;
}

int main() {

    FILE* circuitFile = fopen("circuit.txt", "r");
    if (circuitFile == NULL) {
        printf("Error opening circuit.txt\n");
        return 1;
    }

    char line[100];
    int numGates = 0;
    struct gate** gates = malloc(sizeof(struct gate*) * 15);//for 15 gates initially

    // read the content of circuit.txt
    while (fgets(line, sizeof(line), circuitFile)) {
        char* token = strtok(line, " ");
        //if the word is GATE store the type and the name
        if (strcmp(token, "GATE") == 0) {
            token = strtok(NULL, " ");
            char gateType[20];
            strcpy(gateType, token);
            token = strtok(NULL, "\n");
            char gateName[20];
            strcpy(gateName, token);

            // dynamically allocate memory for the gate struct
            struct gate* newGate = (struct gate*)malloc(sizeof(struct gate));
            if (strcmp(gateType, "INPUT") == 0) {
                newGate->type = INPUT;
            } else if (strcmp(gateType, "AND") == 0) {
                newGate->type = AND;
            } else if (strcmp(gateType, "OR") == 0) {
                newGate->type = OR;
            } else if (strcmp(gateType, "NOT") == 0) {
                newGate->type = NOT;
            } else if (strcmp(gateType, "FLIPFLOP") == 0) {
                newGate->type = FLIPFLOP;
            } else if (strcmp(gateType, "OUTPUT") == 0) {
                newGate->type = OUTPUT;
            }
            strcpy(newGate->name, gateName);
            newGate->inp1 = NULL;
            newGate->inp2 = NULL;
            // add gate to the gates array and increasing the num of gates
            gates[numGates++] = newGate;
            // here to make sure there will not be any flow
            if (numGates >= 15) {
                gates = realloc(gates, sizeof(struct gate*) * (numGates + 10));
                if (gates == NULL) {
                    printf("memory allocation failed\n");
                    return 1;
                }
            }
            //if the word is CONNECTION get the first word after the CONNECTION as fromgate pointer and so on
        } else if (strcmp(token, "CONNECTION") == 0) {
            token = strtok(NULL, " ");
            char fromGate[20];
            strcpy(fromGate, token);
            token = strtok(NULL, "\n");
            char toGate[20];
            strcpy(toGate, token);
            // find the gates based on their names
            struct gate* fromGateptr = findGateByName(gates, numGates, fromGate);
            struct gate* toGateptr = findGateByName(gates, numGates, toGate);
            // establish connection between gates
            if (fromGateptr != NULL && toGateptr != NULL) {
             establishConnection(toGateptr, fromGateptr);
                
            }
        }
    }

    fclose(circuitFile);
    //opening input file 
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }
        int flipFlopStates[numGates];  // assuming each FLIPFLOP gate has a unique index
        for (int i = 0; i < numGates; ++i) {
            if (gates[i]->type == FLIPFLOP) {
                flipFlopStates[i] = 0;  // Initialize FLIPFLOP state to 0
            }
        }
    // read input values from the file and assign them to INPUT gates
    int numLinesInInputFile = 0;
    while (fgets(line, sizeof(line), inputFile)) {
        numLinesInInputFile++;
    }
    // reset file pointer to the beginning of the input file
    fseek(inputFile, 0, SEEK_SET);

    // read input values from the file and assign them to INPUT gates
    for (int lineNum = 0; lineNum < numLinesInInputFile; ++lineNum) {
        for (int i = 0; i < numGates; ++i) {
            if (gates[i]->type == INPUT) {
                char digit;
                do {
                    if (fscanf(inputFile, "%c", &digit) != 1) {
                        printf("Error reading input file");
                        return 1;
                    }
                } while (digit == '\n');//till the newline then go out the loop
                gates[i]->output = digit - '0';//storing the inputs in the INPUT gates by using ASCII table 

            }
        }    // this for loop for printint the output the and evaluates the output of the gates and handling the FLIPFLOP values 
            for (int i = 0; i < numGates; ++i) {
                if(gates[i]->type == OUTPUT ){
                    printf("%d\n",gates[i-1]->output); 
                } 
                if(gates[i]->type == FLIPFLOP){
                flipFlopStates[i] = gates[i]->output;
                gates[i]->former_out = flipFlopStates[i];
                }
                gates[i]->output = evaluateGate(gates[i]);
            }
             
    }
    fclose(inputFile);
    // Free allocated memory
    for (int i = 0; i < numGates; ++i) {
        free(gates[i]);
    }
    free(gates);

    return 0;
}