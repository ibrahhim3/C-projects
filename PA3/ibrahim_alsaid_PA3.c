#include <stdio.h>
#include <math.h>

#define MAX_VALUES 100
#define MAX_POLY_LENGTH 1000
#define MAX_POLYNOMIALS 100

double evaluatePolynomial(char *polynomial, double x) {
    double result = 0.0;
    char *term = polynomial;

    while (*term) {
        double coefficient = 0.0;
        int exponent = 0;  

        if (*term == 'x') {
            coefficient = 1.0;
            ++term;  // Move past 'x'
        } else {
            sscanf(term, "%lfx^%d", &coefficient, &exponent);
            if (coefficient == 0.0 && *(term + 1) == 'x') {
                coefficient = 1.0;
            }
        }

        result += coefficient * pow(x, exponent);

        while (*term && *term != '+' && *term != '-') {
            ++term;
        }

        // Move past the + or -
        if (*term) {
            ++term;
        }
    }

    return result;
}

int main() {
    FILE *valuesFile, *polynomialsFile, *evaluationsFile;
    double values[MAX_VALUES];
    char polynomial[MAX_POLY_LENGTH];
    int numValues = 0;

    // Open files
    valuesFile = fopen("values.txt", "r");
    polynomialsFile = fopen("polynomials.txt", "r");
    evaluationsFile = fopen("evaluations.txt", "w");

    // Read values
    while (fscanf(valuesFile, "%lf", &values[numValues]) == 1) {
        ++numValues;
    }
    fclose(valuesFile);

    // Read polynomials and evaluate
    while (fgets(polynomial, MAX_POLY_LENGTH, polynomialsFile) != NULL) {
        for (int i = 0; i < numValues; ++i) {
            double result = evaluatePolynomial(polynomial, values[i]);
            fprintf(evaluationsFile, "%.2f ", result);
        }
        fprintf(evaluationsFile, "\n");
    }
    fclose(polynomialsFile);

    fclose(evaluationsFile);

    return 0;
}