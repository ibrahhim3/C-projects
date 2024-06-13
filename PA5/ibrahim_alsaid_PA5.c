#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct calculation
{
    double carb;
    double protein;
    double fat;
    double total;
    int weight ;
};

int checkisdigit(const char *st)
{
    while (*st)
    {
        if (isdigit(*st))
        {
            return 1; // if a digit is found
        }
        st++;
    }
    return 0;  //if no digit is found
}
void removeWhitespace(char *str) {//this function for removing the spaces in the string
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {// to go through each character in the string

        if (!isspace(str[i])) {

            str[j++] = str[i];// If not a whitespace character, copy it to the new position
        }
    }
    str[j] = '\0'; 
}

void fun(char *meal, struct calculation *str)
{
    char component[600];

    printf("What is %s: ", meal);
    scanf(" %[^\n]",component);
    removeWhitespace(component);

    char *token = strtok(component, ",");
    int i = 0;
    char *co[20];
    while (token != NULL)
    {
        co[i] = malloc(strlen(token) + 1);
        strcpy(co[i], token);
        token = strtok(NULL, ",");
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        int a = checkisdigit(co[j]);
        if (a == 0)// no digits is found
        {
            fun(co[j], str);
        }
        else
        {
            struct calculation temp;
            printf("List the amount macro nutrients in %s: ", co[j]);
            scanf("%lf %lf %lf", &temp.carb, &temp.protein, &temp.fat);
            temp.total = (temp.carb * 4) + (temp.protein * 4) + (temp.fat * 9);
            sscanf(co[j], "%*[^0-9]%d", &temp.weight);//to get the number 

            // Adding the values 
            str->carb += temp.carb;
            str->protein += temp.protein;
            str->fat += temp.fat;
            str->total += temp.total;
            str->weight+=temp.weight;
        }
        free(co[j]);
    }
}

int main()
{
    char meal[30];
    printf("What is the meal: ");
    fgets(meal, sizeof(meal), stdin);
    meal[strcspn(meal, "\n")] = '\0';

    struct calculation meal_info={0};
    fun(meal, &meal_info);
    //to make the macros in precentage form
    double percentage_carb = (meal_info.carb * 4 / meal_info.total) * 100;
    double percentage_protein = (meal_info.protein * 4 / meal_info.total) * 100;
    double percentage_fat = (meal_info.fat * 9 / meal_info.total) * 100;

    printf("Total calories is %.2lf in %dg %s, %.2lf%% calories from carbs,%.2lf%% calories from proteins,%.2lf%% calories from fats \n", meal_info.total,meal_info.weight,meal, percentage_carb,percentage_protein,percentage_fat);

     return 0;
} 