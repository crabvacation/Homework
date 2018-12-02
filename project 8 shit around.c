//pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    FILE * ifp = NULL;
    struct map {
        int searchval;
        int item;
        int found;
    };
    struct ninja {
        int search;
        int stealth;
    };
    char mapname[20];
    struct map temple[3][3];
    struct ninja skills[4];
    int i,j;

    while(ifp == NULL) {
    printf("What is the name of your map?\n");
    scanf("%s", &mapname);

    ifp = fopen(mapname, "r");
    }

    for(i=0; i<3; i++)
        for(j=0; j<3; j++){
            fscanf(ifp, "%d", &temple[i][j].searchval);
            fscanf(ifp, "%d", &temple[i][j].item);
    }

    for(i=0; i<4; i++){
        fscanf(ifp, "%d", &skills[i].search);
        fscanf(ifp, "%d", &skills[i].stealth);
    }

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%d  ", temple[i][j].searchval);
            printf("%d\t", temple[i][j].item);
    }

    printf("\n");
    }

    for(i=0; i<4; i++){
        printf("%d  ", &skills[i].search);
        printf("%d\n", &skills[i].stealth);
    }

    fclose(ifp);

    return 0;
}