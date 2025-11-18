#include <stdio.h> 

int main()  {

    int limit = 0, speed = 0;
    scanf("%d %d", &limit, &speed);

    if (speed <= (1.2 * limit) && speed > limit) {
        printf("Infracao Media\n");
    } else if (speed > (1.2 * limit) && speed <= (1.5 * limit)) {
        printf("Infracao Grave\n");
    } else if (speed > (1.5 * limit)) {
        printf("Infracao Gravissima\n");
    } else printf("Sem Infracao\n");

    return 0;
}