//pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printninja();

struct map {
    int searchval;
    int item;
    int found;
};

struct ninja {
    int search;
    int stealth;
};

int main(){
    FILE * ifp = NULL;
    char mapname[20];
    struct map temple[3][3];
    struct ninja skills[4];
    int i,j;//,k,l, evasion, sensei;

    printf("You have arrived at the Temple!\n");

    while(ifp == NULL) {
        printf("What is the name of your map?\n");
        scanf("%s", (char *)&mapname);

        ifp = fopen(mapname, "r");
        if (!ifp) {
            fprintf(stdout, "\x1b[1;31m'%s' not found or some shit\x1b[0m\n", mapname);
        }
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


    fclose(ifp);


    printf("You have 2 hours left to collect the relics.\n");
    printninja(&skills);

    return 0;
}

void printninja(struct ninja *skills){

    int i;
    printf("Ninja  Search  Stealth\n");
    for(i=0; i<4; i++){
        printf("%d\t", i+1);
        printf("%d\t", skills[i].search);
        printf("%d\n", skills[i].stealth);
    }
}
