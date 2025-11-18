#include <stdio.h>

int main()  {

    int age = 0, contribution = 0;
    char gender;
    scanf("%d %d %c", &age, &contribution, &gender);

    switch (gender) {
        case 'M':
        if (age >= 60 && age < 65 && contribution >= 35) {
            printf("Pode aposentar\n");
        } else if (age >= 65) {
            printf("Pode aposentar\n");
        } else printf("Nao pode aposentar\n");
        break;
        case 'F':
        if (age >= 55 && age < 60 && contribution >= 30) {
            printf("Pode aposentar\n");
        } else if (age >= 60) {
            printf("Pode aposentar\n");
        } else printf("Nao pode aposentar\n");
        break;
        default:
        break;
    }

    return 0;
}